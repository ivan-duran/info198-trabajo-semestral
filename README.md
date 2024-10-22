## 1. Descripción del Sistema

Este programa es una aplicación de consola escrita en C++ que permite a los usuarios ejecutar una serie de operaciones basadas en un menú interactivo. Las opciones disponibles son:

0. **Salir:** Permite salir del programa.  
1. **Detección de Palíndromos:** Verifica si un texto ingresado es un palíndromo.  
2. **Contar Vocales:** Cuenta el número de vocales en un texto dado.  
3. **Cantidad de Letras:** Calcula la cantidad de letras en un texto.  
4. **Promedio y Sumatoria de un Vector:** Calcula la sumatoria y el promedio de un conjunto de números enteros.  
5. **Calcular f(x) = 5x*x + 1/x:** Realiza una operación matemática sobre un número ingresado.  
6. **Contar Palabras:** Cuenta las palabras que hay en los archivos de un directorio con la misma extensión.
7. **Conteo paralelo con threads:** Cuenta las palabras que hay en los archivos de un directorio con la misma extensión, utilizando threads.

Si el usuario tiene el rol de administrador, podrá acceder a las siguientes opciones adicionales:

8. **Ingresar Usuario:** Permite ingresar un nuevo usuario.  
9. **Listar Usuarios:** Muestra la lista de usuarios registrados.  
10. **Eliminar Usuario:** Elimina un usuario de la lista.


## 2. Compilación

Cada programa se compila por separado con el siguiente comando:
```bash
make
```

## 3. Ejecución

Una vez que los programas esten compilados, en el directorio main se ejecuta el siguiente comando:

```
./main -u <usuario> -p <contraseña> -t <texto> -v <vector> -n <número>
```

Ejemplo:

```
./main -u usuario -p contrasena -t palabra -v 10\;12\;20\;300 -n 5
```

## 4. Parámetros

- **-u:** Permite ingresar el nombre de usuario. El nombre debe contener solo letras y tener al menos 3 caracteres.
- **-p:** Permite ingresar la contraseña. Debe tener al menos 6 caracteres y contener solo letras y números.
- **-t:** Permite ingresar un texto que será utilizado en las opciones 1, 2 y 3 del menú.
- **-v:** Permite ingresar un vector de números enteros separados por `;` para la opción 4 del menú (por ejemplo, `10;12;20;300`).
- **-n:** Permite ingresar un número para calcular la función en la opción 5 del menú.

## 5. Gestión de Usuarios

Este sistema permite gestionar usuarios con dos roles distintos: **Admin** y **Usuario Genérico**. Los usuarios se autentican utilizando un archivo de texto que actúa como base de datos, donde están almacenados el nombre de usuario, la contraseña y el rol. Solo los usuarios con rol **Admin** pueden ver y acceder a las opciones de gestión de usuarios.

El formato del archivo de base de datos es el siguiente:

```
NombreUsuario1;Contraseña1;Rol1
NombreUsuario2;Contraseña2;Rol2
```

### Opciones de gestión de usuarios:

1. **Ingresar Usuario:** Permite añadir nuevos usuarios al archivo de base de datos.
2. **Listar Usuarios:** Muestra una lista de todos los usuarios registrados junto con su rol.
3. **Eliminar Usuario:** Permite eliminar usuarios genéricos del sistema. Solo los usuarios con rol **Admin** pueden realizar esta operación.

## 6. Conteo de Palabras en Archivos

El sistema incluye una funcionalidad para contar palabras en archivos dentro de un directorio especificado por el usuario. Esta opción ejecuta un proceso externo que:

1. Solicita al usuario tres datos:
   - **Extensión de los archivos** a procesar (por ejemplo, `.txt`).
   - **Ruta del directorio** donde se encuentran los archivos.
   - **Ruta del directorio** donde se guardarán los resultados.
   
2. Valida si las carpetas y los archivos existen antes de proceder.

3. Procesa los archivos del directorio de entrada, contando las veces que aparece cada palabra en cada archivo. Luego, genera un archivo de salida con el mismo nombre que el archivo de entrada, pero con los resultados del conteo en el formato:

```
palabra1; cantidad
palabra2; cantidad
```

4. Muestra un resumen al finalizar con la cantidad de palabras distintas en cada archivo procesado.

Ejemplo de salida:

```
archivo /home/lvc/out/cuento1.txt, 100 palabras distintas
archivo /home/lvc/out/cuento10.txt, 1020 palabras distintas
archivo /home/lvc/out/cuento11.txt, 2300 palabras distintas
```

## 7. Conteo de Palabras con Threads

Esta funcionalidad permite contar palabras en archivos de forma paralela usando hilos (threads). Se activa desde el menú seleccionando la opción 10.

#### Funcionamiento:
1. **Procesamiento en paralelo**: Utiliza hilos para procesar múltiples archivos simultáneamente, mejorando el rendimiento en directorios con muchos archivos.
2. **Variables configurables**:
   - **`PATH_INPUT_THREAD`**: Ruta de entrada de los archivos a procesar.
   - **`PATH_OUTPUT_THREAD`**: Ruta donde se guardarán los archivos procesados.
   - **`EXTEN_THREAD`**: Extensión de los archivos a procesar.
   - **`THREADS`**: Número máximo de hilos a usar (opcional).
3. **Salida**: Los archivos procesados se guardan en la carpeta de salida con el indice del texto y la cantidad de palabras contadas.

#### Ejemplo de ejecución:
- Los archivos de entrada en `PATH_INPUT_THREAD` con extensión `EXTEN_THREAD` se procesan en paralelo y los resultados se guardan en `PATH_OUTPUT_THREAD`.

## 8. Variables de Entorno

El sistema utiliza una serie de variables de entorno que son fundamentales para su configuración y funcionamiento. A continuación se detallan cada una de estas variables y su propósito:

- **`PATH_DB`**: Especifica la ruta del archivo que contiene la base de datos de usuarios.

- **`PATH_CLEAN`**: Define la ruta del directorio donde se almacenarán los archivos que han sido limpiados de palabras de parada.

- **`PATH_INPUT_THREAD`**: Especifica la ruta del directorio de entrada que contiene los archivos a procesar utilizando hilos (threads) para el conteo de palabras.

- **`PATH_OUTPUT_THREAD`**: Especifica la ruta del directorio donde se almacenarán los resultados de los archivos procesados con hilos (threads).

- **`PROGRAM_COUNT_WORDS`**:  Ruta del archivo ejecutable encargado de realizar el conteo de palabras.  (ejemplo: cd .. ; cd words_menu ; ./count_words)

- **`PROGRAM_COUNT_WORDS_THREAD`**: Ruta del archivo ejecutable que realiza el conteo de palabras utilizando hilos (threads). (ejemplo: cd .. ; cd words_menu_thread ; ./count_words_thread)

- **`PROGRAM_INVERTED_INDEX`**: Ruta del archivo ejecutable que genera el índice invertido. (ejemplo: cd .. ; cd inverted_index ; ./inverted_index)

- **`PATH_FILES_MAP`**: Define la ruta del archivo que contiene el mapeo de nombres de archivos y sus respectivos índices.

- **`PATH_STOP_WORDS`**: Ruta del archivo que contiene las palabras de parada o palabras a ignorar durante el procesamiento.

- **`PATH_INVERTED_INDEX`**: Especifica la ruta del archivo donde se almacenará el índice invertido generado después del conteo de palabras.

- **`EXTEN_THREAD`**: Especifica la extensión de los archivos que serán procesados con hilos (threads).

- **`THREADS`**: Número máximo de hilos a utilizar para el procesamiento de archivos con hilos (threads).

## 9. Índice Invertido

El **índice invertido** es una estructura que mapea cada palabra a los archivos donde aparece y cuántas veces se repite en cada uno.

#### Funcionamiento:
1. **Generación**:
   - Tras contar las palabras en los archivos con threads, se genera un archivo que contiene el índice invertido.
   - Este archivo se guarda en la ruta definida por la variable `PATH_INVERTED_INDEX`.

2. **Formato del archivo**:
   El archivo de índice invertido tiene el formato:
   ```
   palabra1;(ID1,cantidad);(ID2,cantidad);
   palabra2;(ID3,cantidad);
   ```
   - **ID**: Identificador del archivo.
   - **cantidad**: Número de veces que la palabra aparece en el archivo.

#### Ejemplo:
```
anillo;(0,150);(2,75)
poder;(1,230);(3,120)
```
En este ejemplo, "anillo" aparece 150 veces en el archivo con ID 0 y 75 veces en el archivo con ID 2.