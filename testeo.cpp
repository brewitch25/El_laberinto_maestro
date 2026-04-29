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

 // BLOQUE DE GENERACION DE CAMINO DE SALIDA
// Varifica que el personaje este dentro de los limites de la matriz 
bool es_posicion_valida(int fila, int col, int alto, int ancho)
{
    return (fila >= 0 && fila < alto && col >= 0 && col < ancho);  
}

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

// << === >> RESOLVER LABERINTO USANDO BFS << === >>

//   ====>> FUNCION AUXILIAR: Reconstruye el camino de salida una vez resuelta la funcion de BFS << =====
// < -- QUE PARAMETROS RECIBE LA FUNCION -->
// vector<vector<char>>& matriz_laberinto = crea la matriz
// vector<vector<int>> padreF = posicion del padre en la fila
// vector<vector<int>> padreCol = posicion del padre en la columna
void reconstruir_travesia(vector<vector<char>>& matriz_laberinto, vector<vector<int>>& padreF, vector<vector<int>>&padreCol)
{
    int alto = matriz_laberinto.size();                         // fila
    int ancho = matriz_laberinto[0].size();                     // columna
    // Comenzamos desde la SALIDA "S"
    int coordenada_actual_Fila = padreF[alto - 1][ancho - 1];           // --| Posiciones de la salida en 
    int coordenada_actual_Col = padreCol[alto - 1][ancho - 1];          // --|      la matriz

    // Mientras no lleguemos a la casilla de entrada -> != INICIO
    while (coordenada_actual_Fila != 0 && coordenada_actual_Col != 0) 
    {
        // Marcamos la casilla actual como RUTA
        matriz_laberinto[coordenada_actual_Fila][coordenada_actual_Col] = RUTA;
        // Pasamos al padre de la casilla actual
        coordenada_actual_Fila = padreF[coordenada_actual_Fila][coordenada_actual_Col];
        coordenada_actual_Col = padreCol[coordenada_actual_Fila][coordenada_actual_Col];
    }
}

// Funcion resolverLaberintoBFS
bool resolverLaberintoBFS(vector<vector<char>>& matriz_laberinto)
{
    // Obtenemos el numero de FILAS de la matriz_laberinto
    int filas = matriz_laberinto.size();            //ALTO
    // Obtenemos el numero de COLUMNAS de la matriz laberinto
    int columnas = matriz_laberinto[0].size();      //ANCHO

    // Creamos la cola para almacenar las coordenadas (fila y columna)
    vector<int> cola_fila;
    vector<int> cola_columna;

    // Creamos la matriz visitados con el tamaño [filas][columnas]
    // Llenamos todas las matrices con el valor False(NO han sido visitadas aun)
    vector<vector<bool>> visitadas (filas, vector<bool>(columnas, false));

    // Crear una estructura para buscar de donde venimos Padres
    // Fila del padre 
    vector<vector<int>> padre_Fila (filas, vector<int>(columnas, -1));
    // Columna del padre 
    vector<vector<int>> padre_Columna (filas, vector<int>(columnas, -1));

    // Vamos a insertar coordenadas al final del vector(usando la fucion push_back)
    cola_fila.push_back(0);                 
    cola_columna.push_back(0);

    //Coordenadas de movimientos posible(arriba, abajo, izquierda, derecha)
    int mudaFila[] = {-1, 1, 0, 0};
    int mudaColumna[] = {0, 0, -1, 1};

    // Marcar Inicio como visitado
    visitadas[0][0] = true;

    // Mientras la cola no este vacia
    while(!cola_fila.empty())
    {
        // Extraer el 1er elemento(fila y columna)
        int filaActual = cola_fila[0];
        int columnaActual = cola_columna[0];

        // Borramos de la cola el elemento ya verificado
        cola_fila.erase(cola_fila.begin());
        cola_columna.erase(cola_columna.begin());

        // Si coordenada actual es igual a la SALIDA
        if (filaActual == (filas - 1) && columnaActual == (columnas - 1))
            {
                reconstruir_travesia(matriz_laberinto, padre_Fila, padre_Columna);
                return true;
            }
        // Por cada vecino (coordenadas de movimiento): 
        for (int i = 0; i < 4; i++)        // Iteramos en el indice (i) de las coordenadas
        {   // Calculamos las posiciones de filas y columnas de los vecinos
            int vecinoFila = filaActual + mudaFila[i];
            int vecinoColumna = columnaActual + mudaColumna[i];
            
            // Si los vecinos estan dentro de los limites de la matriz 
            // NO es MURO y NO ha sido visitado
            if (vecinoFila >= 0 && vecinoFila < filas &&
                vecinoColumna >= 0 && vecinoColumna < filas &&
                matriz_laberinto[vecinoFila][vecinoColumna] != MURO &&
                visitadas[vecinoFila][vecinoColumna] == false)
            {
                // Marcamos al vecino como visitado
                visitadas[vecinoFila][vecinoColumna] = true;
                // Guardamos al padre del vecino como coordenada actual
                padre_Fila[vecinoFila][vecinoColumna] = filaActual;
                padre_Columna[vecinoFila][vecinoColumna] = columnaActual;

                // Insertamos el vecino en la cola
                cola_fila.push_back(vecinoFila);
                cola_columna.push_back(vecinoColumna);
            }
        } 
    }
    return false;        // Si no hay salida
}

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

    vector<vector<char>> matriz_laberinto = vector<vector<char>>(alto, vector<char>(ancho, MURO));

    matriz_laberinto[0][0] = ENTRADA;
    matriz_laberinto[0][1] = CAMINO;
    matriz_laberinto[alto - 1][ancho - 1] = SALIDA;
    matriz_laberinto[alto - 2][ancho - 1] = CAMINO;
    
    // Registamos el tiempo antes de empezar - INICIO
    auto tiempo_inicial = chrono::steady_clock::now();
    // Definimos el inicio del algoritimo en la posicion (1,1)
    generar_camino_desde(1, 1, alto, ancho, matriz_laberinto);

    // Registramos el tiempo al terminar la funcion - FINAL
    auto tiempo_final = chrono::steady_clock::now();

    // Calculo de tiempo de ejecucion 
    chrono::duration<double> tiempo_de_ejecucion = tiempo_final - tiempo_inicial;

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
    if (resolverLaberintoBFS(matriz_laberinto)) 
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
    