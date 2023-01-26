/*
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "scheduler_policy.h"

namespace srsgnb {

class scheduler_time_rr : public scheduler_policy
{
public:
  void dl_sched(const ue_resource_grid_view& res_grid,
                ue_pdsch_allocator&          pdsch_alloc,
                const ue_list&               ues,
                bool                         is_retx) override;

  void ul_sched(const ue_resource_grid_view& res_grid,
                ue_pusch_allocator&          pusch_alloc,
                const ue_list&               ues,
                bool                         is_retx) override;

private:
  unsigned rr_count = 0;
};

} // namespace srsgnb
