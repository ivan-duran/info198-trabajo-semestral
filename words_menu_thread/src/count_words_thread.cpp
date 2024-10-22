#include "../include/utils.h"
#include "../include/options.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>


using namespace std;

int main(int argc, char *argv[]) {
    string path_in = "", path_out = "", extension = "", path_map = "", path_stop = "", path_clean = "", auxThreads = "";
    int threads ;

    int c;
    while ((c = getopt(argc, argv, "i:o:e:m:s:c:t:")) != -1) {
        switch (c) {
            case 'i':
                path_in = optarg;
                break;
            case 'o':
                path_out = optarg;
                break;
            case 'e':
                extension = optarg;
                break;
            case 'm':
                path_map = optarg;
                break;
            case 's':
                path_stop = optarg;
                break;
            case 'c':
                path_clean = optarg;
                break;
            case 't':
                auxThreads = optarg;
                break;
        }
    }
    threads = stoi(auxThreads.c_str());

        // Verificar si los paths están vacíos o si no existen
    // Verify that all required directories exist
    const vector<string> requiredDirs = {path_in, path_out, path_clean, path_map, path_stop};
    for (const string& dir : requiredDirs) {
        if (dir.empty() || !std::filesystem::exists(dir)) {
            std::cerr << "Error: " << dir << "no existe o está vacío." << std::endl;
            return 1;
        }
    }

    if (threads <= 0) {
        std::cerr << "Error: El número de hilos debe ser mayor a 0." << std::endl;
        return 1;
    }

    if(!hasFilesWithExtension(path_in, extension)){
        cout << "ERROR: No hay archivos con la extensión especificada en la carpeta de entrada." << endl;
        return 1;
    }

    system("clear");
    showMenu();
    mapa_archivo(path_map, extension, path_in);
    cout << "Se ejecuto mapa_archivo.\n";
    stop_words(path_stop, path_in, path_map, extension, path_clean);
    cout << "Se ejecuto stop_words.\n";
    parallelWordCount(path_clean, path_out, threads);

    //funcion que cuente palabras con threads//
    
    return 0;
}
