#include "../include/utils.h"
#include "../include/options.h"
#include <iostream>
#include <string>
#include <vector>



using namespace std;

int main(int argc, char *argv[]) {
    vector<string> file;
    string extension = "", path_in= "", path_out = "";
    
    for (int i = 0; i < file.size(); i++) {
        cout << file[i] << endl;
    }
    
    do {
        system("clear");
        showMenu();
        char option;
        cin >> option;
        
        switch (option) {
            case '0':
                cout << "Saliendo..." << endl;
                return 0;
            case '1':
                system ("clear");
                cout << "-----------------------------------" << endl;
                cout << "Ingrese la extension: ";
                cin >> extension;
                extension = "." + extension;            
                cout << "-----------------------------------" << endl;
                cout << "Extensión ingresada correctamente, presione enter para continuar" << endl;
                cin.ignore();
                cin.get();
                break;
            case '2':
                system ("clear");
                cout << "-----------------------------------" << endl;
                cout << "Ingrese la ruta a procesar: ";
                cin >> path_in;
                cout << "-----------------------------------" << endl;
                if (!directoryExists(path_in)) {
                    path_in = "";
                    cout << "La carpeta de entrada no existe, presione enter para continuar" << endl;
                    cin.ignore();
                    cin.get();
                    break;
                }
                cout << "Ruta ingresada correctamente, presione enter para continuar" << endl;
                cin.ignore();
                cin.get();
                break;
            case '3':
                system ("clear");
                cout << "-----------------------------------" << endl;
                cout << "Ingrese la ruta de salida: ";
                cin >> path_out;
                cout << "-----------------------------------" << endl;
                if (!directoryExists(path_out)) {
                    path_out = "";
                    cout << "La carpeta de salida no existe, presione enter para continuar" << endl;
                    cin.ignore();
                    cin.get();
                    break;
                }
                cout << "Ruta ingresada correctamente, presione enter para continuar" << endl;
                cin.ignore();
                cin.get();
                break;
            case '4':
                system ("clear");
                cout << "-----------------------------------" << endl;
                if (path_in == "" || path_out == "" || extension == "") {
                    cout << "Debe ingresar todos los datos antes de procesar" << endl;
                    cout << "Datos faltantes: " << endl;
                    if (extension == "") cout << "\tExtensión" << endl;
                    if (path_in == "") cout << "\tRuta de entrada" << endl;
                    if (path_out == "") cout << "\tRuta de salida" << endl;
                    cout << "-----------------------------------" << endl;
                    cout << "Presione enter para continuar" << endl;
                    cin.ignore();
                    cin.get();
                    break;
                } else if (!hasFilesWithExtension(path_in, extension)) {

                    cout << "No hay archivos con la extensión: " << extension << " en el directorio: " << path_in << endl;
                    cout << "-----------------------------------" << endl;
                    cout << "Presione enter para continuar" << endl;
                    cin.ignore();
                    cin.get();
                    break;
                }
                else {
                    cout << "Procesando..." << endl;
                    vector<pair<string, string>> texts_list ;
                    texts_list = readFolder(path_in, extension);
                    vector<pair<string, int>> salida = fileOut(texts_list, path_out, extension);
                    cout << "Realizado con exito.\n"<<endl;
                    for (const auto& aux : salida){
                        cout<< "archivo "<<aux.first<<", "<<aux.second<<" palabras distintas"<<endl;
                    }

                    return 0;
                }
                break;
            default:
                system("clear");
                cout << "Opción inválida" << endl;
                
                break;
        }
        


    } while (true);
    
    return 0;
}
