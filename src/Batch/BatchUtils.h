#ifndef BATCH_UTILS_H
#define BATCH_UTILS_H

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace BatchUtils {
// Function to clear the terminal screen
inline void clearTerminal() {
  std::cout << "\033[2J\033[H" << std::flush;
  std::cout << "----- PACKING OPTIMIZATION -----\n\n";
}
// Function to ensure a directory exists
inline bool ensureDirectory(const std::string &dir) {
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

// Function to handle menu input
inline int getMenuChoice(int max_option) {
  while (true) {
    std::string input;
    std::getline(std::cin, input);
    try {
      int choice = std::stoi(input);
      if (choice >= 1 && choice <= max_option) return choice;
    } catch (...) {
      // Ignore invalid input
    }
    std::cerr << "ERROR: Invalid choice. Please enter a number between 1 and "
              << max_option << ".\n";
  }
}
}  // namespace BatchUtils
#endif  // BATCH_UTILS_H
