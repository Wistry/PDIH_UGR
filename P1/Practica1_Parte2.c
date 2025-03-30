#include <stdio.h>
#include <conio.h>
#include <dos.h>

/* Definiciones de colores */
#define MY_BLACK     0
#define MY_BLUE      1
#define MY_GREEN     2
#define MY_CYAN      3
#define MY_RED       4
#define MY_MAGENTA   5
#define MY_BROWN     6
#define MY_LIGHTGRAY 7
#define MY_DARKGRAY  8
#define MY_LIGHTBLUE 9
#define MY_LIGHTGREEN 10
#define MY_LIGHTCYAN  11
#define MY_LIGHTRED   12
#define MY_LIGHTMAGENTA 13
#define MY_YELLOW     14
#define MY_WHITE      15

/* Variable global para el atributo de texto */
static unsigned char current_attr = 0x07;

/* Declaración de variables para bucles (compatibilidad C89) */
int i;

/* Funciones personalizadas */
void my_setvideomode(int mode) {
    union REGS regs;
    regs.h.ah = 0x00;
    regs.h.al = (unsigned char)mode;
    int86(0x10, &regs, &regs);
}

int my_getvideomode() {
    union REGS regs;
    regs.h.ah = 0x0F;
    int86(0x10, &regs, &regs);
    return (int)regs.h.al;
}

void my_textcolor(int color) {
    current_attr = (current_attr & 0xF0) | (color & 0x0F);
    textattr(current_attr);
}

void my_textbackground(int color) {
    current_attr = (current_attr & 0x0F) | ((color & 0x0F) << 4);
    textattr(current_attr);
}

void my_putpixel(int x, int y, int color) {
    union REGS regs;
    regs.h.ah = 0x0C;
    regs.h.al = (unsigned char)color;
    regs.x.cx = x;
    regs.x.dx = y;
    int86(0x10, &regs, &regs);
}

/* Función para dibujar arte ASCII con colores */
void dibujar_gato() {
    my_textcolor(MY_LIGHTGRAY);
    cprintf("  /\\_/\\\r\n");
    my_textcolor(MY_BROWN);
    cprintf(" ( o.o )\r\n");
    my_textcolor(MY_YELLOW);
    cprintf("  > ^ <\r\n");
    my_textcolor(MY_WHITE);
    cprintf("  /   \\\r\n");
    my_textcolor(MY_LIGHTGRAY);
    cprintf(" (     )\r\n");
    my_textcolor(MY_RED);
    cprintf("  \"   \"\r\n");
}

int main() {
    /* Mostrar modo de video actual */
    printf("Modo de video actual: %d\n", my_getvideomode());
    getch();
    
    /* Cambiar a modo texto */
    my_setvideomode(0x03);
    clrscr();
    
    /* Dibujar arte ASCII con colores */
    my_textbackground(MY_BLACK);
    dibujar_gato();
    
    /* Demostración colores texto */
    my_textcolor(MY_RED);
    my_textbackground(MY_WHITE);
    cprintf("\r\nTexto en rojo con fondo blanco\r\n");
    
    my_textcolor(MY_YELLOW);
    my_textbackground(MY_BLUE);
    cprintf("Texto en amarillo con fondo azul\r\n\r\n");
    
    /* Cambiar a modo gráfico */
    printf("Presione una tecla para modo grafico...\n");
    getch();
    
    my_setvideomode(0x13);  /* Modo VGA 320x200 256 colores */
    
    /* Dibujar píxeles */
    for (i = 0; i < 50; i++) {
        my_putpixel(100 + i, 50 + i, MY_RED);
        my_putpixel(200 - i, 50 + i, MY_BLUE);
        my_putpixel(150, 100 + i, MY_GREEN);
    }
    
    /* Esperar tecla */
    getch();
    
    /* Volver a modo texto y mostrar modo actual */
    my_setvideomode(0x03);
    clrscr();
    printf("Modo de video actual: %d\n", my_getvideomode());
    
    /* Dibujar arte ASCII nuevamente */
    my_textbackground(MY_BLUE);
    dibujar_gato();
    
    printf("\nPrograma terminado.\n");
    
    return 0;
}
