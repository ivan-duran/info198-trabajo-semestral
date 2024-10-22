#include <string>
#include <vector>
#include <unordered_map>
#ifndef UTILS_H
#define UTILS_H

void showMenu(std::string user, std::string rol);
bool isValidUsername(const std::string& user);
bool isValidPassword(const std::string& pass);
std::vector<int> splitVec(std::string vec_str);
bool veryfyUser(std::unordered_map<std::string, std::pair<std::string,std::string>> users, std::string user, std::string pass);
std::unordered_map<std::string, std::pair<std::string,std::string>> loadUsers(std::string path);
std::vector<int> splitInt(std::string s, char delimiter);
bool isValidVec(std::string vector);
bool areParamsProvided(bool hasUser, bool hasPass, bool hasText, bool hasVector, bool hasNumber);



#endif
