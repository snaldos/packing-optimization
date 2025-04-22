#include "BatchInputManager.h"

BatchInputManager::BatchInputManager(std::vector<Pallet> pallets, Truck truck)
    : pallets(pallets), truck(truck) {};

BatchState BatchInputManager::getInputMode() {
  std::vector<std::string> options = {"Terminal Input", "File Input",
                                      "Select Dataset", "Show Dataset", "Exit"};
  int choice = BatchUtils::getMenuChoice(options, "Choose input mode: ");

  switch (choice) {
    case 1:
      BatchUtils::clearTerminal();
      return BatchState::TerminalInput;
    case 2:
      return BatchState::FileInput;
    case 3:
      return BatchState::SelectDataset;
    case 4:
      return BatchState::ShowDataset;
    case 5:
      return BatchState::Exit;
    default:
      return BatchState::Exit;  // Fallback
  }
}

void BatchInputManager::processFileInput() {
  BatchUtils::clearTerminal();
  while (true) {
    std::cout << "--> FILE INPUT <--\n\n"
                 "Enter the filename (located in the input folder):\n";
    std::string filename;
    std::getline(std::cin, filename);
    filename = ParserUtils::trim(filename);

    if (filename.empty()) {
      BatchUtils::clearTerminal();
      std::cerr << "ERROR: Filename cannot be empty.\n";
      continue;
    }

    std::ifstream input_file("input/" + filename);
    if (!input_file.is_open()) {
      BatchUtils::clearTerminal();
      std::cerr << "ERROR: File does not exist.\n";
      continue;
    }
    std::ofstream output_file("output/" + filename);
    if (output_file.is_open()) {
      processInput(input_file, output_file);
      output_file.close();
    } else {
      BatchUtils::clearTerminal();
      std::cerr << "ERROR: Could not open output file.\n";
      processInput(input_file, std::cerr);
    }
    input_file.close();
    break;
  }
}

void BatchInputManager::processInput(std::istream &input_stream,
                                     std::ostream &output_stream) {
  BatchUtils::clearTerminal();
  std::cout << "--> TERMINAL INPUT <--\n\n"
               "Enter input (end with an empty line):\n";
  while (true) {
    std::string input;
    std::getline(std::cin, input);
    input = ParserUtils::trim(input);

    if (input.empty()) {
      break;
      continue;
    }
  }
}
