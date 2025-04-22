#include "Pallet.h"

Pallet::Pallet(std::string id, int weight, int profit)
    : id(id), weight(weight), profit(profit) {}

std::string Pallet::get_id() const { return id; }

int Pallet::get_weight() const {
  return weight;
}

int Pallet::get_profit() const {
  return profit;
}
