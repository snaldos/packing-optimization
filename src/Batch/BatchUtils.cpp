#include "BatchUtils.h"

namespace BatchUtils {
void clear_terminal() {
  std::cout << "\033[2J\033[H" << std::flush;
  std::cout << "----- PACKING OPTIMIZATION -----\n\n";
}

int get_menu_choice(const std::vector<std::string>& options,
                    const std::string& prompt) {
  while (true) {
    clear_terminal();
    for (size_t i = 0; i < options.size(); ++i) {
      std::cout << i + 1 << ": " << options[i] << "\n";
    }
    std::cout << std::endl << prompt;

    std::string input;
    std::getline(std::cin, input);

    // Exit if the user enters an empty line
    if (input.empty()) {
      return 0;  // Special value indicating exit
    }

    try {
      int choice = std::stoi(input);
      if (choice >= 1 && choice <= static_cast<int>(options.size())) {
        return choice;
      }
    } catch (...) {
      // Ignore invalid input
    }
    std::cerr << "ERROR: Invalid choice. Please enter a number between 1 and "
              << options.size() << ".\n";
  }
}
}  // namespace BatchUtils
