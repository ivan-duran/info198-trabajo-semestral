#include <string>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>


#ifndef OPTIONS_H
#define OPTIONS_H 

std::string readFile(const std::string& path);
std::vector<std::pair<std::string, std::string>> readFolder(const std::string& carpetaPath,std::string exten);
std::unordered_map<std::string, int> countWord(const std::string& texto);
std::vector<std::pair<std::string, int>> fileOut(const std::vector<std::pair<std::string, std::string>>& textos, const std::string& path, const std::string& exten);

void mapa_archivo(const std::string& path_map, const std::string& exten,const  std::string& path_in);
void stop_words(const std::string& stopWordsPath, const std::string& path_in, const std::string& path_map, const std::string& exten,const std::string& path_clean);
void parallelWordCount(const std::string& inputDir, const std::string& outputDir, int maxThreads);



#endif