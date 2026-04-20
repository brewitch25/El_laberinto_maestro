
PSEUDOCODIGO DEL PROGRAMA
INICIO DEL PROGRAMA
    // 1. Configuración
    MOSTRAR "Ingrese el ancho del laberinto:"       -
    LEER ancho
    MOSTRAR "Ingrese el alto del laberinto:"
    LEER alto
    
    CREAR matriz_laberinto[alto][ancho]
    INICIALIZAR todas las celdas como MURO (|)

    // 2. Medición de tiempo (Inicio)
    tiempo_inicio = OBTENER_TIEMPO_ACTUAL()

    // 3. Generación
    LLAMAR a generar_camino_desde(1,1 matriz_laberinto)
    MARCAR Entrada 'E' y Salida 'S'

    // 4. Resolución
    MOSTRAR "Resolviendo..."
    ruta_encontrada = LLAMAR a ResolverBFS(matriz_laberinto)

    // 5. Medición de tiempo (Fin)
    tiempo_fin = OBTENER_TIEMPO_ACTUAL()

    // 6. Visualización Final
    DIBUJAR_LABERINTO(matriz_laberinto con la ruta marcada '*')
    MOSTRAR "Tiempo de ejecución: " + (tiempo_fin - tiempo_inicio)
FIN


// Funcion para generar los caminos del laberinto
// utilizando backtracking para asegurar que al menos
// un camino conecte la entrada con la salida
FUNCION generar_camino_desde(fila, col, MATRIZ)
    // Obtener direcciones aleatorias (Norte, Sur, Este, Oeste)
    LISTA direcciones = barajar_aleatoriamente([N, S, E, O])
    
    PARA CADA dir EN direcciones:
        Calcular nueva_fila y nueva_col (saltando 2 espacios para dejar paredes)
        
        SI (nueva_fila y nueva_col están dentro del rango) Y (es una PARED):
            Romper la pared entre (fila, col) y (nueva_fila, nueva_col)
            Marcar (nueva_fila, nueva_col) como CAMINO
            
            // Recursión: seguir explorando desde la nueva posición
            generar_camino_desde(nueva_fila, nueva_col, MATRIZ)
    FIN PARA
FIN FUNCION
// Funcion auxilar es_posicion_valida, a utilizar en la funcion generar_camino_desde
// verifica que los movimientos esten dentro de la matriz
// -> Parametros que recibe: int (filas, columnas, alto y ancho)
// -> Valor que devuelve: boolean (true o false)
FUNCION es_posicion_valida(fila, columna, ancho, alto)
    RETORNA True -> dentro de la matriz;    False -> Fuera de la matriz

// FUNCION QUE CAPTURA EL TIEMPO DE INICIO Y EL FINAL DE TIEMPO DE EJECUCION DE LA FUNCION
// Que parametros recibe, la funcion "chrono::steady_clock::now(), de la libreria chrono.
// Devuelve un numero, el tiempo en el que inicio a correr la ejecucion y el tiempo en el que finalizo la 
// ejecucion de la funcion 
auto tiempo(inicial, final) = chrono::steady_time::now()

// TIEMPO TOTAL DE TIEMPO DE EJECICION DE LA FUNCION generar_laberinto_desde
// Devuelve un numero, que es el tiempo total de ejecucion
diferencia (resta) tiempo final - tiempo inicial

 // <<===>> PSEUDOCODIGOS FUNCION BFS <<===>>
 // -- > Funcion auxiliar reconstruir_camino <--
 Se encarga de dibujar el camino de salida del mapa, la solucion. Una vez que la funcion BFS encuentra la salida, esta funcion retrocede (de la salida a la entrada), marcado el camino recorrido 
 con el caracter X
 FUNCION recostruir_camino(matriz_padres(filas, columnas), posicion_salida, matriz_laberinto)
    // Comenzamos del final
    posicion_actual = posicion_salida

    // Retrocedemos hasta encontrar el inicio
    La pista termina cuando llegamos a la celda que no tiene "padre" ENTRADA
    Mientras que la psocion_actual NO sea posicion_entrada
        
        // Obtenemos la celda desde donde llegamos a la celda actual
        posicion_anterior = matriz_padres[posicion_actual]
        
        // Marcamos el camino en el laberinto
        // Solo marcamos si no es ENTRADA y SALIDA para no borrar el camino
        SI matriz_laberinto[posicion_anterior] NO ES ENTRADA:
            matriz_laberinto[posion_anterior] = RUTA (marcar con X)

        // Movemos nuestro personaje hacia atras
        posicion_actual = posicion anterior 
    FIN (funcion auxiliar)
    



 