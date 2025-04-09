#include <ncurses.h>

int main() {
    initscr();                  
    printw("Hola mundo\n");     
    refresh();                  
    getch();                    
    endwin();                   
    return 0;
}

