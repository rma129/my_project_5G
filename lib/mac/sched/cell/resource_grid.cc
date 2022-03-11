
#include "resource_grid.h"

using namespace srsgnb;

cell_resource_grid::cell_resource_grid(const cell_configuration& cfg_, slot_index_t sl_idx) :
  cfg(cfg_), slot_index(sl_idx), dl_prbs(cfg.nof_dl_prbs, 0, false), ul_prbs(cfg.nof_ul_prbs, 0, false)
{
  dl_grants.pci = cfg.pci;
  ul_grants.pci = cfg.pci;
}

void cell_resource_grid::reset()
{
  dl_prbs.reset();
  ul_prbs.reset();
  dl_grants = {};
  ul_grants = {};
}

/////////////////////////////////////////////////////////////////////////////

cell_resource_grid_pool::cell_resource_grid_pool(const cell_configuration& cfg_) : cfg(cfg_)
{
  slots_.reserve(RESOURCE_GRID_SIZE);
  for (unsigned i = 0; i < RESOURCE_GRID_SIZE; ++i) {
    slots_.push_back(cell_resource_grid{cfg, i % 10});
  }
}

void cell_resource_grid_pool::slot_indication(slot_point sl_tx)
{
  srsran_sanity_check(not last_slot_ind.valid() or last_slot_ind + 1 == sl_tx, "Slot indication was skipped");

  last_slot_ind = sl_tx;

  // Clear old slots
  slots_[(last_slot_ind + MINIMUM_SLOT_DIFF).to_uint() % RESOURCE_GRID_SIZE].reset();
}
