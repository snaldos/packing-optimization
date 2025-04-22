// BatchProcessor.h
#ifndef BATCH_PROCESSOR_H
#define BATCH_PROCESSOR_H

#include <string>
#include <vector>

#include "../DataStructures/Pallet.h"
#include "../DataStructures/Truck.h"

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
