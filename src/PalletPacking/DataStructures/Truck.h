#ifndef TRUCK_H
#define TRUCK_H

class Truck {
private:
  int capacity;
  int num_pallets;

public:
  Truck(int capacity, int num_pallets);

  int get_capacity() const;
  int get_num_pallets() const;
};

#endif
