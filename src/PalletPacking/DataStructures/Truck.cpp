#include "Truck.h"

Truck::Truck() : capacity(0), num_pallets(0) {}

Truck::Truck(int capacity, int num_pallets)
    : capacity(capacity), num_pallets(num_pallets) {}

int Truck::get_capacity() const { return capacity; }

int Truck::get_num_pallets() const { return num_pallets; }

void Truck::set_capacity(int capacity) { this->capacity = capacity; }

void Truck::set_num_pallets(int num_pallets) {
  this->num_pallets = num_pallets;
}
