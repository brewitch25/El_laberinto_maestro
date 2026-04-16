#include <iostream>              // Ayuda a que el programa pueda tener input y output
#include <vector>                // Se usa para generar la matriz del laberinto
#include <ctime>                 // Se usa para generar los numeros aleatorios
#include <chrono>                // Para medir el tiempo de ejecucion
#include <cstdlib>               // Para generar aleatoriedad
using namespace std;             // Permite escribir de forma legible y facil de entender

// Definimos las constantes para los elementos del laberinto
const char SALIDA = 'S';
const char MURO = '#';
const char ENTRADA = 'E';
const char CAMINO = ' ';
const char RUTA = 'X';                          // Marca el camino resulto

// Indice de todas las funciones a usar en main
void generar_camino_desde(int fila, int col, int alto, int ancho, vector<vector<char>>& matriz);
bool es_posicion_valida(int fila, int col, int alto, int ancho);

int main() 
{    
    // Inicializa los numeros aleatorios
    srand(time(NULL));
    
    // Inicializamos y declaramos las variables
    int ancho, alto;
    // Solicitar al usuario valor ancho (numero de filas)
    cout <<"Ingrese el valor para el ancho del laberinto: "; cin >> ancho;
    // Solicitar al usuario valor alto(numero de columnas)
    cout <<"Ingrese el valor para el alto del laberinto: "; cin >> alto;

    // Ajustamos los valores a impares para asegurar paredes entre los caminos
    if (ancho % 2 == 0) ancho++;            // Se suma 1
    if (alto % 2 == 0) alto++;              // Se suma 1

    // Inicializo el laberinto lleno de MUROS
    vector<vector<char>> matriz_laberinto = vector<vector<char>>(alto, vector<char>(ancho, MURO));

    // Definimos la entrada(esquina superior derecha)
    matriz_laberinto[0][0] = ENTRADA;

    // Definimos el inicio del algoritimo en la posicion (1,1)
    generar_camino_desde(1, 1, alto, ancho, matriz_laberinto);

    // Permite que el jugador pase de la entrada al resto del laberinto
    matriz_laberinto[0][1] = CAMINO;
    matriz_laberinto[1][1] = CAMINO;

    // Definimos la salida, se crean los dos caminos para que la salida no se encuentren rodeadas
    // paredes, hace que se pueda acceder a la salida
    matriz_laberinto[alto - 1][ancho - 1] = SALIDA;
    matriz_laberinto[alto - 2][ancho - 1] = CAMINO;
    matriz_laberinto[alto - 2][ancho - 2] = CAMINO;

    return 0;
}

 // << === >> FUNCIONES A USAR EN EL MAIN << === >> //

void generar_camino_desde(int fila, int col, int alto, int ancho, vector<vector<char>>& matriz) 
{
    //Definimos las 4 direcciones(arriba, abajo, izquierda, derecha)
    
}

