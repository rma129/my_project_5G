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

#include "srsran/adt/expected.h"
#include "srsran/asn1/f1ap/f1ap.h"
#include "srsran/support/async/event_signal.h"
#include "srsran/support/async/protocol_transaction_manager.h"

namespace srsran {
namespace srs_du {

/// Response type of a F1AP DU transaction.
using f1ap_transaction_response = expected<asn1::f1ap::successful_outcome_s, asn1::f1ap::unsuccessful_outcome_s>;

/// F1AP protocol transaction type.
using f1ap_transaction = protocol_transaction<f1ap_transaction_response>;

class f1ap_event_manager
{
  /// Transaction Response Container, which gets indexed by transaction_id.
  constexpr static size_t MAX_NOF_TRANSACTIONS = 256;

public:
  protocol_transaction_manager<f1ap_transaction_response> transactions;

  /// F1 UE Context Modification Outcome
  using f1ap_ue_context_modification_outcome_t =
      expected<const asn1::f1ap::ue_context_mod_confirm_s*, const asn1::f1ap::ue_context_mod_refuse_s*>;
  event_signal<f1ap_ue_context_modification_outcome_t> f1ap_ue_context_modification_outcome;

  explicit f1ap_event_manager(timer_factory timer_service) : transactions(MAX_NOF_TRANSACTIONS, timer_service) {}
};

} // namespace srs_du
} // namespace srsran
