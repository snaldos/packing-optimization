// BatchProcessor.h
#ifndef BATCH_PROCESSOR_H
#define BATCH_PROCESSOR_H

#include <string>
#include <vector>

#include "../PalletPacking/DataStructures/Pallet.h"
#include "../PalletPacking/DataStructures/Truck.h"

class BatchProcessor {
 public:
  BatchProcessor(std::vector<Pallet> pallets, Truck truck);

  void start();

 private:
  std::vector<Pallet> pallets;
  Truck truck;
  void clearTerminal();
};

#endif
