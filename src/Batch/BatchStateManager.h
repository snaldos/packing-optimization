// BatchStateManager.h
#ifndef BATCH_PROCESSOR_H
#define BATCH_PROCESSOR_H

#include <string>
#include <vector>

#include "../DataStructures/Pallet.h"
#include "../DataStructures/Truck.h"
#include "BatchDataSetManager.h"
#include "BatchInputManager.h"

class BatchStateManager {
 public:
  BatchStateManager(std::vector<Pallet> pallets, Truck truck);

  void update_state();

 private:
  BatchDataSetManager batch_data_manager;
  BatchInputManager batch_input_manager;
};

#endif
