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

/**
 * @namespace BatchUtils
 * @brief Utility functions for batch mode operations (terminal UI, file paths,
 * menus).
 */
namespace BatchUtils {
/**
 * @brief Clears the terminal screen and prints the application header.
 */
void clear_terminal();

/**
 * @brief Returns the absolute directory for a given relative path.
 * @param path Relative or absolute path
 * @return Absolute path as a string
 */
std::string get_absolute_dir(std::string path);

/**
 * @brief Handles menu input and prints options to the terminal.
 * @param options List of menu options
 * @param prompt Prompt to display
 * @return User's menu choice (1-based index), or 0 if exit
 */
int get_menu_choice(const std::vector<std::string>& options,
                    const std::string& prompt);
}  // namespace BatchUtils

#endif  // BATCH_UTILS_H
