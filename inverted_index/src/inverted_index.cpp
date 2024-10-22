
#include "../include/utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <filesystem>


using namespace std;

int main(int argc, char *argv[]) {
    string  path_out = "", extension = "", path_inverted_index = "";

    int c;
    while ((c = getopt(argc, argv, "o:e:i:")) != -1) {
        switch (c) {
            case 'o':
                path_out = optarg;
                break;
            case 'e':
                extension = optarg;
                break;
            case 'i':
                path_inverted_index = optarg;
                break;
        }
    }
    
    const vector<string> requiredDirs = {path_out};
    for (const string& dir : requiredDirs) {
        if (dir.empty() || !std::filesystem::exists(dir)) {
            cout << "Error: " << dir << " no existe o no fue especificado.\n";
            return 1;
        }
    }

    system("clear");
    showMenu();
    inverted_index(path_inverted_index, path_out, extension);

    
    return 0;
}
