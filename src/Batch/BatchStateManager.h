// BatchStateManager.h
#ifndef BATCH_STATE_MANAGER_H
#define BATCH_STATE_MANAGER_H

#include <string>
#include <vector>

#include "../DataStructures/Pallet.h"
#include "../DataStructures/Truck.h"
#include "BatchDataSetManager.h"
#include "BatchInputManager.h"

/**
 * @class BatchStateManager
 * @brief Manages the state transitions for batch mode user interaction.
 *
 * Handles the main loop for selecting datasets, running algorithms, showing
 * datasets, and changing timeouts. Owns a shared dataset identifier string,
 * which is passed by reference to both BatchDataSetManager and
 * BatchInputManager, ensuring both always see the up-to-date identifier.
 */
class BatchStateManager {
public:
  /**
   * @brief Constructs a BatchStateManager with references to the main data
   * structures and creates a shared dataset identifier.
   * @param pallets Reference to the vector of pallets
   * @param truck Reference to the truck object
   *
   * The shared identifier is passed by reference to both managers, so any
   * update is immediately visible to all.
   */
  BatchStateManager(std::vector<Pallet> &pallets, Truck &truck);

  /**
   * @brief Main loop to update and handle the current batch state.
   */
  void update_state();

private:
  std::string identifier; ///< Current dataset identifier (shared by managers)
  BatchDataSetManager batch_data_manager;
  BatchInputManager batch_input_manager;
};

#endif // BATCH_STATE_MANAGER_H
