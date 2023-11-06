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

#include "srsran/phy/support/resource_grid_context.h"
#include "srsran/phy/upper/channel_processors/channel_processor_formatters.h"
#include "srsran/phy/upper/downlink_processor.h"
#include "srsran/phy/upper/signal_processors/signal_processor_formatters.h"
#include "srsran/phy/upper/unique_tx_buffer.h"

namespace srsran {
class task_executor;

/// \brief Downlink processor implementation with a single executor.
///
/// In this implementation, every task is processed by the same executor. When a task finishes, the results are notified
/// by the upper_phy_rx_results_notifier interface.
class logging_downlink_processor_decorator : public downlink_processor
{
public:
  logging_downlink_processor_decorator(std::unique_ptr<downlink_processor> downlink_proc_,
                                       srslog::basic_logger&               logger_) :
    downlink_proc(std::move(downlink_proc_)), logger(logger_)
  {
    srsran_assert(downlink_proc, "Invalid downlink processor.");
  }

  // See interface for documentation.
  bool process_pdcch(const pdcch_processor::pdu_t& pdu) override
  {
    bool is_enqueued = downlink_proc->process_pdcch(pdu);
    if (!is_enqueued) {
      logger.warning("Could not process PDCCH PDU: {:s}", pdu);
    }
    return is_enqueued;
  }

  // See interface for documentation.
  bool process_pdsch(unique_tx_buffer                                                                     softbuffer,
                     const static_vector<span<const uint8_t>, pdsch_processor::MAX_NOF_TRANSPORT_BLOCKS>& data,
                     const pdsch_processor::pdu_t&                                                        pdu) override
  {
    bool is_enqueued = downlink_proc->process_pdsch(std::move(softbuffer), data, pdu);
    if (!is_enqueued) {
      logger.warning("Could not process PDSCH PDU: {:s}", pdu);
    }
    return is_enqueued;
  }

  // See interface for documentation.
  bool process_ssb(const ssb_processor::pdu_t& pdu) override
  {
    bool is_enqueued = downlink_proc->process_ssb(pdu);
    if (!is_enqueued) {
      logger.warning("Could not process SSB PDU: {:s}", pdu);
    }
    return is_enqueued;
  }

  // See interface for documentation.
  bool process_nzp_csi_rs(const nzp_csi_rs_generator::config_t& config) override
  {
    bool is_enqueued = downlink_proc->process_nzp_csi_rs(config);
    if (!is_enqueued) {
      logger.warning("Could not process NZP-CSI PDU: {:s}", config);
    }
    return is_enqueued;
  }

  // See interface for documentation.
  bool configure_resource_grid(const resource_grid_context& context, resource_grid& grid) override
  {
    logger.set_context(context.slot.sfn(), context.slot.slot_index());

    bool is_enqueued = downlink_proc->configure_resource_grid(context, grid);

    if (!is_enqueued) {
      logger.warning(
          "The resource grid could not be configured. Either the queue is full or the DL proccessor is not in "
          "idle state.");
    }
    return is_enqueued;
  }
  // See interface for documentation.
  void finish_processing_pdus() override { downlink_proc->finish_processing_pdus(); }

private:
  std::unique_ptr<downlink_processor> downlink_proc;
  srslog::basic_logger&               logger;
};
} // namespace srsran
