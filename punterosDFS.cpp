#include <iostream>              // Ayuda a que el programa pueda tener input y output
#include <ctime>                 // Se usa para generar los numeros aleatorios
#include <chrono>                // Para medir el tiempo de ejecucion
#include <cstdlib>               // Para generar aleatoriedad
using namespace std;             // Permite escribir de forma legible y facil de entender
// Definimos las constantes para los elementos del laberinto
const char SALIDA = 'S';
const char MURO = '#';
const char ENTRADA = 'E';
const char CAMINO = '.';
const char RUTA = 'X';                          // Marca el camino resulto

 // BLOQUE DE GENERACION DE CAMINO DE SALIDA
// Varifica que el personaje este dentro de los limites de la matriz 
bool es_posicion_valida(int fila, int col, int alto, int ancho)
{
    return (fila >= 0 && fila < alto && col >= 0 && col < ancho);  
}

void generar_camino_desde(int fila, int col, int alto, int ancho, char** matriz) 
{
    //Definimos las 4 direcciones(arriba, abajo, izquierda, derecha)
    // Usamos estructura simples para reprensentar el movimiento en filas y columnas
    int df[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    int indices [] = {0, 1, 2, 3};

    // Se selecciona un elemento al azar, recorriendo la lista (indices), de atras hacia adelante, por cada
    // posicion, elige al azar un elemento que esté antes de ella y los intercambia.
    for (int i = 3; i > 0; --i) 
    {
        int j = rand() % (i + 1);           // Elige un índice aleatorio entre 0 e i
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Se aplica el movimiento aleatorio
    for (int i = 0; i < 4; ++i) 
    {  // direccion_elegida -> indice que nos dice que direccion usar {0,1,2,3}
        int direccion_elegida = indices[i];

        // Calcula la nueva posicion, de 2 en 2 para mantener los MUROS
        int nueva_fila = fila + (df[direccion_elegida] * 2);
        int nueva_col = col + (dc[direccion_elegida] * 2);


        if (es_posicion_valida(nueva_fila, nueva_col, alto, ancho) && matriz[nueva_fila][nueva_col] == MURO)
        {
            //Marcamos el camino, la celda intermedia y el destino
            matriz[fila + df[direccion_elegida]][col + dc[direccion_elegida]] = CAMINO;       //Celda intermedia
            matriz[nueva_fila][nueva_col] = CAMINO;                                           // Celda destino

            // Usamos recursividad para seguir explorando desde la posicion actual
            generar_camino_desde(nueva_fila, nueva_col, alto, ancho, matriz);
        }
    }
}

// << === >> Funcion resolverDFS << === >>
bool resolverDFS(int fila_actual, int columna_actual, char** matriz, int filas, int columnas)
{
    char visitado = 'v';
    // Caso base limites
    if(fila_actual < 0 || fila_actual >= filas ||
        columna_actual < 0 || columna_actual >= columnas ||
        matriz[fila_actual][columna_actual] == MURO)
    {
        return false;
    }
    // Caso Base: Posicion visitada
    if (matriz[fila_actual][columna_actual] == RUTA ||
        matriz[fila_actual][columna_actual] == visitado)
        {
            return false;
        }
    // Caso base: Salida?
    if (matriz[fila_actual][columna_actual] == SALIDA) 
    {
        return true;
    }
    // Marcamos la ruta
    if (matriz[fila_actual][columna_actual] != ENTRADA)
    {
        matriz[fila_actual][columna_actual] = RUTA; 
    }
    // Definimos las movimientos a utilizar con sus respectivas coordenadas
    int dFila[] = {-1, 1, 0, 0};
    int dColumna[] = {0, 0, -1, 1};
    // Iteramos en las posiciones posibles(arriba, abajo, izquierda, derecha) 
    for (int i = 0; i < 4; i++)
    {   // Mira la posible posicion usando los indices de las posiciones
        int nueva_fila = fila_actual + dFila[i];
        int nueva_columna = columna_actual + dColumna[i];

        // Usamos recursividad para la nueva posicion
        if (resolverDFS(nueva_fila, nueva_columna, matriz, filas, columnas) == true)
        {
            return true;
        }
    }
 // Backtracking -> Termina el bucle y no se retorna un true, no sirve el camino explorado
    if (matriz[fila_actual][columna_actual] != ENTRADA)
        {
        matriz[fila_actual][columna_actual] = CAMINO;
        }
    return false;
}

int main() {

     // Inicializa los numeros aleatorios
    srand(time(NULL));
    // Inicializamos y declaramos las variables
    int filas, columnas;
    // Solicitar al usuario valor ancho (numero de filas)
    cout <<"Ingrese el valor para las filas del laberinto: "; cin >> filas;
    // Solicitar al usuario valor alto(numero de columnas)
    cout <<"Ingrese el valor para las columnas del laberinto: "; cin >> columnas;

    // --> RESERVA DE MEMORIA <--
    char** matriz = new char*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new char[columnas];
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = MURO;
        }
    }
        // Registamos el tiempo antes de empezar - INICIO
    auto tiempo_inicial = chrono::steady_clock::now();
    // Definimos el inicio del algoritimo en la posicion (1,1)
    generar_camino_desde(1, 1, filas, columnas, matriz);

    // Registramos el tiempo al terminar la funcion - FINAL
    auto tiempo_final = chrono::steady_clock::now();

    // Calculo de tiempo de ejecucion 
    chrono::duration<double> tiempo_de_ejecucion = tiempo_final - tiempo_inicial;
    // Marcamos entradas y salidas
    matriz[0][0] = ENTRADA;
    matriz[0][1] = CAMINO;
    matriz[filas - 1][columnas - 1] = SALIDA;
    matriz[filas - 2][columnas - 1] = CAMINO;

        // Visualizacion de la matriz generada
    cout <<"Laberinto Generado" << endl;
    for (int i = 0; i < filas; ++i)      // 1er bucle, recorre cada 
    {
        for (int j = 0; j < columnas; ++j)
        { cout << matriz[i][j] << " "; }
        // Al terminar de imprimir una fila, pasamos a la siguiente linea
        cout << endl;
    }
    // Mostramos el tiempo de ejecucion del laberinto
    cout<<"La ejecucion tardo: "<< tiempo_de_ejecucion.count() <<"segundos"<<endl;
    // (Aquí llenarías el laberinto con un bucle o leyendo un archivo)

    // --- LLAMADA A LA FUNCIÓN ---
    if (resolverDFS(0, 0, matriz, filas, columnas)) {
        cout << "¡Salida encontrada!" << endl;

         for (int i = 0; i < filas; ++i)      // 1er bucle, recorre cada 
        {
            for (int j = 0; j < columnas; ++j)
            { cout << matriz[i][j] << " "; }
            // Al terminar de imprimir una fila, pasamos a la siguiente linea
            cout << endl;
        }
    }

    // --> LIBERACIÓN DE MEMORIA <--
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}