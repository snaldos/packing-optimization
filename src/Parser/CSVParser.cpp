#include "CSVParser.h"

#include <fstream>
#include <iostream>

#include "ParserUtils.h"

void CSVParser::parse(const std::string& pallets_file,
                      const std::string& truck_file,
                      std::vector<Pallet>& pallets, Truck& truck) {
  parse_pallets(pallets_file, pallets);
  parse_truck(truck_file, truck);
}

void CSVParser::parse_pallets(const std::string& filename,
                              std::vector<Pallet>& pallets) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  std::string line;
  // skip header line
  if (!std::getline(file, line)) {
    std::cerr << "Error: CSV file " << filename << " is empty." << std::endl;
    return;
  }

  while (std::getline(file, line)) {
    auto row = ParserUtils::split(line, ',');
    if (row.size() != 3) {
      std::cerr << "Warning: Skipping malformed line: " << line << std::endl;
      continue;
    }

    const std::string& pallet_id = row[0];
    const std::string& weight = row[1];
    const std::string& profit = row[2];

    if (!ParserUtils::is_number(pallet_id) || !ParserUtils::is_number(weight) ||
        !ParserUtils::is_number(profit)) {
      std::cerr << "Warning: Skipping line with non-integer values " << line
                << std::endl;
      continue;
    }

    int w = std::stoi(weight);
    int p = std::stoi(profit);

    if (w <= 0 || p <= 0) {
      std::cerr << "Warning: Skipping line with non-positive values " << line
                << std::endl;
      continue;
    }
    Pallet parsed_pallet = Pallet(pallet_id, w, p);
    pallets.push_back(parsed_pallet);
    std::cout << "Parsed pallet: " << pallet_id << ", weight: " << w
              << ", profit: " << p << std::endl;
  }

  file.close();
}

void CSVParser::parse_truck(const std::string& filename, Truck& truck) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  std::string line;
  // skip header line
  if (!std::getline(file, line)) {
    std::cerr << "Error: CSV file " << filename << " is empty." << std::endl;
    return;
  }

  while (std::getline(file, line)) {
    auto row = ParserUtils::split(line, ',');
    if (row.size() != 2) {
      std::cerr << "Warning: Skipping malformed line: " << line << std::endl;
      continue;
    }

    const std::string& capacity = row[0];
    const std::string& num_pallets = row[1];

    if (!ParserUtils::is_number(capacity) ||
        !ParserUtils::is_number(num_pallets)) {
      std::cerr << "Warning: Skipping line with non-integer values " << line
                << std::endl;
      continue;
    }

    int c = std::stoi(capacity);
    int p = std::stoi(num_pallets);

    if (c <= 0 || p <= 0) {
      std::cerr << "Warning: Skipping line with non-positive values " << line
                << std::endl;
      continue;
    }
    truck.set_capacity(c);
    truck.set_num_pallets(p);

    std::cout << "Parsed truck: capacity: " << c << ", pallets_num: " << p
              << std::endl;
  }

  file.close();
}
