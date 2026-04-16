#include <iostream>              // Ayuda a que el programa pueda tener input y output
#include <vector>                // Se usa para generar la matriz del laberinto
#include <ctime>                 // Se usa para generar los numeros aleatorios
#include <chrono>                // Para medir el tiempo de ejecucion
#include <stdlib.h>              // Para generar aleatoriedad
using namespace std;             // Permite escribir de forma legible y facil de entender

// Definimos las constantes para los elementos del laberinto
const char SALIDA = 'S';
const char MURO = '|';
const char ENTRADA = 'E';
const char CAMINO = '.';
const char RUTA = 'X';                          // Marca el camino resulto

int main() 
{
    // Inicializamos y declaramos las variables
    int ancho, alto;
    
    // Vamos a solicitar al usuario los siguientes valor (ancho y alto)
    // Valor ancho (numero de filas)
    cout <<"Ingrese el valor para el ancho del laberinto: "; cin >> ancho;
    // Valor alto(numero de columnas)
    cout <<"Ingrese el valor para el alto del laberinto: "; cin >> alto;

    // Inicializo el laberinto
    vector<vector<char>> matriz_laberinto = vector<vector<char>>(alto, vector<char>(ancho, MURO));

    // Output de prueba de visualizacion de inicializacion de laberinto
    //cout <<"Laberinto creado de " << ancho << "x" << alto << endl;

    return 0;
}


