#ifndef BATCH_DATASET_MANAGER_H
#define BATCH_DATASET_MANAGER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../DataStructures/Pallet.h"
#include "../DataStructures/Truck.h"
#include "../Parser/CSVParser.h"
#include "../Parser/ParserUtils.h"
#include "../Utils.h"
#include "BatchUtils.h"

/**
 * @class BatchDataSetManager
 * @brief Manages loading, displaying, and tracking datasets for batch mode
 * operations.
 *
 * Handles user interaction for selecting datasets, loading CSV files, and
 * displaying current data.
 */
class BatchDataSetManager {
 public:
   /**
    * @brief Constructs a BatchDataSetManager with references to the main data
    * structures.
    * @param pallets Reference to the vector of pallets
    * @param truck Reference to the truck object
    */
   BatchDataSetManager(std::vector<Pallet> &pallets, Truck &truck);

   /**
    * @brief Prompts the user to select and load a dataset from available files.
    * @return 1 if a dataset was loaded, 0 otherwise
    */
   int select_and_load_dataset();

   /**
    * @brief Displays the currently loaded dataset (pallets and truck info).
    */
   void show_dataset();

   /**
    * @brief Returns a const reference to the loaded pallets vector.
    * @return Const reference to vector of pallets
    */
   const std::vector<Pallet> &get_pallets() const;

 private:
   /**
    * @brief Loads a dataset given an identifier (file suffix).
    * @param identifier Dataset identifier (e.g., "01")
    * @return True if dataset loaded successfully, false otherwise
    */
   bool load_dataset(std::string identifier);
   CSVParser csv_data_parser;      ///< CSV parser for reading data files
   std::vector<Pallet> &pallets;   ///< Reference to the vector of pallets
   Truck &truck;                   ///< Reference to the truck object
   std::string current_identifier; ///< Tracks the current dataset identifier
};

#endif  // BATCH_DATASET_MANAGER_H
