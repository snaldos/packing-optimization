#include "BatchProcessor.h"

#include "BatchDataSetManager.h"
#include "BatchInputManager.h"

BatchProcessor::BatchProcessor(std::vector<Pallet> pallets, Truck truck)
    : pallets(pallets), truck(truck) {};

void BatchProcessor::start() {
  BatchDataSetManager data_manager = BatchDataSetManager(pallets, truck);
  if (data_manager.selectAndLoadDataset() == -1) return;
  BatchInputManager input_manager = BatchInputManager(pallets, truck);
  if (input_manager.getInputMode() == 1) return start();
}
