

#include "BatchProcessor/BatchProcessor.h"
#include "PalletPacking/DataStructures/Pallet.h"
#include "PalletPacking/DataStructures/Truck.h"

int main() {
  std::vector<Pallet> pallets;
  Truck truck;

  // Initialize batch processor
  BatchProcessor batch_processor(pallets, truck);
  batch_processor.start();
  return 0;
}
