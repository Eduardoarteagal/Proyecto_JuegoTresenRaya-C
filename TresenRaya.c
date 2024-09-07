#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define JUGADOR 'X'
#define IA 'O'

char tablero[3][3];

// Inicializa el tablero vacío
void inicializarTablero() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j] = ' ';
        }
    }
}

// Muestra el tablero en la consola
void mostrarTablero() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", tablero[i][j]);
            if (j < 2) printf("|");
        }
        if (i < 2) printf("\n---|---|---\n");
    }
    printf("\n");
}

// Verifica si hay un ganador
char verificarGanador() {
    // Verificar filas y columnas
    for (int i = 0; i < 3; i++) {
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2] && tablero[i][0] != ' ') {
            return tablero[i][0];
        }
        if (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i] && tablero[0][i] != ' ') {
            return tablero[0][i];
        }
    }
    // Verificar diagonales
    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2] && tablero[0][0] != ' ') {
        return tablero[0][0];
    }
    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0] && tablero[0][2] != ' ') {
        return tablero[0][2];
    }
    return ' ';
}

// Verifica si hay espacios vacíos en el tablero
int hayEspacios() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == ' ') return 1;
        }
    }
    return 0;
}

// Turno del jugador humano
void turnoJugador() {
    int fila, columna;
    do {
        printf("Ingresa fila y columna (1-3) separados por un espacio: ");
        scanf("%d %d", &fila, &columna);
        fila--; columna--; // Para que sea indexado desde 0
    } while (tablero[fila][columna] != ' ');

    tablero[fila][columna] = JUGADOR;
}

// Turno de la IA
void turnoIA() {
    int fila, columna;
    srand(time(0));
    do {
        fila = rand() % 3;
        columna = rand() % 3;
    } while (tablero[fila][columna] != ' ');

    tablero[fila][columna] = IA;
    printf("La IA ha jugado en la fila %d, columna %d\n", fila + 1, columna + 1);
}

int main() {
    char ganador = ' ';
    inicializarTablero();
    printf("¡Bienvenido al Tres en Raya!\n");

    while (ganador == ' ' && hayEspacios()) {
        mostrarTablero();
        turnoJugador();
        ganador = verificarGanador();
        if (ganador != ' ' || !hayEspacios()) break;
        turnoIA();
        ganador = verificarGanador();
    }

    mostrarTablero();
    if (ganador == JUGADOR) {
        printf("¡Felicidades, ganaste!\n");
    } else if (ganador == IA) {
        printf("La IA ha ganado. ¡Suerte la próxima vez!\n");
    } else {
        printf("Es un empate.\n");
    }

    return 0;
}
