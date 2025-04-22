#include "BatchUtils.h"

#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>

namespace BatchUtils {
void clearTerminal() {
  std::cout << "\033[2J\033[H" << std::flush;
  std::cout << "----- PACKING OPTIMIZATION -----\n\n";
}

bool ensureDirectory(const std::string& dir) {
  struct stat info;
  if (stat(dir.c_str(), &info) != 0) {
    // Directory does not exist, create it
    if (mkdir(dir.c_str(), 0777) == -1) {
      std::cerr << "ERROR: Could not create directory: " << dir << std::endl;
      return false;
    }
  } else if (!(info.st_mode & S_IFDIR)) {
    // Path exists but is not a directory
    std::cerr << "ERROR: Path exists but is not a directory: " << dir
              << std::endl;
    return false;
  }
  return true;
}

int getMenuChoice(const std::vector<std::string>& options, const std::string& prompt) {
  while (true) {
    clearTerminal();
    for (size_t i = 0; i < options.size(); ++i) {
      std::cout << i + 1 << ": " << options[i] << "\n";
    }
    std::cout << prompt;

    std::string input;
    std::getline(std::cin, input);
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
