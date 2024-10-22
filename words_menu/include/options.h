#include <string>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <vector>


#ifndef OPTIONS_H
#define OPTIONS_H 

std::string readFile(const std::string& path);
std::vector<std::pair<std::string, std::string>> readFolder(const std::string& carpetaPath,std::string exten);
std::unordered_map<std::string, int> countWord(const std::string& texto);
std::vector<std::pair<std::string, int>> fileOut(const std::vector<std::pair<std::string, std::string>>& textos, const std::string& path, const std::string& exten);




#endif