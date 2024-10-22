#include <string>
#include <filesystem>

#ifndef UTILS_H
#define UTILS_H

void showMenu ();
bool directoryExists(const std::string& path);
bool hasFilesWithExtension(const std::string& path, const std::string& exten);

#endif