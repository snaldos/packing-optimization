#ifndef PALLET_H
#define PALLET_H

#include <string>
class Pallet {
private:
 std::string id;
 int weight;
 int profit;

public:
 Pallet(std::string, int weight, int profit);

 std::string get_id() const;
 int get_weight() const;
 int get_profit() const;
};

#endif
