#include <iostream>              // Ayuda a que el programa pueda tener input y output
#include <vector>                // Se usa para generar la matriz del laberinto
#include <algorithm>             // Se usa para el procesamiento de datos, en este caso los datos del vector
#include <stack>                 // Se usa para la generacion del laberinto (ya que va a ser hecho por el usuario)
#include <queue>                 // Se usa para resolver el algoritmo BFS 
#include <ctime>                 // Se usa para generar los numeros aleatorios
#include <chrono>                // Para medir el tiempo de ejecucion
#include <random>                // Para generar aleatoriedad en el laberinto
using namespace std;             // Permite escribir de forma legible y facil de entender

// Definimos las constantes para los elementos del laberinto
const char MURO = '|';
const char CAMINO = '.';
const char ENTRADA = 'E';
const char SALIDA = 'S';
const char RUTA = 'X';                          // Marca el camino resulto




