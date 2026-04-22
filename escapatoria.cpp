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
const char CAMINO = '.';
const char RUTA = 'X';                          // Marca el camino resulto

//  <<==>> Indice de todas las funciones a usar en main <<==>>
void generar_camino_desde(int fila, int col, int alto, int ancho, vector<vector<char>>& matriz);
bool es_posicion_valida(int fila, int col, int alto, int ancho);
void reconstruir_camino(vector<vector<int>>& padre_fila, vector<vector<int>>& padre_col,
                        int fila_salida, int col_salida, vector<vector<char>>& matriz_laberinto);
bool resolverBFS(int alto, int ancho, vector<vector<char>>& matriz_laberinto);

int main() 
{    
    // Inicializa los numeros aleatorios
    srand(time(NULL));
    
    // Inicializamos y declaramos las variables
    int alto, ancho;
    // Solicitar al usuario valor ancho (numero de filas)
    cout <<"Ingrese el valor para el alto del laberinto: "; cin >> alto;
    // Solicitar al usuario valor alto(numero de columnas)
    cout <<"Ingrese el valor para el ancho del laberinto: "; cin >> ancho;

    // Inicializo el laberinto lleno de MUROS
    vector<vector<char>> matriz_laberinto = vector<vector<char>>(alto, vector<char>(ancho, MURO));

    // Definimos la entrada(esquina superior derecha)
    matriz_laberinto[0][0] = ENTRADA;

    // Permite que el jugador pase de la entrada al resto del laberinto
    matriz_laberinto[0][1] = CAMINO;

    // Registamos el tiempo antes de empezar - INICIO
    auto tiempo_inicial = chrono::steady_clock::now();

    // Definimos el inicio del algoritimo en la posicion (1,1)
    generar_camino_desde(1, 1, alto, ancho, matriz_laberinto);

    // Registramos el tiempo al terminar la funcion - FINAL
    auto tiempo_final = chrono::steady_clock::now();

    // Calculo de tiempo de ejecucion 
    chrono::duration<double> tiempo_de_ejecucion = tiempo_final - tiempo_inicial;

    // Permite que el jugador pase de la entrada al resto del laberinto
    matriz_laberinto[0][1] = CAMINO;
    matriz_laberinto[1][1] = CAMINO;

    // Definimos la salida, se crean los dos caminos para que la salida no se encuentren rodeadas
    // de paredes, hace que se pueda acceder a la salida
    matriz_laberinto[alto - 1][ancho - 1] = SALIDA;
    matriz_laberinto[alto - 2][ancho - 1] = CAMINO;
    //matriz_laberinto[alto - 2][ancho - 2] = CAMINO;

    
    // Visualizacion de la matriz generada
    cout <<"Laberinto Generado" << endl;
    for (int i = 0; i < alto; ++i)      // 1er bucle, recorre cada 
    {
        for (int j = 0; j < ancho; ++j)
        { cout << matriz_laberinto[i][j] << " "; }
        // Al terminar de imprimir una fila, pasamos a la siguiente linea
        cout << endl;
    }
    // Mostramos el tiempo de ejecucion del laberinto
    cout<<"La ejecucion tardo: "<< tiempo_de_ejecucion.count() <<"segundos"<<endl;
    
    
    // BLOQUE DE RESOLUCION DE LA FUNCION resolverBFS
    cout << "Buscando escapatoria del laberinto.. Resolviendo BFS" << endl;
    if (resolverBFS(alto, ancho, matriz_laberinto)) 
    {
        cout<< "Ruta encontrada :)! La ruta se ha marcado con '"<< RUTA << endl;
    } else {
        cout << "No se ha encontrado una ruta de salida :( " << endl;
    }
    // Mostramos el laberinto final
    cout << "Mapa de salida del laberinto" << endl;
    for (int i = 0; i < alto; i++)
    {
        for (int j = 0; j < ancho; j++) 
        {
            // Imprimimos los caracteres del laberinto
            cout << matriz_laberinto[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}


 // << === >> FUNCIONES A USAR EN EL MAIN << === >> //

void generar_camino_desde(int fila, int col, int alto, int ancho, vector<vector<char>>& matriz) 
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

// Varifica que el personaje este dentro de los limites de la matriz 
bool es_posicion_valida(int fila, int col, int alto, int ancho)
{
    return (fila >= 0 && fila < alto && col >= 0 && col < ancho);  
}

// << === >> Bloque BFS << === >>
void reconstruir_camino(vector<vector<int>>& padre_fila, vector<vector<int>>& padre_col, int fila_salida,
                        int col_salida, vector<vector<char>>& matriz_laberinto)
{
    // Empezamos del final(Salida)
    int f_actual = fila_salida;
    int c_actual = col_salida;

    // Retrocedemos mientras la fila del padre sea valida, diferente sea positivo
    while (padre_fila[f_actual][c_actual] >= 0) 
    {
        // Guardamos temporalmente quien es el padre, antes de movernos
        int f_anterior = padre_fila[f_actual][c_actual];
        int c_anterior = padre_col[f_actual][c_actual];

        // Nos movemos en la posicion del padre
        f_actual = f_anterior;
        c_actual = c_anterior;

        // Marcamos con "X" = RUTA, en caso de no ser la Entrada
        if(matriz_laberinto[f_actual][c_actual] != ENTRADA) 
        { 
            matriz_laberinto[f_actual][c_actual] = RUTA;
        }
    }
}

//  <<===>> FUNCION resolverBFS <<===>>
bool resolverBFS(int alto, int ancho, vector<vector<char>>& matriz_laberinto)
{
    // matrices para guardar la posicion de los padres
    vector<vector<int>> padre_fila(alto, vector<int>(ancho, -1));
    vector<vector<int>> padre_col(alto, vector<int>(ancho, -1));

    // Generamos la cola con vectores y el indice "frente"(primer elemento de la fila)
    vector<int> cola_f;
    vector<int> cola_c;
    int frente = 0;         //Este indice nos dice, quien tiene que ser procesado

    // Comenzamos en la Entreda, posicion [0,0]
    cola_f.push_back(0);
    cola_c.push_back(0);
    padre_fila[0][0] = -2;      // Marca para no volver a la entrada 
    padre_col[0][0] = -2;       // Marca para no volver a la entrada 

    // Direcciones: arriba, abajo, izquierda, derecha
    int cambio_fila[] = {-1, 1, 0, 0};
    int cambio_columna[] = {0, 0, -1, 1};

    // Bucle principal: mientras el frente, no llegue al final de la lista
    while (frente < cola_f.size())
    {
        // Obtenemos el elemento a procesar, el "frente"
        int f_actual = cola_f[frente];
        int col_actual = cola_c[frente];
        frente++;                               // Marcamos, sumamos moviendo el frente al siguiente

        // Encontramos la salida?
        if (matriz_laberinto[f_actual][col_actual] == SALIDA)   
        {
            reconstruir_camino(padre_fila, padre_col, f_actual, col_actual, matriz_laberinto);
            return true;
        }
        // Verificamos las 4 direcciones (iteramos en el indice)
        for (int i = 0; i < 4; i++)
        {
            // Calculamos la fila y columna del vecino que estamos verificando
            int fila_vecino = f_actual + cambio_fila[i];
            int col_vecino = col_actual + cambio_columna[i];

            // Verificamos que la posicion del vecino sea valida para transitar
            if (fila_vecino >= 0 && fila_vecino < alto && 
                col_vecino >= 0 && col_vecino < ancho && 
                matriz_laberinto[fila_vecino][col_vecino] != MURO && 
                padre_fila[fila_vecino][col_vecino] == -1)
            {
                // Guardamos el rastro
                padre_fila[fila_vecino][col_vecino] = f_actual;
                padre_col[fila_vecino][col_vecino] = col_actual;

                // Agregamos a la lista de espera
                cola_f.push_back(fila_vecino);
                cola_c.push_back(col_vecino);
            }
        }
    }
    return false;       // Si no hay salida
}

