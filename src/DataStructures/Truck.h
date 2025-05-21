#ifndef TRUCK_H
#define TRUCK_H

/**
 * @class Truck
 * @brief Represents a truck with a given capacity and number of pallets.
 *
 * Used as the container for the knapsack problem, specifying the maximum weight
 * (capacity) and the number of pallets it can carry.
 */
class Truck {
private:
  unsigned int capacity;    ///< Maximum weight capacity of the truck
  unsigned int num_pallets; ///< Number of pallets the truck can carry

public:
  /**
   * @brief Default constructor. Initializes capacity and num_pallets to 0.
   */
  Truck();
  /**
   * @brief Constructs a Truck with specified capacity and number of pallets.
   * @param capacity Maximum weight capacity
   * @param num_pallets Number of pallets
   */
  Truck(unsigned int capacity, unsigned int num_pallets);

  /**
   * @brief Gets the truck's maximum weight capacity.
   * @return Capacity in weight units
   */
  unsigned int get_capacity() const;
  /**
   * @brief Gets the number of pallets the truck can carry.
   * @return Number of pallets
   */
  unsigned int get_num_pallets() const;

  /**
   * @brief Sets the truck's maximum weight capacity.
   * @param capacity Maximum weight capacity
   */
  void set_capacity(unsigned int capacity);
  /**
   * @brief Sets the number of pallets the truck can carry.
   * @param num_pallets Number of pallets
   */
  void set_num_pallets(unsigned int num_pallets);
};

#endif  // TRUCK_H
