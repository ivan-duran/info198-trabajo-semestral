#include "utils.h"

#include <iostream>
#include <unistd.h> 
#include <filesystem> 
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>


using namespace std ;

/**
 * @brief Muestra el menú de opciones disponibles para el usuario.
 * 
 * Muestra el menú de opciones disponibles para el usuario.
 */
void showMenu(){
    pid_t pid = getpid();
    cout << "Creacion de inverted index" << endl;
    cout << "-----------------------------------" << endl;
    cout << "PID: " << pid << endl;
    cout << endl <<"Creando indice invertido..."<<endl;
    cout << "-----------------------------------" << endl;
}



/**
 * @brief Verifica si un directorio está vacío.
 * 
 * @param path Ruta del directorio a verificar.
 * @return true Si el directorio está vacío.
 * 
 * Verifica si un directorio está vacío.
 */
bool hasFilesWithExtension(const string& path, const string& exten) {
    for (const auto& entry : filesystem::directory_iterator(path)) {
        if (entry.path().extension().string() == exten) {
            return true;
        }
    }
    return false;
}

void inverted_index(const string& path_inverted_index, const string& path_out, const string& exten){
    unordered_map<string, vector<pair<int,int>>> inverted_index;
    for (const auto& entry : std::filesystem::directory_iterator(path_out)) {
        string pathArchivo = entry.path().string();
        string linea;
        if (entry.path().extension().string()== "." + exten){
            ifstream archivo(pathArchivo);
            string id = entry.path().stem().string();
            while (getline(archivo, linea)) {
                size_t pos = linea.rfind(':');
                string palabra = linea.substr(0, pos);  // Parte antes del último :
                string cant = linea.substr(pos + 1);
                inverted_index[palabra].push_back(make_pair(stoi(id), stoi(cant)));
            }
            archivo.close();
        }
    }

    ofstream archivo(path_inverted_index);
    for (const auto& entry : inverted_index) {
        string palabra = entry.first;
        archivo << palabra << "; ";
        for (const auto& id_cant : entry.second) {
            string id = to_string(id_cant.first);
            string cant = to_string(id_cant.second);
            archivo << "( " << id << ", " << cant <<");";
        }
        archivo << endl;
    }
    archivo.close();
    cout<<"Indice invertido creado exitosamente."<<endl;

}



