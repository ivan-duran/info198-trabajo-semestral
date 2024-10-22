#include "options.h"
#include "utils.h"
#include "dotenv.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unistd.h>
#include <sys/types.h>




using namespace std;

//ejecucion = ./main -u IsaiasCabrera -p qwertyui -t "haiah" -v 1\;2\;3\;4 -n 3

int main(int argc, char *argv[]) {    
    system("clear");
    string user, pass, rol, text, str_vec;
    vector<int> vec_num;
    double num;
    bool hasUser = false, hasPass = false, hasText = false, hasVector = false, hasNumber = false, passThread = false;

    dotenv::init("path_db.env");
    string path_db = getenv("PATH_DB");
    unordered_map<string, pair<string, string>> users = loadUsers(path_db);
    
    string extension_thread = getenv("EXTEN_THREAD");
    string path_in_thread = getenv("PATH_INPUT_THREAD");
    string path_out_thread = getenv("PATH_OUTPUT_THREAD");
    string path_map = getenv("PATH_FILES_MAP");
    string path_stop = getenv("PATH_STOP_WORDS");
    string path_clean = getenv("PATH_CLEAN");
    string program_count_words = getenv("PROGRAM_COUNT_WORDS");
    string program_count_words_thread = getenv("PROGRAM_COUNT_WORDS_THREAD");
    string program_inverted_index = getenv("PROGRAM_INVERTED_INDEX");
    string path_inverted_index = getenv("PATH_INVERTED_INDEX");
    string threads = getenv("THREADS");
    cout << threads << endl;
    if(path_in_thread == path_out_thread){
        cout << "ERROR: Las rutas de entrada y salida no pueden ser iguales." << endl;
        return 1;
    }

    int c;
    while ((c = getopt(argc, argv, "u:p:t:v:n:")) != -1) {
        switch (c) {
            case 'u':
                user = optarg;
                if (!isValidUsername(user)){
                    cerr << "Nombre de usuario no valido, debe contener solo letras y tener al menos 3 caracteres." << endl;
                    return 1;
                }
                hasUser = true;
                break;
            case 'p':
                pass = optarg;
                if (!isValidPassword(pass)){
                    cerr << "Contraseña no valida, debe tener al menos 6 caracteres y contener solo letras y números.." << endl;
                    return 1;
                }
                hasPass = true;

                break;
            case 't':
                text = optarg;
                hasText = true;
                break;
            case 'v': {
                str_vec = optarg;
                if (!isValidVec(str_vec)) {
                    cerr << "ERROR: El argumento -v " << str_vec << " debe estar ingresado en el siguiente formato n;n;...;n." << endl;
                    return 1;
                }
                vec_num = splitInt(str_vec, ';');
                hasVector = true;
                break;
            }
            case 'n':
                try {
                    num = stod(optarg);
                } catch (const std::invalid_argument& ia) {
                    cerr << "El argumento -n '" << optarg << "' debe ser un número real" << endl;
                    return 1;
                }
                hasNumber = true;
                break;
            default:
                cerr << "Opción no válida." << endl;
                return 1;
        }
    }

    
    if (!areParamsProvided(hasUser, hasPass, hasText, hasVector, hasNumber)) {
        return 1;
    }


    if (!veryfyUser(users, user, pass)) {
        cerr << "Usuario o contraseña incorrectos." << endl;
        return 1;
    }
    rol = users[user].second;

    do {
        system("clear");
        int option;
        showMenu(user, rol);
        cout << "Ingrese una opción: ";
        cin >> option;
        system("clear"); 
        switch (option) {
            case 0:
                cout << "Saliendo..." << endl;
                return 0;
            case 1:
                cout << "-----------------------------------" << endl;
                cout << "La palabra: " << text << endl;
                if (isPalindrome(text))
                    cout << "Es palíndromo." << endl;
                else
                    cout << "No es palíndromo." << endl;
                cout << "-----------------------------------" << endl;
                break;
            case 2:
                cout << "-----------------------------------" << endl;
                cout << "La palabra: " << text <<"\ntiene " << countVowels(text) << " vocales." << endl;
                cout << "-----------------------------------" << endl;
                break;
            case 3:
                cout << "-----------------------------------" << endl;
                cout << "La palabra: " << text <<"\ntiene " << countLetters(text) << " letras." << endl;
                cout << "-----------------------------------" << endl;
                break;
            case 4: {
                cout << "-----------------------------------" << endl;
                pair<int, double> result = sumAndAverage(vec_num);
                cout << "Vector: (";
                for (int i = 0; i < vec_num.size(); i++) {
                    cout << vec_num[i];
                    if (i != vec_num.size() - 1) cout << ", ";
                }
                cout << ")" << endl;
                cout << "Sumatoria: " << result.first << endl;
                cout << "Promedio: " << result.second << endl;
                cout << "-----------------------------------" << endl;
                break;
                }   
            case 5:
                cout << "-----------------------------------" << endl;
                cout << "f(" << num << ") = " << calculateFunction(num) << endl;
                cout << "-----------------------------------" << endl;
                break;
            case 6:
                cout << "-----------------------------------" << endl;
                system(program_count_words.c_str());
                cout << "-----------------------------------" << endl;
                break;
            case 7: {
                cout << "-----------------------------------" << endl;
                string aux_path = program_count_words_thread + " -i " + path_in_thread + " -o " + path_out_thread + " -e " + extension_thread + " -m " + path_map + " -s " + path_stop + " -c " + path_clean + " -t " + threads;
                system(aux_path.c_str());
                passThread = true;
                cout << "-----------------------------------" << endl;
                break;
            }
            case 8: {
                if (passThread){
                cout << "-----------------------------------" << endl;
                string aux_path = program_inverted_index + " -o " + path_out_thread + " -i " + path_inverted_index + " -e " + extension_thread;
                system(aux_path.c_str());
                cout << "-----------------------------------" << endl;
                }
                else{
                    cout << "-----------------------------------" << endl;
                    cout << "Se debe ejecutar la opcion 7 antes de ejecutar la opcion 8." << endl;
                    cout << "-----------------------------------" << endl;
                }
                break;
            }
            case 9:
                if (rol == "Admin"){
                    cout << "-----------------------------------" << endl;
                    string userIns, passIns, rolIns;
                    do{
                        cout << "Nombre de usuario: ";
                        cin>>userIns;
                        if (!isValidUsername(userIns)) cout << "El usuario debe ser solo letras y tener mas de 3 caracteres" << endl;
                    }while(!isValidUsername(userIns));
                    do{
                        cout << "Contraseña del usuarios: ";
                        cin>>passIns;
                        if (!isValidPassword(passIns)) cout << "La contraseña debe ser solo numeros o letras y tener mas de 6 caracteres" << endl;
                    }while(!isValidPassword(passIns));
                    do {
                        cout << "Rol del usuario: 1. Admin 2. Usuario Generico" << endl;
                        cin>>rolIns;
                        if (rolIns == "1") rolIns = "Admin";
                        else if (rolIns == "2") rolIns = "User";
                        else cout << "Opción no válida.\n\n";
                    } while (rolIns != "Admin" && rolIns != "User");
                    cout<< "Creando Usuario ..."<<endl;
                    createUser(userIns, passIns, rolIns, users, "usuarios.csv");
                    cout << "-----------------------------------" << endl;
                    break;
                break;
                }else {
                    cout << "Opción no válida.\n\n";
                    break;
                }
            case 10:
                if (rol == "Admin"){
                    cout << "-----------------------------------" << endl;
                    showUsers(users);
                    cout << "-----------------------------------" << endl;
                    break;
                }else {
                    cout << "Opción no válida.\n\n";
                    break;
                }
                
            case 11:
                if (rol == "Admin"){
                    cout << "-----------------------------------" << endl;
                    string userDel;
                    cout << "Nombre de usuario: ";
                    cin>>userDel;
                    cout<< "Eliminando Usuario ..."<<endl;
                    deleteUser(userDel, users[userDel].second, users, "usuarios.csv");
                    cout << "-----------------------------------" << endl;
                    break;
                }else {
                    cout << "Opción no válida.\n\n";
                    break;
                }
        }
        do {
            cout << "¿Desea realizar otra operación? (s/n): ";
            string ans;
            cin >> ans;
            if (ans == "n" || ans == "N") {
                cout << "Saliendo..." << endl;
                return 0;
            } else if (ans == "s" || ans == "S" || ans.empty()) {
                break;
            }
        } while (true);

    } while (true);
    return 0;
}
