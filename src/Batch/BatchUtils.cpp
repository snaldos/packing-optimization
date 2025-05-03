#include "BatchUtils.h"

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace BatchUtils {
void clear_terminal() {
  std::cout << "\033[2J\033[H" << std::flush;
  std::cout << "----- PACKING OPTIMIZATION -----\n\n";
}

std::string get_output_dir() { return std::string(PROJECT_DIR) + "/output"; }

bool remove_directory(const std::string& path) {
  DIR* dir = opendir(path.c_str());
  if (!dir) return false;

  struct dirent* entry;
  while ((entry = readdir(dir)) != nullptr) {
    std::string name = entry->d_name;
    if (name == "." || name == "..") continue;

    std::string fullPath = path + "/" + name;
    struct stat info;
    if (stat(fullPath.c_str(), &info) == 0) {
      if (S_ISDIR(info.st_mode)) {
        if (!remove_directory(fullPath)) {
          closedir(dir);
          return false;
        }
      } else {
        if (unlink(fullPath.c_str()) == -1) {
          closedir(dir);
          return false;
        }
      }
    }
  }
  closedir(dir);
  return rmdir(path.c_str()) == 0;
}

bool ensure_directory(const std::string& dir) {
  struct stat info;
  if (stat(dir.c_str(), &info) == 0) {
    if (S_ISDIR(info.st_mode)) {
      // Directory exists, remove it
      if (!remove_directory(dir)) {
        std::cerr << "ERROR: Failed to remove existing directory: " << dir
                  << std::endl;
        return false;
      }
    } else {
      std::cerr << "ERROR: Path exists but is not a directory: " << dir
                << std::endl;
      return false;
    }
  }

  // Create the new directory
  if (mkdir(dir.c_str(), 0777) == -1) {
    std::cerr << "ERROR: Could not create directory: " << dir << std::endl;
    return false;
  }

  return true;
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
