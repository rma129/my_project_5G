/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/cu_cp/cu_cp_types.h"
#include "srsran/cu_cp/up_resource_manager.h"
#include "srsran/e1ap/common/e1ap_types.h"
#include "srsran/e1ap/cu_cp/e1ap_cu_cp_bearer_context_update.h"
#include "srsran/pdcp/pdcp_config.h"
#include "srsran/rrc/rrc_types.h"

namespace srsran {
namespace srs_cu_cp {

void fill_e1ap_drb_pdcp_config(e1ap_pdcp_config& e1ap_pdcp_cfg, const pdcp_config& cu_cp_pdcp_cfg);
void fill_e1ap_qos_flow_param_item(e1ap_qos_flow_qos_param_item&      e1ap_qos_item,
                                   const srslog::basic_logger&        logger,
                                   const qos_flow_setup_request_item& request_item);
void fill_drb_to_setup_list(slotted_id_vector<drb_id_t, e1ap_drb_to_setup_item_ng_ran>&          e1ap_drb_to_setup_list,
                            const slotted_id_vector<qos_flow_id_t, qos_flow_setup_request_item>& qos_flow_list,
                            const std::map<drb_id_t, up_drb_context>&                            drb_to_add_list,
                            const srslog::basic_logger&                                          logger);
void fill_drb_to_remove_list(std::vector<drb_id_t>&       e1ap_drb_to_remove_list,
                             const std::vector<drb_id_t>& drb_to_remove_list);

/// \brief Fill RRC Reconfiguration Arguments.
/// \param[out] rrc_reconfig_args The RRC Reconfiguration Arguments struct to fill.
/// \param[in] srbs_to_be_setup_mod_list SRBs to be setup (only needed if default DRB is being setup).
/// \param[in] pdu_sessions The PDU sessions to add to the reconfiguration.
/// \param[in] ue_context_modification_response The UE Context Modification Response as received by the DU.
/// \param[in] nas_pdus NAS PDUs to forward to the UE as received by the AMF.
void fill_rrc_reconfig_args(
    rrc_reconfiguration_procedure_request&                              rrc_reconfig_args,
    const slotted_id_vector<srb_id_t, cu_cp_srbs_to_be_setup_mod_item>& srbs_to_be_setup_mod_list,
    const std::map<pdu_session_id_t, up_pdu_session_context_update>&    pdu_sessions,
    const cu_cp_ue_context_modification_response&                       ue_context_modification_response,
    const std::map<pdu_session_id_t, byte_buffer>&                      nas_pdus,
    bool                                                                is_reestablishment = false);

bool update_setup_list(
    slotted_id_vector<pdu_session_id_t, cu_cp_pdu_session_res_setup_response_item>& ngap_response_list,
    cu_cp_ue_context_modification_request&                                          ue_context_mod_request,
    const slotted_id_vector<pdu_session_id_t, cu_cp_pdu_session_res_setup_item>&    ngap_setup_list,
    const slotted_id_vector<pdu_session_id_t, e1ap_pdu_session_resource_setup_modification_item>&
                            pdu_session_resource_setup_list,
    const up_config_update& next_config,
    up_resource_manager&    rrc_ue_up_resource_manager,
    srslog::basic_logger&   logger);

bool update_setup_list(
    slotted_id_vector<pdu_session_id_t, cu_cp_pdu_session_res_setup_response_item>& ngap_response_list,
    e1ap_bearer_context_modification_request&                                       bearer_ctxt_mod_request,
    const slotted_id_vector<pdu_session_id_t, cu_cp_pdu_session_res_setup_item>&    ngap_setup_list,
    const cu_cp_ue_context_modification_response&                                   ue_context_modification_response,
    const up_config_update&                                                         next_config,
    const srslog::basic_logger&                                                     logger);

void update_failed_list(
    slotted_id_vector<pdu_session_id_t, cu_cp_pdu_session_res_setup_failed_item>&     ngap_failed_list,
    const slotted_id_vector<pdu_session_id_t, e1ap_pdu_session_resource_failed_item>& pdu_session_resource_failed_list);

/// \brief Processes the result of a Bearer Context Modifcation Result's PDU session modify list.
/// \param[out] ngap_response_list Reference to the final NGAP response
/// \param[out] ue_context_mod_request Reference to the next request message - a UE context modification.
/// \param[in] ngap_modify_list Const reference to the original NGAP request
/// \param[in] e1ap_pdu_session_resource_modify_list Const reference to the response of the previous subprocedure
/// \param[in]next_config Const reference to the calculated config update
/// \param[in] logger Reference to the logger.
/// \return True on success, false otherwise.
bool update_modify_list(
    slotted_id_vector<pdu_session_id_t, cu_cp_pdu_session_resource_modify_response_item>& ngap_response_list,
    cu_cp_ue_context_modification_request&                                                ue_context_mod_request,
    const slotted_id_vector<pdu_session_id_t, cu_cp_pdu_session_res_modify_item_mod_req>& ngap_modify_list,
    const slotted_id_vector<pdu_session_id_t, e1ap_pdu_session_resource_modified_item>&
                                e1ap_pdu_session_resource_modify_list,
    const up_config_update&     next_config,
    const srslog::basic_logger& logger);

/// \brief Processes the response of a UE Context Modifcation Request.
/// \param[out] ngap_response_list Reference to the final NGAP response.
/// \param[out] ue_context_mod_request Reference to the next request message - a Bearer context modification request.
/// \param[in] ngap_modify_list Const reference to the original NGAP request
/// \param[in] ue_context_modification_response Const reference to the response of the UE context modifcation request.
/// \param[in] next_config Const reference to the calculated config update
/// \param[in] logger Reference to the logger.
/// \return True on success, false otherwise.
bool update_modify_list(
    slotted_id_vector<pdu_session_id_t, cu_cp_pdu_session_resource_modify_response_item>& ngap_response_list,
    e1ap_bearer_context_modification_request&                                             bearer_context_mod_request,
    const slotted_id_vector<pdu_session_id_t, cu_cp_pdu_session_res_modify_item_mod_req>& ngap_modify_list,
    const cu_cp_ue_context_modification_response& ue_context_modification_response,
    const up_config_update&                       next_config,
    const srslog::basic_logger&                   logger);

} // namespace srs_cu_cp
} // namespace srsran
