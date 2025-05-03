#include "Utils.h"

namespace Utils {
std::string get_absolute_dir(std::string path) {
  return std::string(PROJECT_DIR) + path;
}

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

}  // namespace Utils
