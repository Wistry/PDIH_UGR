#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * Función para mostrar la pantalla de inicio del juego.
 * Muestra el título, instrucciones y creadores
 */
void ventana_inicio() {
    clear();
    int center_x = COLS / 2; // Centro de la pantalla
    int center_y = LINES / 2; // Centro de la pantalla

    // Título del juego
    mvprintw(center_y - 7, center_x - 20, "===========================================");
    mvprintw(center_y - 6, center_x - 20,  "=================== PONG =================");
    mvprintw(center_y - 5, center_x - 20, "===========================================");

    // Instrucciones
    mvprintw(center_y, center_x - 20, "Jugador 1: Teclas W/S");
    mvprintw(center_y + 1, center_x - 20, "Jugador 2: Flechas Arriba/Abajo");

    // Créditos
    mvprintw(center_y + 3, center_x - 20, "Desarrollado por:");
    mvprintw(center_y + 4, center_x - 20, "William Patrick Quinn Cortes y Laura Riesco");

    // Mensaje para comenzar
    mvprintw(center_y + 6, center_x - 20, "Presiona cualquier tecla para comenzar...");
    mvprintw(center_y + 7, center_x - 20, "Presiona 'Q' para salir");

    refresh();
    getch(); // Esperar a que el usuario presione una tecla
}

/**
 * Función para mostrar la pantalla de fin de juego.
 * Muestra el ganador y opciones para reiniciar o salir.
 * @param ganador El número del jugador ganador (1 o 2)
 */
void ventana_finalizacion(int ganador) {
    clear();
    mvprintw(LINES/2 - 1, COLS/2 - 10, "JUGADOR %d GANA!", ganador); // Mensaje de victoria
    mvprintw(LINES/2 + 1, COLS/2 - 20, "Presiona 'R' para reiniciar o 'Q' para salir");
    refresh();
    
    // Menu para reiniciar o salir
    while(1) {
        int ch = getch();
        if (ch == 'r' || ch == 'R') break;
        else if (ch == 'q' || ch == 'Q') { endwin(); exit(0); }
    }
}

#define DELAY 65000 // Velocidad del juego, afecta a la velocidad de la pelota y de las palas

int main() {

    // Variables de la pelota
    int bola_x = 0, bola_y = 0; // Posición inicial de la pelota
    int bola_dir_x = 1, bola_dir_y = 1; // Dirección de la pelota (1 o -1)

    // Variables de las palas
    int pala_izq_y = 10, pala_drch_y = 10; // Posición inicial de las palas
    int pala_tam = 4; // Tamaño de las palas

    // Marcadores
    int marcador_izq = 0, marcador_drch = 0;

    // Configuración inicial de ncurses
    initscr();
    curs_set(FALSE);   
    noecho();           
    keypad(stdscr, TRUE); 

    // Desactivar modo no bloqueante para la pantalla de inicio
    nodelay(stdscr, FALSE);
    ventana_inicio(); // Pantalla de inicio
    nodelay(stdscr, TRUE); // Reactivar modo no bloqueante

    // Bucle principal del juego
    while (1) {
        clear();

        // Dibujar elementos
        // - Marcadores
        mvprintw(0, 5, "Jugador 1: %d", marcador_izq);
        mvprintw(0, COLS - 15, "Jugador 2: %d", marcador_drch);

        // - Palas
        for (int i = 0; i < pala_tam; i++) {
            mvaddch(pala_izq_y + i, 2, '|'); // Coloca en la posicion izquierda (2) la pala
            mvaddch(pala_drch_y + i, COLS - 3, '|');
        }

        // - Pelota
        mvaddch(bola_y, bola_x, 'O');

        // Actualizar pantalla
        refresh();

        // Controlar ganador
         // Verificar condición de victoria
         if (marcador_izq >= 5 || marcador_drch >= 5) {
            int winner = (marcador_izq >= 5) ? 1 : 2;
            ventana_finalizacion(winner);
            
            // Reiniciar variables del juego
            marcador_izq = 0;
            marcador_drch = 0;
            bola_x = COLS / 2;
            bola_y = LINES / 2;
            pala_izq_y = pala_drch_y = LINES/2 - 2;
        }

        // Lógica del juego
        usleep(DELAY);
        bola_x += bola_dir_x;
        bola_y += bola_dir_y;

        // Rebotar en bordes verticales
        if (bola_y <= 0 || bola_y >= LINES - 1) bola_dir_y *= -1;

        // Rebotar en palas
        if (bola_x == 3 && 
            bola_y >= pala_izq_y && 
            bola_y < pala_izq_y + pala_tam) {
            bola_dir_x *= -1;
        }

        if (bola_x == COLS - 4 && 
            bola_y >= pala_drch_y && 
            bola_y < pala_drch_y + pala_tam) {
            bola_dir_x *= -1;
        }

        // Puntuación
        if (bola_x <= 0) {
            marcador_drch++;
            bola_x = COLS / 2;
            bola_y = LINES / 2;
        } else if (bola_x >= COLS - 1) {
            marcador_izq++;
            bola_x = COLS / 2;
            bola_y = LINES / 2;
        }

        // Manejar entrada del teclado
        int ch = getch();
        switch(ch) {
            case 'w': if (pala_izq_y > 1) pala_izq_y-=2; break;
            case 's': if (pala_izq_y < LINES - pala_tam) pala_izq_y+=2; break;
            case KEY_UP: if (pala_drch_y > 1) pala_drch_y-=2; break;
            case KEY_DOWN: if (pala_drch_y < LINES - pala_tam) pala_drch_y+=2; break;
            case 'q': endwin(); return 0; // Salir con 'q'
        }
    }

    endwin();
    return 0;
}