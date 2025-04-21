#include "Pallet.h"

Pallet::Pallet(int id, int weight, int profit)
    : id(id), weight(weight), profit(profit) {}

int Pallet::get_id() const {
  return id;
}

int Pallet::get_weight() const {
  return weight;
}

int Pallet::get_profit() const {
  return profit;
}
