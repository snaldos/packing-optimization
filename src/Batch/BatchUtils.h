#ifndef BATCH_UTILS_H
#define BATCH_UTILS_H

#include <string>
#include <vector>

namespace BatchUtils {
// Function to clear the terminal screen
void clear_terminal();

// Function to remove a directory and its contents
bool remove_directory(const std::string& path);

// Function to ensure a directory exists
bool ensure_directory(const std::string& dir);

// Function to get the output directory
std::string get_absolute_dir(std::string path);

// Function to handle menu input and print options
int get_menu_choice(const std::vector<std::string>& options,
                    const std::string& prompt);
}  // namespace BatchUtils

#endif  // BATCH_UTILS_H
