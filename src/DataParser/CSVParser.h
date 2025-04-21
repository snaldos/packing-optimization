#ifndef DISTANCE_PARSER_H
#define DISTANCE_PARSER_H

#include <vector>
#include <string>
#include "../PalletPacking/DataStructures/Pallet.h"
#include "../PalletPacking/DataStructures/Truck.h"

class CSVParser {
 public:
  CSVParser() = default;

  void parse(const std::string& pallets_file, const std::string& truck_file,
             std::vector<Pallet>& pallets, Truck& truck);

  ~CSVParser() = default;

 private:
  void parse_pallets(const std::string& filename, std::vector<Pallet>& pallets);
  void parse_truck(const std::string& filename, Truck& truck);
};

#endif
