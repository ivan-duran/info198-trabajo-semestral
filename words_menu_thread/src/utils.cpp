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
    cout << "CONTEO PARALELO CON THREADS" << endl;
    cout << "-----------------------------------" << endl;
    cout << "PID: " << pid << endl;
    cout << endl <<"Procesando..."<<endl;
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
        if (entry.path().extension().string() == "." + exten) {
            return true;
        }
    }
    return false;
}



