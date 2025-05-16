#ifndef TRUCK_H
#define TRUCK_H

class Truck {
private:
 unsigned int capacity;
 unsigned int num_pallets;

public:
 Truck();  // Default constructor
 Truck(unsigned int capacity, unsigned int num_pallets);

 unsigned int get_capacity() const;
 unsigned int get_num_pallets() const;

 void set_capacity(unsigned int capacity);        // Setter for capacity
 void set_num_pallets(unsigned int num_pallets);  // Setter for num_pallets
};

#endif  // TRUCK_H
