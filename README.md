
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
