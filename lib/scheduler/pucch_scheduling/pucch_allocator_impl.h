/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "../cell/resource_grid.h"
#include "../config/ue_configuration.h"
#include "pucch_allocator.h"
#include "pucch_resource_manager.h"
#include "srsran/scheduler/scheduler_dci.h"
#include <variant>

namespace srsran {

/// Implementation of the PUCCH allocator interface.
class pucch_allocator_impl final : public pucch_allocator
{
public:
  explicit pucch_allocator_impl(const cell_configuration& cell_cfg_,
                                unsigned                  max_pucchs_per_slot,
                                unsigned                  max_ul_grants_per_slot_);

  ~pucch_allocator_impl() override;

  /// Updates the internal slot_point and tracking of PUCCH resource usage; and resets the PUCCH common allocation grid.
  void slot_indication(slot_point sl_tx) override;

  std::optional<unsigned> alloc_common_pucch_harq_ack_ue(cell_resource_allocator&    res_alloc,
                                                         rnti_t                      tcrnti,
                                                         unsigned                    k0,
                                                         unsigned                    k1,
                                                         const pdcch_dl_information& dci_info) override;

  std::optional<unsigned> alloc_common_and_ded_harq_res(cell_resource_allocator&     res_alloc,
                                                        rnti_t                       rnti,
                                                        const ue_cell_configuration& ue_cell_cfg,
                                                        unsigned                     k0,
                                                        unsigned                     k1,
                                                        const pdcch_dl_information&  dci_info) override;

  std::optional<unsigned> alloc_ded_pucch_harq_ack_ue(cell_resource_allocator&     res_alloc,
                                                      rnti_t                       crnti,
                                                      const ue_cell_configuration& ue_cell_cfg,
                                                      unsigned                     k0,
                                                      unsigned                     k1) override;

  void pucch_allocate_sr_opportunity(cell_slot_resource_allocator& slot_alloc,
                                     rnti_t                        crnti,
                                     const ue_cell_configuration&  ue_cell_cfg) override;

  void pucch_allocate_csi_opportunity(cell_slot_resource_allocator& pucch_slot_alloc,
                                      rnti_t                        crnti,
                                      const ue_cell_configuration&  ue_cell_cfg,
                                      unsigned                      csi_part1_nof_bits) override;

  pucch_uci_bits remove_ue_uci_from_pucch(cell_slot_resource_allocator& slot_alloc,
                                          rnti_t                        crnti,
                                          const ue_cell_configuration&  ue_cell_cfg) override;

  [[nodiscard]] bool has_common_pucch_grant(rnti_t rnti, slot_point sl_tx) const override;

private:
  /// ////////////  Helper struct and classes   //////////////

  // Structs with the info about the PUCCH resources.
  struct pucch_res_alloc_cfg {
    // True if the struct has a valid config.
    unsigned   pucch_res_indicator;
    grant_info first_hop_res;
    // Contains grant only if intra-slot freq-hopping is active.
    grant_info second_hop_res;
    // Cyclic-shift.
    unsigned cs;
    // PUCCH format.
    pucch_format format;
  };

  struct pucch_common_params {
    unsigned pucch_res_indicator;
    unsigned r_pucch;
  };

  // At the moment, we only supports PUCCH resource set index 0 and 1.
  enum class pucch_res_set_idx : uint8_t { set_0 = 0, set_1 };

  struct harq_res_id {
    pucch_res_set_idx pucch_set_idx = pucch_res_set_idx::set_0;
    uint8_t           pucch_res_ind = 0;
  };

  /// Defines the type of resource.
  /// HARQ indicates the HAR-ACK resource (it can carry HARQ-ACK and/or SR and/or CSI bits).
  /// SR indicates the resource dedicated for SR (it can carry SR and HARQ-ACK bits).
  /// CSI indicates the resource dedicated for CSI (it can carry CSI and SR bits).
  enum class pucch_grant_type { harq_ack, sr, csi };

  /// \brief Defines a PUCCH grant (and its relevant information) currently allocated to a given UE.
  /// It is used internally to keep track of the UEs' allocations of the PUCCH grants with dedicated resources.
  class pucch_grant
  {
  public:
    pucch_grant_type type;
    // Only relevant for HARQ-ACK resources.
    harq_res_id           harq_id;
    pucch_uci_bits        bits;
    const pucch_resource* pucch_res_cfg = nullptr;

    [[nodiscard]] pucch_format get_format() const
    {
      return pucch_res_cfg != nullptr ? pucch_res_cfg->format : pucch_format::NOF_FORMATS;
    }
    [[nodiscard]] ofdm_symbol_range get_symbols() const;
  };

  /// \brief List of possible PUCCH grants that allocated to a UE, at a given slot.
  class pucch_grant_list
  {
  public:
    std::optional<pucch_grant> harq_resource;
    std::optional<pucch_grant> sr_resource;
    std::optional<pucch_grant> csi_resource;
    unsigned                   nof_grants = 0;

    [[nodiscard]] pucch_uci_bits get_uci_bits() const;
    [[nodiscard]] bool           is_emtpy() const;
  };

  /// Keeps track of the PUCCH grants (common + dedicated) for a given UE.
  struct ue_grants {
    rnti_t rnti;
    // Information about the common PUCCH grant.
    bool has_common_pucch = false;
    // List of PUCCH grants with dedicated resources.
    pucch_grant_list pucch_grants;
  };

  using slot_pucch_grants = static_vector<ue_grants, MAX_PUCCH_PDUS_PER_SLOT>;

  /// ////////////  Main private functions   //////////////

  // Allocates the PUCCH (common) resource for HARQ-(N)-ACK.
  std::optional<pucch_res_alloc_cfg> alloc_pucch_common_res_harq(cell_slot_resource_allocator&  pucch_alloc,
                                                                 const dci_context_information& dci_info);

  void compute_pucch_common_params_and_alloc(cell_slot_resource_allocator& pucch_alloc,
                                             rnti_t                        rnti,
                                             pucch_common_params           pucch_params);

  std::optional<pucch_common_params> find_common_and_ded_harq_res_available(cell_slot_resource_allocator& pucch_alloc,
                                                                            ue_grants& existing_grants,
                                                                            rnti_t     rnti,
                                                                            const ue_cell_configuration&   ue_cell_cfg,
                                                                            const dci_context_information& dci_info);

  // Helper that allocates a NEW PUCCH HARQ grant (Format 0 or 1).
  std::optional<unsigned> allocate_harq_grant(cell_slot_resource_allocator& pucch_slot_alloc,
                                              rnti_t                        crnti,
                                              const ue_cell_configuration&  ue_cell_cfg);

  // Helper that allocates a new PUCCH HARQ grant (Format 2/3/4) for CSI.
  void allocate_csi_grant(cell_slot_resource_allocator& pucch_slot_alloc,
                          rnti_t                        crnti,
                          const ue_cell_configuration&  ue_cell_cfg,
                          unsigned                      csi_part1_bits);

  // Implements the main steps of the multiplexing procedure as defined in TS 38.213, Section 9.2.5.
  std::optional<unsigned> multiplex_and_allocate_pucch(cell_slot_resource_allocator& pucch_slot_alloc,
                                                       pucch_uci_bits                new_bits,
                                                       ue_grants&                    current_grants,
                                                       const ue_cell_configuration&  ue_cell_cfg,
                                                       bool                          preserve_res_indicator = false);

  // Computes which resources are expected to be sent, depending on the UCI bits to be sent, before any multiplexing.
  std::optional<pucch_grant_list> get_pucch_res_pre_multiplexing(slot_point                   sl_tx,
                                                                 pucch_uci_bits               new_bits,
                                                                 ue_grants                    ue_current_grants,
                                                                 const ue_cell_configuration& ue_cell_cfg);

  // Execute the multiplexing algorithm as defined in TS 38.213, Section 9.2.5.
  pucch_grant_list multiplex_resources(slot_point                   sl_tx,
                                       rnti_t                       crnti,
                                       pucch_grant_list             candidate_grants,
                                       const ue_cell_configuration& ue_cell_cfg,
                                       bool                         preserve_res_indicator = false);

  // Applies the multiplexing rules depending on the PUCCH resource format, as per TS 38.213, Section 9.2.5.1/2.
  std::optional<pucch_grant> merge_pucch_resources(span<const pucch_grant> resources_to_merge,
                                                   slot_point              slot_harq,
                                                   rnti_t                  crnti,
                                                   const pucch_config&     pucch_cfg,
                                                   bool                    preserve_res_indicator = false);

  // Allocate the PUCCH PDUs in the scheduler output, depending on the new PUCCH grants to be transmitted, and depending
  // on the PUCCH PDUs currently allocated.
  std::optional<unsigned> allocate_grants(cell_slot_resource_allocator& pucch_slot_alloc,
                                          ue_grants&                    existing_pucchs,
                                          rnti_t                        crnti,
                                          pucch_grant_list              grants_to_tx,
                                          const ue_cell_configuration&  ue_cell_cfg);

  // Fills the PUCCH HARQ PDU for common resources.
  void fill_pucch_harq_common_grant(pucch_info& pucch_info, rnti_t rnti, const pucch_res_alloc_cfg& pucch_res);

  // Fills the PUCCH Format 1 PDU.
  void fill_pucch_ded_format1_grant(pucch_info&           pucch_grant,
                                    rnti_t                crnti,
                                    const pucch_resource& pucch_ded_res_cfg,
                                    unsigned              harq_ack_bits,
                                    sr_nof_bits           sr_bits);

  // Fills the PUCCH Format 2 PDU.
  void fill_pucch_format2_grant(pucch_info&                  pucch_grant,
                                rnti_t                       crnti,
                                const pucch_resource&        pucch_ded_res_cfg,
                                const ue_cell_configuration& ue_cell_cfg,
                                unsigned                     nof_prbs,
                                unsigned                     harq_ack_bits,
                                sr_nof_bits                  sr_bits,
                                unsigned                     csi_part1_bits);

  /// ////////////  Private helpers   //////////////

  void remove_unsed_pucch_res(slot_point                   sl_tx,
                              pucch_grant_list             grants_to_tx,
                              ue_grants&                   existing_pucchs,
                              const ue_cell_configuration& ue_cell_cfg);

  unsigned get_max_pucch_grants(unsigned currently_allocated_puschs);

  // \brief Ring of PUCCH allocations indexed by slot.
  circular_array<slot_pucch_grants, cell_resource_allocator::RING_ALLOCATOR_SIZE> pucch_grants_alloc_grid;

  constexpr static unsigned     PUCCH_FORMAT_1_NOF_PRBS{1};
  const cell_configuration&     cell_cfg;
  const unsigned                max_pucch_grants_per_slot;
  const unsigned                max_ul_grants_per_slot;
  slot_point                    last_sl_ind;
  pucch_resource_manager        resource_manager;

  srslog::basic_logger& logger;
};

} // namespace srsran
