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

#include "srsran/radio/radio_session.h"
#include "srsran/support/executors/task_executor.h"
#include <memory>

namespace srsran {

/// Describes a radio session factory for a determined radio driver.
class radio_factory : public radio_base
{
public:
  /// Returns a reference to .
  virtual const radio_configuration::validator& get_configuration_validator() = 0;

  /// \brief Creates a new radio session with the given configuration parameters.
  /// \param[in] config Provides the configuration parameters.
  /// \param[in] task_executor Provides a task executor for executing asynchronous tasks.
  /// \param[in] notifier Provides radio event notifier interface.
  /// \return The ownership to a radio session if the session was successfully created.
  virtual std::unique_ptr<radio_session> create(const radio_configuration::radio& config,
                                                task_executor&                    async_task_executor,
                                                radio_notification_handler&       notifier) = 0;
};

/// \brief Creates a radio factory.
///
/// \param[in] driver_name Selects the type of radio factory for example \e uhd or \e zmq.
/// \return A valid radio factory if the provided driver name are valid.
std::unique_ptr<radio_factory> create_radio_factory(std::string driver_name);

/// \brief Helper function to print all available radio factories to stdout.
void print_available_radio_factories();

} // namespace srsran
