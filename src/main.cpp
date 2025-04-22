

#include "Batch/BatchProcessor.h"
#include "DataStructures/Pallet.h"
#include "DataStructures/Truck.h"

int main() {
  std::vector<Pallet> pallets;
  Truck truck;

  // Initialize batch processor
  BatchProcessor batch_processor(pallets, truck);
  batch_processor.start();
  return 0;
}
