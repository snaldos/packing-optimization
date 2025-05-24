#include "BatchStateManager.h"

BatchStateManager::BatchStateManager(std::vector<Pallet> &pallets, Truck &truck)
    : identifier(), batch_data_manager(pallets, truck, identifier),
      batch_input_manager(pallets, truck, identifier) {}

void BatchStateManager::update_state() {
  BatchState state = BatchState::SelectDataset;
  while (true) {
    switch (state) {
    case BatchState::RunAlgorithms:
      batch_input_manager.processInput();
      break;
    case BatchState::SelectDataset:
      batch_data_manager.select_and_load_dataset();
      if (batch_data_manager.get_pallets().empty()) {
        std::cout << "\nNo pallets loaded. Exiting...\n";
        return;
      }
      break;
    case BatchState::ShowDataset:
      batch_data_manager.show_dataset();
      break;
    case BatchState::SelectTimeout:
      batch_input_manager.select_timeout();
      break;
    case BatchState::Exit:
      return;
    default:
      break;
    }
    state = batch_input_manager.getInputMode();
  }
}
