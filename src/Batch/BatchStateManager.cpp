#include "BatchStateManager.h"

BatchStateManager::BatchStateManager(std::vector<Pallet> pallets, Truck truck)
    : batch_data_manager(pallets, truck),
      batch_input_manager(pallets, truck) {};

void BatchStateManager::update_state() {
  BatchState state = BatchState::SelectDataset;
  while (true) {
    switch (state) {
      case BatchState::TerminalInput:
        batch_input_manager.processInput(std::cin, std::cout);
        break;
      case BatchState::FileInput:
        batch_input_manager.processFileInput();
        break;
      case BatchState::SelectDataset:
        batch_data_manager.selectAndLoadDataset();
        break;
      case BatchState::ShowDataset:
        batch_data_manager.showDataset();
        break;
      case BatchState::Exit:
        return;
      default:
        break;
    }
    state = batch_input_manager.getInputMode();
  }
}
