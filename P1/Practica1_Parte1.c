#include <dos.h>

// --- Práctica 1. Entrada/Salida utilizando interrupciones con lenguaje C ---
// --- Parte realizada por William Patrick Quinn Cortes ---
// --- Asignatura: Perifericos y Dispositivos de interfaz humana ---

// --- Ejercicio 1: gotoxy(): coloca el cursor en una posición determinada ---
void gotoxy(int x, int y) {
    union REGS regs;
    regs.h.ah = 0x02; // Función para mover el cursor
    regs.h.dh = y; // Cordenada y (fila)
    regs.h.dl = x; // Cordenada x (columna)
    regs.h.bh = 0; // Pantalla activa (0 = pantalla actual)

    // LLamada a la interrupción 10h 
    int86(0x10, &regs, &regs);
}

// --- Ejercicio 2: setcursortype(): fijar el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL y GRUESO.
// setcursortype(): (0: INVISIBLE, 1: NORMAL, 2: GRUESO)
void setcursortype(int tipo) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x01; // Interrupcion que controla el tipo de cursor
    switch(tipo) {
        case 0: // Invisible
            inregs.h.ch = 0x20;  
            inregs.h.cl = 0x00;
            break;
        case 1: // Normal
            inregs.h.ch = 6;     
            inregs.h.cl = 7;     
            break;
        case 2: // Grueso
            inregs.h.ch = 0; // Empieza desde la fila 0 haciendo que sea grueso
            inregs.h.cl = 7;
            break;
        default:
            break;
    }
    int86(0x10, &inregs, &outregs);
}

// --- Ejercicio 3: clrscr(): borra toda la pantalla ---
void clrscr(void) {
    union REGS inregs, outregs;
    // Se borra la pantalla (función 06h de la BIOS)
    inregs.h.ah = 0x06;
    inregs.h.al = 0;       // Borrar toda la pantalla
    inregs.h.bh = 0x07;    // Color de fondo (por ejemplo, blanco sobre negro)
    
    // Posicones de la pantalla  aborrar
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 24;      // Última fila (25 filas en modo 80x25)
    inregs.h.dl = 79;      // Última columna (80 columnas)
    int86(0x10, &inregs, &outregs);
    
    // Reposicionar el cursor
    gotoxy(0, 0);
}

// --- Ejercicio 4: cputchar(): escribe un carácter en pantalla con el color indicado actualmente
void cputchar(char c) {
    union REGS regs;
    regs.h.ah = 0x0E; // Función para imprimir un carácter en modo texto
    regs.h.al = c;    
    regs.h.bh = 0;    
    regs.h.bl = 0x07; 
    int86(0x10, &regs, &regs); // Llamada a la interrupción 10h
}

// --- Ejercicio 5: getche(): obtiene un carácter de teclado y lo muestra en pantalla
char getche(void) {
    union REGS regs;
    char c; 

    // Leer un carácter del teclado
    regs.h.ah = 0x00; // Función para leer un carácter del teclado
    int86(0x16, &regs, &regs); // Llamada a la interrupción 16h
    c = regs.h.al; // Carácter leído

    // Imprimir el carácter en pantalla
    cputchar(c);

    return c; 
}

/* --- Función para dibujar un cuadro en modo gráfico ---
Implementar una función que permita dibujar un recuadro en la pantalla en modo texto. Recibirá como
parámetros las coordenadas superior izquierda e inferior derecha del recuadro, el color de primer plano y
el color de fondo.*/
void drawSquare(int x, int y, int side, unsigned char color) {
    union REGS inregs, outregs;
    int i;
    for(i = 0; i < side; i++) {
        // Línea superior
        inregs.x.cx = x + i; // Coordenada x
        inregs.x.dx = y; // Coordenada y
        inregs.h.al = color; // Color del pixel
        inregs.h.ah = 0x0C; // Función para dibujar un pixel
        int86(0x10, &inregs, &outregs); // Llamada a la interrupción 10h
        // Línea inferior
        inregs.x.cx = x + i;
        inregs.x.dx = y + side - 1;
        inregs.h.al = color;
        inregs.h.ah = 0x0C;
        int86(0x10, &inregs, &outregs);
    }
    for(i = 0; i < side; i++) {
        // Línea izquierda
        inregs.x.cx = x;
        inregs.x.dx = y + i;
        inregs.h.al = color;
        inregs.h.ah = 0x0C;
        int86(0x10, &inregs, &outregs);
        // Línea derecha
        inregs.x.cx = x + side - 1;
        inregs.x.dx = y + i;
        inregs.h.al = color;
        inregs.h.ah = 0x0C;
        int86(0x10, &inregs, &outregs);
    }
}

// --- Función para mostrar mensajes y pausar ---
void showMessage(const char *msg) {
    printf("\n%s", msg);
    getche();
    clrscr();
}

// --- Menú de opciones ---
void menuSetCursor(void); // Declaracion del menu

int main() {
    int opcion;
    union REGS inregs, outregs;
    char ch;
    
    // Configuración inicial: establecer cursor normal y limpiar pantalla
    setcursortype(1);
    clrscr();
    
    do {
         // Menú principal (alineado a la esquina superior izquierda)
        clrscr();
        gotoxy(2, 1);
        printf("Menu Principal - Ejercicios");
        gotoxy(2, 3);
        printf("1. gotoxy: Mover cursor y mostrar texto");
        gotoxy(2, 4);
        printf("2. setcursortype: Cambiar tipo de cursor");
        gotoxy(2, 5);
        printf("3. clrscr: Borrar la pantalla");
        gotoxy(2, 6);
        printf("4. cputchar: Escribir un caracter ('X')");
        gotoxy(2, 7);
        printf("5. getche: Leer y mostrar una tecla");
        gotoxy(2, 8);
        printf("6. Modo grafico: Dibujar un cuadrado");
        gotoxy(2, 9);
        printf("7. Salir");
        gotoxy(2, 11);
        printf("Elige una opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                // Forzar modo texto (modo 3) antes de usar gotoxy y printf
                inregs.h.ah = 0x00;
                inregs.h.al = 3;
                int86(0x10, &inregs, &outregs);
                clrscr();
                gotoxy(35, 12);
                printf("Hola Mundo!");
                showMessage("Presiona una tecla para volver al menu...");
                break;
                
            case 2:
                // Llama al submenú para cambiar el tipo de cursor
                menuSetCursor();
                break;
                
            case 3:
                clrscr();
                gotoxy(30, 12);
                printf("Pantalla borrada.");
                showMessage("Presiona una tecla para volver al menu...");
                break;
                
            case 4:
                clrscr();
                gotoxy(35, 12);
                cputchar('X');
                showMessage("Presiona una tecla para volver al menu...");
                break;
                
            case 5:
                clrscr();
                gotoxy(30, 12);
                printf("Pulsa una tecla: ");
                ch = getche();
                gotoxy(30, 13);
                printf("Tecla leida: %c", ch);
                showMessage("Presiona una tecla para volver al menu...");
                break;
                
            case 6:
                clrscr();
                // Cambiar a modo gráfico CGA (modo 4)
                inregs.h.ah = 0x00;
                inregs.h.al = 4;
                int86(0x10, &inregs, &outregs);

                drawSquare(50, 50, 40, 2); // Posicion (50,50), lado 40, color 2
                gotoxy(20, 24);
                printf("Cuadrado dibujado. Presiona una tecla para continuar...");
                getch();

                // Volver a modo texto (modo 3)
                inregs.h.ah = 0x00;
                inregs.h.al = 3;
                int86(0x10, &inregs, &outregs);
                break;
                
            case 7:
                clrscr();
                gotoxy(35, 12);
                printf("Saliendo del programa...");
                break;
                
            default:
                clrscr();
                gotoxy(30, 12);
                printf("Opcion invalida.");
                showMessage("Presiona una tecla para continuar...");
        }
    } while(opcion != 7);
    
    return 0;
}

// --- Submenú para cambiar el tipo de cursor ---
void menuSetCursor(void) {
    int op;
    do {
        clrscr();
        gotoxy(30, 2);
        printf("Submenu - Cambiar Tipo de Cursor");
        gotoxy(30, 4);
        printf("1. Cursor Invisible");
        gotoxy(30, 5);
        printf("2. Cursor Normal");
        gotoxy(30, 6);
        printf("3. Cursor Grueso");
        gotoxy(30, 7);
        printf("4. Volver al menu principal");
        gotoxy(30, 9);
        printf("Elige una opcion: ");
        scanf("%d", &op);
        
        clrscr();
        gotoxy(30, 5);
        switch(op) {
            case 1:
                setcursortype(0);
                printf("Cursor invisible activado.");
                break;
            case 2:
                setcursortype(1);
                printf("Cursor normal activado.");
                break;
            case 3:
                setcursortype(2);
                printf("Cursor grueso activado.");
                break;
            case 4:
                printf("Volviendo al menu principal...");
                break;
            default:
                printf("Opcion invalida.");
        }
        if(op != 4) {
            gotoxy(30, 7);
            printf("Presiona una tecla para continuar...");
            getch();
        }
    } while(op != 4);
}
