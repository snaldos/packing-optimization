#ifndef BATCH_INPUT_MANAGER_H
#define BATCH_INPUT_MANAGER_H

#include <sys/stat.h>
#include <sys/types.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../Algorithms/APPROX/Greedy.h"
#include "../Algorithms/BB/BranchAndBound.h"
#include "../Algorithms/BF/BruteForce.h"
#include "../Algorithms/DP/DynamicProgramming.h"
#include "../Algorithms/ILP/ILPBridgePy.h"
#include "../Algorithms/ILP/IntegerLinearProgramming.h"
#include "../DataStructures/Pallet.h"
#include "../DataStructures/Truck.h"
#include "../Parser/ParserUtils.h"
#include "../Utils.h"
#include "BatchState.h"
#include "BatchUtils.h"

/**
 * @class BatchInputManager
 * @brief Handles user input, algorithm selection, and output file generation in
 * batch mode.
 *
 * Provides menu-driven interaction for running algorithms, selecting datasets,
 * changing timeouts, and saving results.
 */
class BatchInputManager {
 private:
   /**
    * @brief Generates an output file with the results of an algorithm run.
    * @param filename Name of the output file
    * @param used_pallets Vector of selected pallets
    * @param max_profit Maximum profit achieved
    * @param message Status and timing info
    */
   void generate_output_file(std::string &filename,
                             std::vector<Pallet> &used_pallets,
                             unsigned int &max_profit, std::string &message);
   std::vector<Pallet> &pallets; ///< Reference to the vector of pallets
   Truck &truck;                 ///< Reference to the truck object
   unsigned int timeout_ms =
       60000; ///< Timeout in milliseconds (default 1 minute)
   std::string &identifier; ///< Reference to the shared dataset identifier

 public:
   /**
    * @brief Constructs a BatchInputManager with references to the main data
    * structures and a shared identifier.
    * @param pallets Reference to the vector of pallets
    * @param truck Reference to the truck object
    * @param identifier Reference to the shared dataset identifier
    */
   BatchInputManager(std::vector<Pallet> &pallets, Truck &truck,
                     std::string &identifier);

   /**
    * @brief Gets the current input mode/state from the user.
    * @return BatchState enum value representing the user's choice
    */
   BatchState getInputMode();

   /**
    * @brief Main loop for processing user input and running algorithms.
    */
   void processInput();

   /**
    * @brief Sets the timeout value in milliseconds.
    * @param ms Timeout in milliseconds
    */
   void set_timeout_ms(unsigned int ms) { timeout_ms = ms; }

   /**
    * @brief Gets the current timeout value in milliseconds.
    * @return Timeout in milliseconds
    */
   unsigned int get_timeout_ms() const { return timeout_ms; }

   /**
    * @brief Prompts the user to select a new timeout value.
    */
   void select_timeout();
};

#endif  // BATCH_INPUT_MANAGER_H
