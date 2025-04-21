#include "Truck.h"

Truck::Truck(int capacity, int num_pallets)
    : capacity(capacity), num_pallets(num_pallets) {}

int Truck::get_capacity() const {
  return capacity;
}

int Truck::get_num_pallets() const {
  return num_pallets;
}
