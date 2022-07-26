/*
 *
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "procedures/f1ap_ue_context_release_procedure.h"
#include "srsgnb/adt/slot_array.h"
#include "srsgnb/asn1/f1ap.h"
#include "srsgnb/f1_interface/cu/f1ap_cu.h"
#include "srsgnb/ran/nr_cgi.h"
#include "srsgnb/support/async/async_queue.h"
#include "srsgnb/support/async/async_task_loop.h"
#include <memory>

namespace srsgnb {
namespace srs_cu_cp {

class f1ap_event_manager;

class f1ap_cu_impl final : public f1_interface
{
public:
  f1ap_cu_impl(f1c_message_notifier&              f1c_pdu_notifier_,
               f1c_du_processor_message_notifier& f1c_du_processor_notifier_,
               f1c_du_management_notifier&        f1c_du_management_notifier_);
  ~f1ap_cu_impl();

  // f1ap connection manager functions

  void handle_f1ap_setup_response(const f1_setup_response_message& msg) override;

  // f1ap rrc message transfer procedure functions

  void handle_dl_rrc_message_transfer(const f1ap_dl_rrc_message& msg) override;

  void add_ue_index_to_context(f1ap_ue_id_t cu_ue_id, ue_index_t ue_index) override;

  // f1ap ue context manager functions

  async_task<f1ap_ue_context_setup_response_message>
  handle_ue_context_setup_request(const f1ap_ue_context_setup_request_message& request) override;

  void handle_ue_context_release_command(const f1ap_ue_context_release_command_message& msg) override;

  async_task<f1ap_ue_context_modification_response_message>
  handle_ue_context_modification(const f1ap_ue_context_modification_request_message& request) override;

  // f1c message handler functions

  void handle_message(const f1c_msg& msg) override;

  void handle_connection_loss() override {}

  // F1AP statistics
  int get_nof_ues() override;

private:
  /// \brief Notify about the reception of an initiating message.
  /// \param[in] msg The received initiating message.
  void handle_initiating_message(const asn1::f1ap::init_msg_s& msg);

  /// \brief Notify about the reception of an Initial UL RRC Message Transfer message.
  /// \param[in] msg The F1AP initial UL RRC message.
  void handle_initial_ul_rrc_message(const asn1::f1ap::init_ulrrc_msg_transfer_s& msg);

  /// \brief Notify about the reception of an UL RRC Message Transfer message.
  /// \param[in] msg The F1AP UL RRC message.
  void handle_ul_rrc_message(const asn1::f1ap::ulrrc_msg_transfer_s& msg);

  /// \brief Notify about the reception of an successful outcome.
  /// \param[in] msg The received successful outcome message.
  void handle_successful_outcome(const asn1::f1ap::successful_outcome_s& outcome);

  /// \brief Notify about the reception of an F1 Removal Request.
  /// \param[in] msg The F1 Removal Request message.
  void handle_f1_removal_resquest(const f1_removal_request_message& msg);

  /// \brief Get the next available CU UE ID.
  /// \return The CU UE ID.
  f1ap_ue_id_t get_next_cu_ue_id();

  /// \brief Find the CU UE ID by a given UE index.
  /// \param[in] ue_index The UE index used to find the CU UE ID.
  /// \return The CU UE ID.
  f1ap_ue_id_t find_cu_ue_id(ue_index_t ue_index);

  /// \brief Remove a UE context from the F1AP.
  /// \param[in] cu_ue_id The ID of the UE.
  void remove_ue(f1ap_ue_id_t cu_ue_id);

  srslog::basic_logger& logger;

  std::array<f1ap_ue_context, MAX_NOF_UES> cu_ue_id_to_f1ap_ue_context;

  // nofifiers and handles

  f1c_message_notifier&              pdu_notifier;
  f1c_du_processor_message_notifier& du_processor_notifier;
  f1c_du_management_notifier&        du_management_notifier;

  std::unique_ptr<f1ap_event_manager> events;

  // task event loops indexed by ue_index
  slot_array<async_task_sequencer, MAX_NOF_UES> ue_ctrl_loop;
};

} // namespace srs_cu_cp
} // namespace srsgnb
