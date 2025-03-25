pila segment stack 'stack'
    dw 100h dup (?)   
pila ends

datos segment 'data'
    msg db 'hola$'    
datos ends

codigo segment 'code'
    assume cs:codigo, ds:datos, ss:pila  ; Asocia registros de segmento
main PROC
    mov ax, datos     
    mov ds, ax

    mov dx, OFFSET msg  ; Carga la dirección de 'msg' en DX
    mov ah, 9           ; Función 9 de int 21h = imprimir cadena
    int 21h             ; Llama a MS-DOS

    mov ax, 4C00h       ; Función 4Ch de int 21h = terminar programa
    int 21h             ; Retorna al sistema operativo
main ENDP
codigo ends

END main               ; Punto de entrada del programa