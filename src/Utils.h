#ifndef UTILS_H
#define UTILS_H

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

namespace Utils {
std::string get_absolute_dir(std::string path);

bool remove_directory(const std::string& path);

bool ensure_directory(const std::string& dir);

}  // namespace Utils

#endif  // UTILS_H
