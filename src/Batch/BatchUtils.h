#ifndef BATCH_UTILS_H
#define BATCH_UTILS_H

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
#include <vector>

namespace BatchUtils {
// Function to clear the terminal screen
void clear_terminal();

// Function to get the output directory
std::string get_absolute_dir(std::string path);

// Function to handle menu input and print options
int get_menu_choice(const std::vector<std::string>& options,
                    const std::string& prompt);
}  // namespace BatchUtils

#endif  // BATCH_UTILS_H
