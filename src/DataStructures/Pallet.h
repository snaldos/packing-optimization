#ifndef PALLET_H
#define PALLET_H

#include <string>
class Pallet {
private:
 std::string id;
 unsigned int weight;
 int profit;

public:
 Pallet(std::string, unsigned int weight, int profit);

 std::string get_id() const;
 int unsigned get_weight() const;
 int get_profit() const;
};

#endif
