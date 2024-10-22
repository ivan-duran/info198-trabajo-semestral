#include "utils.h"

#include <iostream>
#include <unistd.h> 
#include <filesystem> 

using namespace std ;

/**
 * @brief Muestra el menú de opciones disponibles para el usuario.
 * 
 * Muestra el menú de opciones disponibles para el usuario.
 */
void showMenu(){
    pid_t pid = getpid();
    cout << "CONTADOR DE PALABRAS" << endl;
    cout << "-----------------------------------" << endl;
    cout << "PID: " << pid << endl;
    cout << endl << "0) Salir\n";
    cout << "1) Extensión de archivos a procesar(ej: txt)\n";
    cout << "2) Path de carpeta a procesar (ej: /home/lvc/in)\n";
    cout << "3) path de carpeta que contendrá la respuesta del proceso (ej: /home/lvc/out)\n";
    cout << "4) Procesar\n";
    cout << "-----------------------------------" << endl;
}

/**
 * @brief Verifica si un directorio existe.
 * 
 * @param path Ruta del directorio a verificar.
 * @return true Si el directorio existe.
 * 
 * Verifica si un directorio existe.
 */
bool directoryExists(const string& path) {
    return filesystem::exists(path) && filesystem::is_directory(path);
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