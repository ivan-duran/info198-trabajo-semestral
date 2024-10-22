#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#ifndef OPTIONS_H
#define OPTIONS_H 


bool isPalindrome(std::string text);
int countVowels(std::string text);
int countLetters(std::string text);
std::pair<int, double> sumAndAverage(const std::vector<int>& numbers);
double calculateFunction(double n);
void showUsers(std::unordered_map<std::string, std::pair<std::string, std::string>> users);
void createUser(std::string user, std::string pass, std::string rol, std::unordered_map<std::string, std::pair<std::string, std::string>>& users, std::string path);
void deleteUser(std::string user, std::string rol, std::unordered_map<std::string, std::pair<std::string, std::string>>& users, std::string path);





#endif