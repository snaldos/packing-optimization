#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>
#include <vector>

#include "../DataStructures/Pallet.h"
#include "../DataStructures/Truck.h"

/**
 * @class CSVParser
 * @brief Parses CSV files to extract pallet and truck data.
 *
 * Provides methods to read and parse CSV files containing pallet and truck
 * information, populating vectors of Pallet objects and Truck objects for use
 * in algorithms.
 */
class CSVParser {
 public:
   /**
    * @brief Default constructor.
    */
   CSVParser() = default;

   /**
    * @brief Parses the given CSV files and populates the pallets and truck
    * objects.
    * @param pallets_file Path to the pallets CSV file
    * @param truck_file Path to the truck CSV file
    * @param pallets Output vector of Pallet objects
    * @param truck Output Truck object
    */
   void parse(const std::string &pallets_file, const std::string &truck_file,
              std::vector<Pallet> &pallets, Truck &truck);

   /**
    * @brief Default destructor.
    */
   ~CSVParser() = default;

 private:
   /**
    * @brief Parses the pallets CSV file and populates the pallets vector.
    * @param filename Path to the pallets CSV file
    * @param pallets Output vector of Pallet objects
    */
   void parse_pallets(const std::string &filename,
                      std::vector<Pallet> &pallets);

   /**
    * @brief Parses the truck CSV file and populates the truck object.
    * @param filename Path to the truck CSV file
    * @param truck Output Truck object
    */
   void parse_truck(const std::string &filename, Truck &truck);
};

#endif
