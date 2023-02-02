/*
 *
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "ngc_impl.h"
#include "ngap_asn1_helpers.h"
#include "ngap_asn1_utils.h"
#include "procedures/ng_setup_procedure.h"
#include "procedures/ngap_initial_context_setup_procedure.h"
#include "procedures/ngap_pdu_session_resource_setup_procedure.h"
#include "procedures/ngap_procedure_helpers.h"

using namespace srsgnb;
using namespace asn1::ngap;
using namespace srs_cu_cp;

ngc_impl::ngc_impl(ngc_configuration&     ngc_cfg_,
                   ngc_ue_task_scheduler& task_sched_,
                   ngap_ue_manager&       ue_manager_,
                   ngc_message_notifier&  ngc_notifier_,
                   task_executor&         ctrl_exec_) :
  logger(srslog::fetch_basic_logger("NGC")),
  ngc_cfg(ngc_cfg_),
  task_sched(task_sched_),
  ue_manager(ue_manager_),
  ngc_notifier(ngc_notifier_),
  ctrl_exec(ctrl_exec_),
  ev_mng(task_sched.get_timer_manager())
{
}

// Note: For fwd declaration of member types, dtor cannot be trivial.
ngc_impl::~ngc_impl() {}

void ngc_impl::create_ngc_ue(ue_index_t                         ue_index,
                             ngc_rrc_ue_pdu_notifier&           rrc_ue_pdu_notifier,
                             ngc_rrc_ue_control_notifier&       rrc_ue_ctrl_notifier,
                             ngc_du_processor_control_notifier& du_processor_ctrl_notifier)
{
  // Create UE context and store it
  ngap_ue* ue = ue_manager.add_ue(ue_index, rrc_ue_pdu_notifier, rrc_ue_ctrl_notifier, du_processor_ctrl_notifier);

  if (ue == nullptr) {
    logger.error("Failed to create NGAP UE (ue_index={})", ue_index);
    return;
  }

  logger.debug("Created NGAP UE (ran_ue_id={}, ue_index={})", ue->get_ran_ue_id(), ue_index);
}

async_task<ng_setup_response> ngc_impl::handle_ng_setup_request(const ng_setup_request& request)
{
  if (logger.debug.enabled()) {
    asn1::json_writer js;
    request.msg.to_json(js);
    logger.debug("Containerized NG Setup Request: {}", js.to_string());
  }

  return launch_async<ng_setup_procedure>(request, ngc_notifier, ev_mng, task_sched.get_timer_manager(), logger);
}

void ngc_impl::handle_initial_ue_message(const ngap_initial_ue_message& msg)
{
  auto* ue = ue_manager.find_ngap_ue(msg.ue_index);
  if (ue == nullptr) {
    logger.info("UE with ue_index={} does not exist. Dropping Initial UE Message", msg.ue_index);
    return;
  }

  logger.info("Handling Initial UE Message for UE with ran_ue_id={}", ue->get_ran_ue_id());

  ngc_message ngc_msg = {};
  ngc_msg.pdu.set_init_msg();
  ngc_msg.pdu.init_msg().load_info_obj(ASN1_NGAP_ID_INIT_UE_MSG);

  auto& init_ue_msg                       = ngc_msg.pdu.init_msg().value.init_ue_msg();
  init_ue_msg->ran_ue_ngap_id.value.value = ran_ue_id_to_uint(ue->get_ran_ue_id());

  init_ue_msg->nas_pdu.value.resize(msg.nas_pdu.length());
  std::copy(msg.nas_pdu.begin(), msg.nas_pdu.end(), init_ue_msg->nas_pdu.value.begin());

  init_ue_msg->rrc_establishment_cause.value.value = msg.establishment_cause.value;

  auto& user_loc_info_nr       = init_ue_msg->user_location_info.value.set_user_location_info_nr();
  user_loc_info_nr.nr_cgi      = msg.nr_cgi;
  user_loc_info_nr.tai.plmn_id = msg.nr_cgi.plmn_id;
  user_loc_info_nr.tai.tac.from_number(msg.tac);

  init_ue_msg->ue_context_request_present = true;
  init_ue_msg->ue_context_request.value   = asn1::ngap::ue_context_request_opts::options::requested;

  // TODO: Add missing optional values

  if (logger.debug.enabled()) {
    asn1::json_writer js;
    ngc_msg.pdu.to_json(js);
    logger.debug("Containerized Initial UE Message: {}", js.to_string());
  }

  // Forward message to AMF
  ngc_notifier.on_new_message(ngc_msg);
}

void ngc_impl::handle_ul_nas_transport_message(const ngap_ul_nas_transport_message& msg)
{
  auto* ue = ue_manager.find_ngap_ue(msg.ue_index);
  if (ue == nullptr) {
    logger.info("UE with ue_index={} does not exist. Dropping UL NAS Transport Message", msg.ue_index);
    return;
  }

  logger.info("Handling UL NAS Transport Message for UE with ran_ue_id={}", ue->get_ran_ue_id());

  ngc_message ngc_msg = {};
  ngc_msg.pdu.set_init_msg();
  ngc_msg.pdu.init_msg().load_info_obj(ASN1_NGAP_ID_UL_NAS_TRANSPORT);

  auto& ul_nas_transport_msg = ngc_msg.pdu.init_msg().value.ul_nas_transport();

  ul_nas_transport_msg->ran_ue_ngap_id.value.value = ran_ue_id_to_uint(ue->get_ran_ue_id());

  amf_ue_id_t amf_ue_id = ue->get_amf_ue_id();
  if (amf_ue_id == amf_ue_id_t::invalid) {
    logger.error("UE AMF ID for ue_index={} not found!", msg.ue_index);
    return;
  }
  ul_nas_transport_msg->amf_ue_ngap_id.value.value = amf_ue_id_to_uint(amf_ue_id);

  ul_nas_transport_msg->nas_pdu.value.resize(msg.nas_pdu.length());
  std::copy(msg.nas_pdu.begin(), msg.nas_pdu.end(), ul_nas_transport_msg->nas_pdu.value.begin());

  auto& user_loc_info_nr       = ul_nas_transport_msg->user_location_info.value.set_user_location_info_nr();
  user_loc_info_nr.nr_cgi      = msg.nr_cgi;
  user_loc_info_nr.tai.plmn_id = msg.nr_cgi.plmn_id;
  user_loc_info_nr.tai.tac.from_number(msg.tac);

  if (logger.debug.enabled()) {
    asn1::json_writer js;
    ngc_msg.pdu.to_json(js);
    logger.debug("Containerized UL NAS Transport Message: {}", js.to_string());
  }

  // Forward message to AMF
  ngc_notifier.on_new_message(ngc_msg);
}

void ngc_impl::handle_message(const ngc_message& msg)
{
  logger.info("Handling NGAP PDU of type \"{}.{}\"", msg.pdu.type().to_string(), get_message_type_str(msg.pdu));

  if (logger.debug.enabled()) {
    asn1::json_writer js;
    msg.pdu.to_json(js);
    logger.debug("Rx NGAP message: {}", js.to_string());
  }

  // Run NGAP protocols in Control executor.
  ctrl_exec.execute([this, msg]() {
    switch (msg.pdu.type().value) {
      case ngap_pdu_c::types_opts::init_msg:
        handle_initiating_message(msg.pdu.init_msg());
        break;
      case ngap_pdu_c::types_opts::successful_outcome:
        handle_successful_outcome(msg.pdu.successful_outcome());
        break;
      case ngap_pdu_c::types_opts::unsuccessful_outcome:
        handle_unsuccessful_outcome(msg.pdu.unsuccessful_outcome());
        break;
      default:
        logger.error("Invalid PDU type");
        break;
    }
  });
}

void ngc_impl::handle_initiating_message(const init_msg_s& msg)
{
  switch (msg.value.type().value) {
    case ngap_elem_procs_o::init_msg_c::types_opts::dl_nas_transport:
      handle_dl_nas_transport_message(msg.value.dl_nas_transport());
      break;
    case ngap_elem_procs_o::init_msg_c::types_opts::init_context_setup_request:
      handle_initial_context_setup_request(msg.value.init_context_setup_request());
      break;
    case ngap_elem_procs_o::init_msg_c::types_opts::pdu_session_res_setup_request:
      handle_pdu_session_resource_setup_request(msg.value.pdu_session_res_setup_request());
      break;
    case ngap_elem_procs_o::init_msg_c::types_opts::ue_context_release_cmd:
      handle_ue_context_release_command(msg.value.ue_context_release_cmd());
      break;
    default:
      logger.error("Initiating message of type {} is not supported", msg.value.type().to_string());
  }
}

void ngc_impl::handle_dl_nas_transport_message(const asn1::ngap::dl_nas_transport_s& msg)
{
  ue_index_t ue_index = ue_manager.get_ue_index(uint_to_ran_ue_id(msg->ran_ue_ngap_id.value.value));
  if (ue_index == ue_index_t::invalid) {
    logger.info("UE with ue_index={} does not exist. Dropping PDU", ue_index);
    return;
  }

  auto* ue = ue_manager.find_ngap_ue(ue_index);
  if (ue == nullptr) {
    logger.info("UE with ue_index={} does not exist. Dropping PDU", ue_index);
    return;
  }

  // Add AMF UE ID to ue ngap context if it is not set (this is the first DL NAS Transport message)
  if (ue->get_amf_ue_id() == amf_ue_id_t::invalid) {
    // Set AMF UE ID in the UE context and also in the lookup
    ue_manager.set_amf_ue_id(ue_index, uint_to_amf_ue_id(msg->amf_ue_ngap_id.value.value));
  }

  byte_buffer nas_pdu;
  nas_pdu.resize(msg->nas_pdu.value.size());
  std::copy(msg->nas_pdu.value.begin(), msg->nas_pdu.value.end(), nas_pdu.begin());
  logger.debug(nas_pdu.begin(), nas_pdu.end(), "DL NAS Transport PDU ({} B)", nas_pdu.length());

  ue->get_rrc_ue_pdu_notifier().on_new_pdu(std::move(nas_pdu));
}

void ngc_impl::handle_initial_context_setup_request(const asn1::ngap::init_context_setup_request_s& request)
{
  ue_index_t ue_index = ue_manager.get_ue_index(uint_to_ran_ue_id(request->ran_ue_ngap_id.value));
  auto*      ue       = ue_manager.find_ngap_ue(ue_index);
  if (ue == nullptr) {
    logger.info("UE with ue_index={} does not exist. Dropping Initial Context Setup Request", ue_index);
    return;
  }

  if (logger.debug.enabled()) {
    asn1::json_writer js;
    request.to_json(js);
    logger.debug("Received Initial Context Setup Request Message: {}", js.to_string());
  }

  // start routine
  task_sched.schedule_async_task(
      ue_index,
      launch_async<ngap_initial_context_setup_procedure>(ue_index, request, ue_manager, ngc_notifier, logger));
}

void ngc_impl::handle_pdu_session_resource_setup_request(const asn1::ngap::pdu_session_res_setup_request_s& request)
{
  ue_index_t ue_index = ue_manager.get_ue_index(uint_to_ran_ue_id(request->ran_ue_ngap_id.value));
  auto*      ue       = ue_manager.find_ngap_ue(ue_index);
  if (ue == nullptr) {
    logger.info("UE with ue_index={} does not exist. Dropping PDU Session Resource Setup Request", ue_index);
    return;
  }

  if (logger.debug.enabled()) {
    asn1::json_writer js;
    request.to_json(js);
    logger.debug("Received PDU Session Resource Setup Request Message: {}", js.to_string());
  }

  // Store information in UE context
  if (request->ue_aggr_max_bit_rate_present) {
    ue->set_aggregate_maximum_bit_rate_dl(request->ue_aggr_max_bit_rate.value.ue_aggr_max_bit_rate_dl);
  }

  // Convert to common type
  cu_cp_pdu_session_resource_setup_request msg;
  msg.ue_index     = ue_index;
  msg.serving_plmn = ngc_cfg.plmn;
  fill_cu_cp_pdu_session_resource_setup_request(msg, request->pdu_session_res_setup_list_su_req.value);
  msg.ue_aggregate_maximum_bit_rate_dl = ue->get_aggregate_maximum_bit_rate_dl();

  // start routine
  task_sched.schedule_async_task(ue_index,
                                 launch_async<ngap_pdu_session_resource_setup_procedure>(
                                     *ue, msg, ue->get_du_processor_control_notifier(), ngc_notifier, logger));

  // Handle optional parameters
  if (request->nas_pdu_present) {
    handle_nas_pdu(logger, request->nas_pdu.value, *ue);
  }
}

void ngc_impl::handle_ue_context_release_command(const asn1::ngap::ue_context_release_cmd_s& cmd)
{
  amf_ue_id_t amf_ue_id = amf_ue_id_t::invalid;
  ran_ue_id_t ran_ue_id = ran_ue_id_t::invalid;
  if (cmd->ue_ngap_ids.value.type() == asn1::ngap::ue_ngap_ids_c::types_opts::amf_ue_ngap_id) {
    amf_ue_id = uint_to_amf_ue_id(cmd->ue_ngap_ids->amf_ue_ngap_id());
  } else if (cmd->ue_ngap_ids.value.type() == asn1::ngap::ue_ngap_ids_c::types_opts::ue_ngap_id_pair) {
    amf_ue_id = uint_to_amf_ue_id(cmd->ue_ngap_ids->ue_ngap_id_pair().amf_ue_ngap_id);
    ran_ue_id = uint_to_ran_ue_id(cmd->ue_ngap_ids->ue_ngap_id_pair().ran_ue_ngap_id);
  }
  ue_index_t ue_index = ue_manager.get_ue_index(amf_ue_id);
  auto*      ue       = ue_manager.find_ngap_ue(ue_index);
  if (ue == nullptr) {
    logger.info("UE with ue_index={} does not exist. Dropping UE Context Release Command", ue_index);
    return;
  }

  if (ran_ue_id == ran_ue_id_t::invalid) {
    ran_ue_id = ue->get_ran_ue_id();
  }

  if (logger.debug.enabled()) {
    asn1::json_writer js;
    cmd.to_json(js);
    logger.debug("Received UE Context Release Command: {}", js.to_string());
  }

  // Convert to common type
  cu_cp_ue_context_release_command msg;
  msg.ue_index = ue_index;
  fill_cu_cp_ue_context_release_command(msg, cmd);

  // Notify DU processor about UE Context Release Command
  ue->get_du_processor_control_notifier().on_new_ue_context_release_command(msg);

  // Send UE Context Release Complete
  ngc_message ngc_msg = {};

  ngc_msg.pdu.set_successful_outcome();
  ngc_msg.pdu.successful_outcome().load_info_obj(ASN1_NGAP_ID_UE_CONTEXT_RELEASE);

  // TODO: Add optional fields to UE context Release Complete
  // fill_asn1_ue_context_release_complete(ngc_msg.pdu.successful_outcome().value.ue_context_release_complete(),
  // response);

  auto& ue_context_release_complete = ngc_msg.pdu.successful_outcome().value.ue_context_release_complete();
  ue_context_release_complete->amf_ue_ngap_id.value = amf_ue_id_to_uint(amf_ue_id);
  ue_context_release_complete->ran_ue_ngap_id.value = ran_ue_id_to_uint(ran_ue_id);

  if (logger.debug.enabled()) {
    asn1::json_writer js;
    ngc_msg.pdu.to_json(js);
    logger.debug("Containerized UE Context Release Complete Message: {}", js.to_string());
  }

  // Remove NGAP UE
  ue_manager.remove_ngap_ue(ue_index);

  logger.info("Sending UE Context Release Complete to AMF");
  ngc_notifier.on_new_message(ngc_msg);
}

void ngc_impl::handle_successful_outcome(const successful_outcome_s& outcome)
{
  switch (outcome.value.type().value) {
    case ngap_elem_procs_o::successful_outcome_c::types_opts::ng_setup_resp: {
      ev_mng.ng_setup_outcome.set(outcome.value.ng_setup_resp());
    } break;
    default:
      logger.error("Successful outcome of type {} is not supported", outcome.value.type().to_string());
  }
}

void ngc_impl::handle_unsuccessful_outcome(const unsuccessful_outcome_s& outcome)
{
  switch (outcome.value.type().value) {
    case ngap_elem_procs_o::unsuccessful_outcome_c::types_opts::ng_setup_fail: {
      ev_mng.ng_setup_outcome.set(outcome.value.ng_setup_fail());
    } break;
    default:
      logger.error("Unsuccessful outcome of type {} is not supported", outcome.value.type().to_string());
  }
}

size_t ngc_impl::get_nof_ues() const
{
  return ue_manager.get_nof_ngap_ues();
}
