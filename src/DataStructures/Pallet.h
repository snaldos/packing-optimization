#ifndef PALLET_H
#define PALLET_H

#include <string>

/**
 * @class Pallet
 * @brief Represents a pallet with an ID, weight, and profit value.
 *
 * Used as an item in the knapsack problem, where each pallet has a unique
 * identifier, a weight, and an associated profit.
 */
class Pallet {
private:
  std::string id;      ///< Unique identifier for the pallet
  unsigned int weight; ///< Weight of the pallet
  int profit;          ///< Profit value of the pallet

public:
  /**
   * @brief Constructs a Pallet with the given ID, weight, and profit.
   * @param id Unique identifier
   * @param weight Weight of the pallet
   * @param profit Profit value
   */
  Pallet(std::string id, unsigned int weight, int profit);

  /**
   * @brief Gets the unique identifier of the pallet.
   * @return Pallet ID as a string
   */
  std::string get_id() const;
  /**
   * @brief Gets the weight of the pallet.
   * @return Weight as an unsigned integer
   */
  unsigned int get_weight() const;
  /**
   * @brief Gets the profit value of the pallet.
   * @return Profit as an integer
   */
  int get_profit() const;
};

#endif  // PALLET_H
