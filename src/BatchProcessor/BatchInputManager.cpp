#include "BatchInputManager.h"

BatchInputManager::BatchInputManager(std::vector<Pallet> pallets, Truck truck)
    : pallets(pallets), truck(truck) {};

int BatchInputManager::getInputMode() {
  // BatchUtils::clearTerminal();
  std::cout << "Choose input mode:" << std::endl
            << "1: Terminal Input" << std::endl
            << "2: File Input\n"
            << std::endl
            << "0: back" << std::endl
            << "3: exit" << std::endl;
  while (true) {
    int choice_mode;
    std::string input_mode;
    std::getline(std::cin, input_mode);

    try {
      choice_mode = std::stoi(input_mode);
    } catch (const std::invalid_argument &e) {
      std::cerr << "ERROR: Input MUST be a number." << std::endl;
      continue;
    }

    switch (choice_mode) {
      case 1:
        BatchUtils::clearTerminal();
        // initial message
        std::cout << "--> TERMINAL INPUT <--\n\n"
                     "INPUT FORMAT\n"
                     "<REQUIRED>\n"

                     "<OPTIONAL>\n"
                     "\n\n"
                     "Enter input (end with an empty line):"
                  << std::endl;
        processInput(std::cin, std::cout);
        return 0;
      case 2: {
        BatchUtils::clearTerminal();
        // INITIAL MESSAGE
        std::cout << "--> FILE INPUT <--\n\n"
                     "The file MUST be located in the project input folder.\n"
                     "Enter the filename:"
                  << std::endl;

        // gets file
        std::string input;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        std::string filename;
        if (iss >> filename) {
          std::cerr << "ERROR: Invalid filename." << std::endl;
          return -1;
        }

        filename = ParserUtils::trim(filename);
        if (filename.empty()) {
          std::cerr << "ERROR: Filename cannot be empty." << std::endl;
          return -1;
        }
        std::string input_filename = "input/" + filename;
        // Check if the file exists
        std::ifstream input_file(input_filename);
        if (!input_file) {
          std::cerr << "ERROR: File does not exist." << std::endl;
          return -1;
        }

        if (input_file.is_open()) {
          // Project root directory defined by CMake
          std::string project_root = PROJECT_DIR;

          // Ensure output directory exists
          std::string output_dir = project_root + "/output/";
          if (!BatchUtils::ensureDirectory(output_dir)) return -1;

          std::string output_filename = output_dir + filename;
          std::ofstream output_file(output_filename);
          if (output_file.is_open()) {
            processInput(input_file, output_file);
            output_file.close();
          } else {
            std::cerr << "ERROR: Could not open output file: "
                      << output_filename << std::endl;
            processInput(input_file, std::cerr);
          }
          input_file.close();
        } else {
          std::cerr << "ERROR: Could not open input file: " << input_filename
                    << std::endl;
        }
        return 0;
      }
      case 3:
        return -1;

      case 0:
        return 1;
      default:
        std::cerr << "ERROR: Invalid input mode." << std::endl;
        break;
    }
  }
}

void BatchInputManager::processInput(std::istream &input_stream,
                                     std::ostream &output_stream) {}
