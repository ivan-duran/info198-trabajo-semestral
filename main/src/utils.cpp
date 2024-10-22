#include "utils.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <unistd.h>


using namespace std;

/**
 * @brief Muestra el menú de opciones disponibles para el usuario.
 * 
 * @param user Nombre de usuario.
 * @param rol Rol del usuario.
 * 
 * Muestra el menú de opciones disponibles para el usuario, dependiendo de su rol.
 */
void showMenu(string user, string rol) {
    pid_t pid = getpid();
    cout << "MAIN (PID = " << pid <<")"<< endl;
    cout << "Nombre de Usuario: " << user << endl;
    cout << "Rol: " << rol << endl;    
    cout << "-----------------------------------" << endl;
    cout << "0) Salir\n";
    cout << "1) Detección de palíndromos\n";
    cout << "2) Contar vocales\n";
    cout << "3) Cantidad de letras en un texto\n";
    cout << "4) Promedio y sumatoria de un vector\n";
    cout << "5) Calcular f(x)=5x*x+1/x\n";
    cout << "6) Contar Palabras\n";
    cout << "7) Conteo Paralelo Con Threads\n";
    cout << "8) Crear Indice Invertido\n";
    if (rol == "Admin"){
        cout << "9) Ingresar Usuario\n";
        cout << "10) Listar Usuarios\n";
        cout << "11) Eliminar Usuario\n";
    }
    cout << "-----------------------------------" << endl;
}


/**
 * @brief Verifica si un nombre de usuario es válido.
 *
 * @param user Nombre de usuario a verificar.
 * @return true Si el nombre de usuario es válido.
 * @return false Si el nombre de usuario no es válido.
 *
 * Un nombre de usuario es válido si solo contiene letras y tiene al menos 3 caracteres.
 */
bool isValidUsername(const string& user) {
    if (user.length() < 3) return false;
    for (char c : user) {
        if (!isalpha(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

/**
 * @brief Verifica si una contraseña es válida.
 *
 * @param pass Contraseña a verificar.
 * @return true Si la contraseña es válida.
 * @return false Si la contraseña no es válida.
 *
 * Una contraseña es válida si tiene al menos 6 caracteres y solo contiene letras y números.
 */
bool isValidPassword(const string& pass) {
    if (pass.length() < 6) return false;
    for (char c : pass) {
        if (!isalnum(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

/**
 * @brief Divide un texto en números.
 *
 * @param text Texto a dividir.
 * @return vector<int> Vector con los números obtenidos.
 *
 * Esta función divide un texto en números separados por punto y coma.
 */
vector<int> splitVec(string vec_str){
    string word;
    stringstream ss(vec_str);
    vector<int> vec;
    while (getline(ss, word, ';')) {
        cout << word << endl;
        for (char c : word) {
            if (!isdigit(c)) {
                cout << "ERROR: El argumento -v " << vec_str << " debe contener numeros enteros." << endl;
                exit(0);
                return vec;
            }
        }
        vec.push_back(stoi(word));

    }
    return vec;
}

/**
 * @brief Verifica si un usuario y contraseña son válidos.
 * 
 * @param users Mapa con los usuarios y contraseñas.
 * @param user Usuario a verificar.
 * @param pass Contraseña a verificar.
 * @return true Si el usuario y contraseña son válidos.
 * @return false Si el usuario y contraseña no son válidos.
 * 
 * Verifica si un usuario y contraseña son válidos comparando con un mapa de usuarios y contraseñas.
 */
bool veryfyUser(unordered_map<string, pair<string,string>> users, string user, string pass){
    if (users[user].first == pass) return true;
    return false;
}


/**
 * @brief Carga un archivo csv y lo pone en un unordered_map<string, pair<string,string>>.
 * 
 * @param path Ruta del archivo de variables de entorno.
 * @return unordered_map<string, pair<string,string>> Mapa con los usuarios.
 * 
 * Función que carga un archivo de variables de entorno que tiene la forma user,password,Rol
 * y retorna un mapa con los usuarios, contraseñas y roles.
 */
unordered_map<string, pair<string,string>> loadUsers(string path){

    unordered_map <string, pair<string, string>> usuarios;
    ifstream archivo(path);
    string linea, usuario, contraseña, rol;
    
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, usuario, ';');
        getline(ss, contraseña, ';');
        getline(ss, rol, ';');
        usuarios[usuario] = make_pair(contraseña, rol);
    }
    archivo.close();
    return usuarios;
}

/**
 * @brief Verifica si un vector esta ingresado en un formato valido.
 * 
 * @param vector Vector a verificar.
 * @return true si esta bien ingresado, false sino.
 * 
 * Recorre el vector esperando un int y ";" con la condicion de haber un numero antes de un nuevo ";" ademas de terminar con un numero.
 */
bool isValidVec(string vector){
    bool aux = false;
    int i = 0;
    while(i<vector.size()){
        if (isdigit(vector[i])) aux = true;
        else if((vector[i] == ';' && aux)) aux = false;
        else return false;
        i++;
    }
    if(!aux) return false;
    return true;
}

/**
 * @brief Divide un string y lo gaurda en un vector<int>.
 * 
 * @param s String a dividir.
 * @param delimiter caracter el cual se usara de separador
 * @return vector<int> con el string dividido segun el separador.
 * 
 * Divide un string en numeros separados por un delimitador.
 */
vector<int> splitInt(string s, char delimiter) {
    vector<int> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(stoi(token));
    }
    return tokens;
}

/**
 * @brief Verifica si se ingresaron todos los parametros necesarios.
 * 
 * @param hasUser Si se ingreso el usuario.
 * @param hasPass Si se ingreso la contraseña.
 * @param hasText Si se ingreso el texto.
 * @param hasVector Si se ingreso el vector.
 * @param hasNumber Si se ingreso el numero.
 * @return true si se ingresaron todos los parametros, false sino.
 * 
 * Verifica si se ingresaron todos los parametros necesarios para realizar una operacion.
 */
bool areParamsProvided(bool hasUser, bool hasPass, bool hasText, bool hasVector, bool hasNumber){
    if (!hasUser) {
        cout << "Error: Se debe ingresar el usuario (-u)." << endl;
        return false;
    }
    if (!hasPass) {
        cout << "Error: Se debe ingresar la contraseña (-p)." << endl;
        return false;
    }
    if (!hasText) {
        cout << "Error: Se debe ingresar el texto (-t)." << endl;
        return false;
    }
    if (!hasVector) {
        cout << "Error: Se debe ingresar el vector (-v)." << endl;
        return false;
    }
    if (!hasNumber) {
        cout << "Error: Se debe ingresar el número (-n)." << endl;
        return false;
    }
    return true;
}