#include "Batch/BatchStateManager.h"
#include "DataStructures/Pallet.h"
#include "DataStructures/Truck.h"

int main() {
  std::vector<Pallet> pallets;
  Truck truck;

  // Initialize batch processor
  BatchStateManager batch_state_manager(pallets, truck);
  batch_state_manager.update_state();
  return 0;
}
