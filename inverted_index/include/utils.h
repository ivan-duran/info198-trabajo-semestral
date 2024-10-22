#include <string>

#ifndef UTILS_H
#define UTILS_H

void showMenu ();
bool directoryExists(const std::string& path);
bool hasFilesWithExtension(const std::string& path, const std::string& exten);
void inverted_index(const std::string& path_inverted_index, const std::string& path_out, const std::string& extension);

#endif