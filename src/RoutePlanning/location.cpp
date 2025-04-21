#include "location.h"

// constructor
Location::Location(const std::string& name, const std::string& id,
                   const std::string& code, bool has_parking)
    : name(name), id(id), code(code), has_parking(has_parking) {}

// getters
const std::string& Location::get_name() const { return name; }
const std::string& Location::get_id() const { return id; }
const std::string& Location::get_code() const { return code; }
bool Location::get_has_parking() const { return has_parking; }

// comparison operators
bool Location::operator==(const Location& other) const {
  return code == other.code;
}
