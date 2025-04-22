#ifndef BATCH_UTILS_H
#define BATCH_UTILS_H

#include <string>
#include <vector>

namespace BatchUtils {
// Function to clear the terminal screen
void clearTerminal();

// Function to ensure a directory exists
bool ensureDirectory(const std::string& dir);

// Function to handle menu input and print options
int getMenuChoice(const std::vector<std::string>& options,
                  const std::string& prompt);
}  // namespace BatchUtils

#endif  // BATCH_UTILS_H
