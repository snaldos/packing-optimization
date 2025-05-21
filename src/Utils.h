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

/**
 * @namespace Utils
 * @brief Utility functions for file and directory operations.
 */
namespace Utils {
/**
 * @brief Returns the absolute directory for a given relative path.
 * @param path Relative or absolute path
 * @return Absolute path as a string
 */
std::string get_absolute_dir(std::string path);

/**
 * @brief Removes a directory and its contents.
 * @param path Path to the directory
 * @return True if the directory was removed successfully, false otherwise
 */
bool remove_directory(const std::string& path);

/**
 * @brief Ensures that a directory exists, creating it if necessary.
 * @param dir Path to the directory
 * @return True if the directory exists or was created successfully, false
 * otherwise
 */
bool ensure_directory(const std::string& dir);

}  // namespace Utils

#endif  // UTILS_H
