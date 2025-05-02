#include "Pallet.h"

Pallet::Pallet(std::string id, unsigned int weight, int profit)
    : id(id), weight(weight), profit(profit) {}

std::string Pallet::get_id() const { return id; }

unsigned int Pallet::get_weight() const { return weight; }

int Pallet::get_profit() const { return profit; }
