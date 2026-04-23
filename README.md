
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
// ==> Funcion resolverBFS <==
Busca el mejor camino y el mas corto, haciendo busqueda por anchura.
FUNCION resolverBFS(alto, ancho, matriz_laberinto)
    // 1. Preparación
    CREAR una COLA para guardar las posiciones a visitar
    CREAR una MATRIZ de "padres" para recordar de dónde venimos (para reconstruir el camino)
    CREAR una MATRIZ de "visitados" (booleana) para no caminar en círculos
    
    // 2. Punto de inicio
    posicion_inicial = (0, 0) // Donde está la 'E'
    INSERTAR posicion_inicial en la COLA
    MARCAR posicion_inicial como VISITADO
    
    // 3. Bucle principal de búsqueda
    MIENTRAS la COLA no esté vacía y sea mayor a cero o un numero entero positivo:
        posicion_actual = EXTRAER el primer elemento de la COLA
        
        // ¿Llegamos a la meta?
        SI matriz_laberinto[posicion_actual] es 'S':
            LLAMAR a reconstruir_camino(matriz_padres, posicion_actual)
            RETORNAR verdadero
            
        // Explorar vecinos (Arriba, Abajo, Izquierda, Derecha)
        PARA CADA direccion EN [N, S, E, O]:
            vecino = posicion_actual + direccion
            
            SI vecino está DENTRO del laberinto Y NO es MURO Y NO ha sido VISITADO:
                MARCAR vecino como VISITADO
                GUARDAR en MATRIZ_PADRES: "el padre de vecino es posicion_actual"
                INSERTAR vecino en la COLA
    FIN MIENTRAS

    RETORNAR falso // No se encontró salida
FIN FUNCION

// << === >> PSEUDOCODIGO FUNCION resolverDFS << === >>
El algoritmo de DFS(Depth Fisrt Search), comienza desde un vertice dado y explora un camino 
hasta lo más profundo, cuando llega a un vértice sin vecinos que visitar, retrocede al vértice anterior para explorar otros caminos sin visitar. Esto continúa hasta que se visitan todos los vértices alcanzables desde el origen.

//Antes de la funcion, definimos los movimientos posibles
// Representa los 4 movimientos posibles
// Arriba, abajo, izquierda, derecha 
dFila [] = {-1, 1, 0, 0}
dColumna [] = {0, 0, -1, 1}

Funcion resolverDFS(fila_actual, columna_actual, matriz_laberinto)
    // Caso base nº 1
    // Estamos fuera de los limites del laberinto?
    Si es_posicion_valida(fila_actual, columna_actual, alto, ancho) Ó 
        matriz_laberinto[fila_actual][columna_actual] == MURO
        retornar False      -> (Camino Bloqueado)
    // Caso base nº 2
    // Ya visitamos esta posicion?
    Si matriz_laberinto[fila_actual][columna] == RUTA Ó 
        matriz_laberinto[fila_actual][columna_actual] == 'visitado'
        retornar False
    // Caso base nº 3
    // Es la salida?
    Si matriz_laberinto[fila_actual][columna_actual] == SALIDA
        retornar True
    // Marcamos la ruta(por donde ya pasamos)
    Si matriz_laberinto[fila_actual][columna_actualmna] != ENTRADA 
        matriz_laberinto[fila_actual][columna_actual] == RUTA
    
    // Iteramos en las 4 posiciones posibles
    Para i desde 0 hasta 3
        variable nueva_fila = fila_actual + dFila[i]
        variable nueva_columna = columna_actual + dColumna[i]

        // Se usa la recursividad para la nueva posicion
        Si resolverDFS(nueva_fila, nueva_columna, matriz_laberinto) == True
            retornar True
    Fin 
    // Backtracking 
    // Si el bucle termino y nadie retorno True, este camino no funciona
    Si matriz_laberinto[fila_actual][columna_actual] != ENTRADA
        matriz_laberinto[fila_actual][columna_actual] == CAMINO
    Retornar Falso
Fin de la funcion




 