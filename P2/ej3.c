#include <ncurses.h>

int main() {
    int x = 10, y = 10;
    int ch;

    initscr();
    keypad(stdscr, TRUE);  
    noecho();              
    curs_set(FALSE);       

    mvaddch(y, x, 'O');    
    refresh();

    while((ch = getch()) != KEY_F(1)) {
        mvaddch(y, x, ' '); 
        switch(ch) {
            case KEY_UP: y--; break;
            case KEY_DOWN: y++; break;
            case KEY_LEFT: x--; break;
            case KEY_RIGHT: x++; break;
        }
        mvaddch(y, x, 'O'); 
        refresh();
    }

    endwin();
    return 0;
}

