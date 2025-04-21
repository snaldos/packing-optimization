#ifndef TRUCK_H
#define TRUCK_H

class Truck {
private:
  int capacity;
  int num_pallets;

public:
 Truck();  // Default constructor
 Truck(int capacity, int num_pallets);

 int get_capacity() const;
 int get_num_pallets() const;

 void set_capacity(int capacity);        // Setter for capacity
 void set_num_pallets(int num_pallets);  // Setter for num_pallets
};

#endif
