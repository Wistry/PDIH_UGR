#include <dos.h>
#include <stdio.h>

// Posiciona el cursor en (x,y)
void gotoxy(int x, int y) {
    union REGS regs;
    regs.h.ah = 0x02;
    regs.h.dh = y;
    regs.h.dl = x;
    int86(0x10, &regs, &regs);
}

// Controla el tipo de cursor: 0=invisible, 1=normal, 2=grueso
void setcursortype(int tipo) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;
    switch(tipo){
        case 0: // Invisible
            inregs.h.ch = 0x0A;
            inregs.h.cl = 0x00;
            break;
        case 1: // Normal
            inregs.h.ch = 0x0A;
            inregs.h.cl = 0x0A;
            break;
        case 2: // Grueso
            inregs.h.ch = 0x00;
            inregs.h.cl = 0x0A;
            break;
    }
    int86(0x10, &inregs, &outregs);
}

// Borra la pantalla (asume 80x25)
void clrscr(void) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x06;
    inregs.h.al = 0;       // borrar toda la pantalla
    inregs.h.bh = 0;       // color de fondo negro
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 24;      // última fila (25 filas)
    inregs.h.dl = 79;      // última columna (80 columnas)
    int86(0x10, &inregs, &outregs);
}

// Escribe un carácter en pantalla (modo teletipo)
void cputchar(char c) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x0E;
    inregs.h.al = c;
    int86(0x10, &inregs, &outregs);
}

// Lee y muestra un carácter (eco) del teclado
char getche(void) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;
    int86(0x21, &inregs, &outregs);
    return outregs.h.al;
}

// Dibuja un pixel en modo gráfico
void pixel(int x, int y, unsigned char color) {
    union REGS inregs, outregs;
    inregs.x.cx = x;
    inregs.x.dx = y;
    inregs.h.al = color;
    inregs.h.ah = 0x0C;
    int86(0x10, &inregs, &outregs);
}

// Extra: Dibuja un cuadrado en modo gráfico
void drawSquare(int x, int y, int side, unsigned char color) {
    int i;
    for(i = 0; i < side; i++){
        pixel(x + i, y, color);
        pixel(x + i, y + side - 1, color);
    }
    for(i = 0; i < side; i++){
        pixel(x, y + i, color);
        pixel(x + side - 1, y + i, color);
    }
}

int main() {
    // Ejemplo en modo texto
    clrscr();
    gotoxy(10, 5);
    printf("Hola Mundo!");
    setcursortype(0);  // Cursor invisible
    cputchar('A');
    char ch = getche();

    // Cambiar a modo gráfico CGA (modo 4)
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    inregs.h.al = 4;
    int86(0x10, &inregs, &outregs);

    // Dibuja un cuadrado en modo gráfico
    drawSquare(50, 50, 40, 2);

    // Pausa hasta pulsar una tecla
    getche();

    // Regresar a modo texto (modo 3)
    inregs.h.ah = 0x00;
    inregs.h.al = 3;
    int86(0x10, &inregs, &outregs);

    return 0;
}
