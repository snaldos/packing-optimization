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
 * datasets, and changing timeouts.
 */
class BatchStateManager {
 public:
   /**
    * @brief Constructs a BatchStateManager with references to the main data
    * structures.
    * @param pallets Reference to the vector of pallets
    * @param truck Reference to the truck object
    */
   BatchStateManager(std::vector<Pallet> &pallets, Truck &truck);

   /**
    * @brief Main loop to update and handle the current batch state.
    */
   void update_state();

 private:
   BatchDataSetManager
       batch_data_manager; ///< Manages dataset loading and display
   BatchInputManager
       batch_input_manager; ///< Handles user input and algorithm selection
};

#endif // BATCH_STATE_MANAGER_H
