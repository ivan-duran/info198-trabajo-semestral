#include "options.h"
#include <string>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <vector>


using namespace std;

/**
 * @brief Verifica si un texto es un palíndromo.
 * 
 * @param text Texto a verificar.
 * @return true Si el texto es un palíndromo.
 * @return false Si el texto no es un palíndromo.
 * 
 * Un palíndromo es una palabra o frase que se lee igual de izquierda a derecha que de derecha a izquierda.
*/
string readFile(const string& path) {
    ifstream archivo(path); 
    stringstream buffer;
    buffer << archivo.rdbuf();
    archivo.close();
    
    return buffer.str();
}

/**
 * @brief Lee los archivos de una carpeta y los guarda en un vector.
 * 
 * @param carpetaPath Ruta de la carpeta a leer.
 * @param exten Extensión de los archivos a leer.
 * @return vector<pair<string, string
 * 
 * Lee los archivos de una carpeta y los guarda en un vector de pares, donde el primer elemento es el título del archivo y el segundo es el contenido.
 */    
vector<pair<string, string>> readFolder(const string& carpetaPath,string exten) {
    vector<pair<string, string>> todosLosArchivos;
    for (const auto& entry : std::filesystem::directory_iterator(carpetaPath)) {
        string pathArchivo = entry.path().string();
        
        if (entry.path().extension().string()== exten){
            string titulo = entry.path().stem().string();
            string contenido = readFile(pathArchivo);
            todosLosArchivos.push_back(make_pair(titulo, contenido));
        }
    }
    return todosLosArchivos;
}

/**
 * @brief Cuenta la cantidad de palabras en un texto.
 * 
 * @param texto Texto a contar.
 * @return unordered_map<string, int> Mapa con las palabras y su cantidad.
 * 
 * Cuenta la cantidad de palabras en un texto y las guarda en un mapa.
 */
unordered_map<string, int> countWord(const string& texto) {
    unordered_map<string, int> conteoPalabras; 
    stringstream ss(texto);
    string palabra;
    
    while (ss >> palabra) {
        while (!palabra.empty() && !isalpha(palabra.back())) {
            palabra.pop_back();
        }
        while (!palabra.empty() && !isalpha(palabra.front())) {
            palabra.erase(palabra.begin()); 
        }
        for (char& c : palabra) {
            c = tolower(c);
        }
        
        if (!palabra.empty()) {
            conteoPalabras[palabra]++;
        }
    }
    return conteoPalabras;
}

/**
 * @brief Crea archivos con el conteo de palabras de un texto.
 * 
 * @param textos Vector de pares con el título y contenido de los textos.
 * @param path Ruta de la carpeta donde se guardarán los archivos.
 * @param exten Extensión de los archivos a crear.
 * @return vector<pair<string, int>> Vector de pares con la ruta de los archivos creados y la cantidad de palabras diferentes.
 * 
 * Crea archivos con el conteo de palabras de un texto y los guarda en una carpeta con la extensión especificada.
 */
vector<pair<string, int>> fileOut(const vector<pair<string, string>>& textos, const string& path, const string& exten) {
    vector<pair<string, int>> salida;
    for (const auto& texto : textos) {
        string titulo = texto.first;
        string contenido = texto.second;
    
        unordered_map<string, int> conteo = countWord(contenido);
        
        // Crear el archivo en la carpeta con la extensión especificada
        string archivoPath = path + "/" + titulo + exten;
        ofstream archivo(archivoPath);

        // Escribir el conteo de palabras en el archivo
        int diffWords = 0;
        for (const auto& par : conteo) {
            archivo << par.first << "; " << par.second << endl; 
            diffWords ++;
        }

        archivo.close(); 
        salida.push_back(make_pair(archivoPath, diffWords));
    }
    return salida;
}

    
