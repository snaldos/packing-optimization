#ifndef LOCATION_H
#define LOCATION_H

#include <string>
/**
 * @param name the name of the city location.
 * @param id the number id used to identify the location.
 * @param code the code string used to identify the location.
 * @param has_parking location has at least one parking spot if true.
 */
class Location {
 private:
  std::string name;
  std::string id;
  std::string code;
  bool has_parking;

 public:
  /** @brief constructor 
   * Complexity: O(1)
  */
  Location() = default;
  Location(const std::string& name, const std::string& id,
           const std::string& code, bool has_parking);

  /** @brief getters
   * Complexity: O(1)
  */
  const std::string& get_name() const;
  const std::string& get_id() const;
  const std::string& get_code() const;
  bool get_has_parking() const;

  // for debugging
  std::string to_string() const;

  // comparison operators
  bool operator==(const Location& other) const;
};

#endif