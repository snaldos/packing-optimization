#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "location.h"

class Route {
 private:
  std::string source;
  std::string destination;
  std::vector<std::string> location_codes;
  double weight;

 public:
  /** @brief constructor 
   * Complexity: O(1)
  */
  Route();
  Route(const std::string& source, const std::string& destination,
        const std::vector<std::string>& location_codes, const double weight);

  /** @brief getters 
   * Complexity: O(1)
  */
  const std::string& get_source() const;
  const std::string& get_destination() const;
  const std::vector<std::string>& get_location_codes() const;
  double get_weight() const;

  // Assignment operator
  Route& operator=(const Route& other);

  // Generate a human-readable report
  std::string generate_report(
      std::string route_type,
      const std::unordered_map<std::string, Location>& code_location_map) const;
};

#endif