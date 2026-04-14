
PSEUDOCODIGO DEL PROGRAMA
INICIO DEL PROGRAMA
    // 1. Configuración
    MOSTRAR "Ingrese el ancho del laberinto:"
    LEER ancho
    MOSTRAR "Ingrese el alto del laberinto:"
    LEER alto
    
    CREAR matriz_laberinto[alto][ancho]
    INICIALIZAR todas las celdas como MURO (#)

    // 2. Medición de tiempo (Inicio)
    tiempo_inicio = OBTENER_TIEMPO_ACTUAL()

    // 3. Generación
    LLAMAR a GenerarLaberinto(matriz_laberinto, 1, 1)
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