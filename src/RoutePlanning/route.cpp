#include "route.h"

// Constructors

Route::Route() : source(""), destination(""), location_codes({}), weight(0) {}

Route::Route(const std::string& source, const std::string& destination,
             const std::vector<std::string>& location_codes,
             const double weight)
    : source(source), destination(destination), weight(weight) {
  // Deep copy the location codes
  this->location_codes = location_codes;
}

// Assignment operator
Route& Route::operator=(const Route& other) {
  if (this == &other) {
    return *this;  // Handle self-assignment
  }

  this->source = other.source;
  this->destination = other.destination;
  this->location_codes = other.location_codes;  // Deep copy the vector
  this->weight = other.weight;

  return *this;
}

// Getters
const std::string& Route::get_source() const { return this->source; }
const std::string& Route::get_destination() const { return this->destination; }
const std::vector<std::string>& Route::get_location_codes() const {
  return this->location_codes;
}
double Route::get_weight() const { return this->weight; }

// Generate a human-readable report
std::string Route::generate_report(
    std::string route_type,
    const std::unordered_map<std::string, Location>& code_location_map) const {
  std::string report = "";

  report += route_type + ":";

  if (this->location_codes.size() == 0) {
    report += "none\n";
    return report;
  }

  for (unsigned long i = 0; i < this->location_codes.size(); i++) {
    const std::string code = this->location_codes[i];
    std::string location_id = code_location_map.at(code).get_id();
    report += location_id;
    if (i < this->location_codes.size() - 1) {
      report += ",";
    }
  }
  report += "(" + std::to_string(static_cast<int>(this->weight)) + ")" + "\n";
  return report;
}