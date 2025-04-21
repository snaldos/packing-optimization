#ifndef PALLET_H
#define PALLET_H

class Pallet {
private:
  int id;
  int weight;
  int profit;

public:
  Pallet(int id, int weight, int profit);

  int get_id() const;
  int get_weight() const;
  int get_profit() const;
};

#endif
