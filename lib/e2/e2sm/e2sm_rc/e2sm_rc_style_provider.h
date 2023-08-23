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

#include "srsran/adt/byte_buffer.h"
#include "srsran/asn1/asn1_utils.h"
#include "srsran/asn1/e2ap/e2ap.h"
#include "srsran/asn1/e2ap/e2sm_rc.h"
#include "srsran/e2/e2sm/e2sm.h"
#include <map>
namespace srsran {

struct action_parameter_t {
  uint32_t    id;
  std::string name;
};

class e2sm_rc_action_provider
{
public:
  e2sm_rc_action_provider(std::string name_) : name(name_) {}
  e2sm_rc_action_provider(const e2sm_rc_action_provider& other) : name(other.name), action_params(other.action_params)
  {
  }

  void        add_parameter_support(uint32_t id, std::string param_name) { action_params[id] = {id, param_name}; }
  std::string name;
  std::map<uint32_t, action_parameter_t> action_params;
};

class e2sm_rc_style_provider
{
public:
  e2sm_rc_style_provider(std::string name_) : name(name_) {}
  e2sm_rc_style_provider(const e2sm_rc_style_provider& other) :
    name(other.name), action_providers(other.action_providers)
  {
  }
  void add_action_provider(uint16_t id, const e2sm_rc_action_provider& provider)
  {
    action_providers.emplace(id, e2sm_rc_action_provider(provider));
  }
  std::string                                 name;
  std::map<uint16_t, e2sm_rc_action_provider> action_providers;
};

class e2sm_rc_provider
{
public:
  e2sm_rc_provider(std::string name_) : name(name_) {}
  e2sm_rc_provider(const e2sm_rc_provider& other) : name(other.name), style_providers(other.style_providers) {}
  void add_style_provider(uint32_t id, e2sm_rc_style_provider provider)
  {
    style_providers.emplace(id, e2sm_rc_style_provider(provider));
  }
  std::string                                name;
  std::map<uint32_t, e2sm_rc_style_provider> style_providers;
};

} // namespace srsran