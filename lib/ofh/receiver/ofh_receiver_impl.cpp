/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "ofh_receiver_impl.h"
#include "srsran/ofh/ethernet/ethernet_properties.h"

using namespace srsran;
using namespace ofh;

/// Returns an Open Fronthaul uplink packet handler configuration from the given receiver implementation configuration.
static uplane_uplink_packet_handler_config get_packet_handler_config(const receiver_config&      config,
                                                                     receiver_impl_dependencies& depen)
{
  uplane_uplink_packet_handler_config out_cfg(*depen.logger, *depen.ul_cp_context_repo);
  out_cfg.is_prach_cp_enabled = config.is_prach_cp_enabled;
  out_cfg.ul_prach_eaxc       = config.prach_eaxc;
  out_cfg.ul_eaxc             = config.ul_eaxc;
  out_cfg.uplane_decoder      = std::move(depen.uplane_decoder);
  out_cfg.ecpri_decoder       = std::move(depen.ecpri_decoder);
  out_cfg.eth_frame_decoder   = std::move(depen.eth_frame_decoder);

  // VLAN configuration.
  out_cfg.vlan_params.eth_type        = ether::ECPRI_ETH_TYPE;
  out_cfg.vlan_params.tci             = config.tci;
  out_cfg.vlan_params.mac_dst_address = config.mac_dst_address;
  out_cfg.vlan_params.mac_src_address = config.mac_src_address;

  return out_cfg;
}

/// Returns an Open Fronthaul User-Plane uplink symbol manager configuration from the given receiver implementation
/// configuration and handlers.
static uplane_uplink_symbol_manager_config
get_uplink_symbol_manager_config(const receiver_config&                                 config,
                                 receiver_impl_dependencies&                            depen,
                                 uplane_uplink_packet_handler&                          packet_handler,
                                 const static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC>& ru_ul_eaxc,
                                 const static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC>& ru_prach_eaxc,
                                 rx_window_checker&                                     rx_window)
{
  uplane_uplink_symbol_manager_config out_cfg(*depen.logger,
                                              *depen.notifier,
                                              packet_handler,
                                              *depen.prach_context_repo,
                                              *depen.ul_slot_context_repo,
                                              ru_ul_eaxc,
                                              ru_prach_eaxc,
                                              rx_window);

  return out_cfg;
}

receiver_impl::receiver_impl(const receiver_config& config, receiver_impl_dependencies&& depen) :
  decompressor_sel(std::move(depen.decompressor_sel)),
  window_checker(*depen.logger,
                 config.rx_timing_params,
                 std::chrono::duration<double, std::nano>(
                     1e6 / (get_nsymb_per_slot(config.cp) * get_nof_slots_per_subframe(config.scs)))),
  ul_packet_handler(get_packet_handler_config(config, depen)),
  ul_symbol_manager(get_uplink_symbol_manager_config(config,
                                                     depen,
                                                     ul_packet_handler,
                                                     config.ul_eaxc,
                                                     config.prach_eaxc,
                                                     window_checker))
{
}

ether::frame_notifier& receiver_impl::get_ethernet_frame_notifier()
{
  return ul_symbol_manager;
}

ota_symbol_handler& receiver_impl::get_ota_symbol_handler()
{
  return window_checker;
}
