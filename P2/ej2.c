#include <ncurses.h>

int main(void) {
    int rows, cols;

    initscr();

    if (!has_colors()) {
        endwin();
        printw("El terminal no tiene soporte de color\n");
        refresh();
        getch(); // Espera una tecla antes de salir
        return 1;
    }

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    clear();
    refresh();

    getmaxyx(stdscr, rows, cols);
    WINDOW *win = newwin(rows, cols, 0, 0);
    wbkgd(win, COLOR_PAIR(1));
    box(win, '|', '-');
    mvwprintw(win, 10, 10, "una cadena dentro de la ventana");
    wrefresh(win);

    getch();
    endwin();
    return 0;
}

