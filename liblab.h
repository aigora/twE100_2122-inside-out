#ifndef _LIBRERIA
#define _LIBRERIA

#include <stdlib.h>


#ifdef _WIN32        // si compilamos en win32 /win64

    #include <conio.h>

#endif

#define F 16 //Como máximo 50 filas, apartir de ahí empieza a funcionar mal
#define C 17//En la pantalla caben como máximo 51 columnas, si ampliamos la terminal caben 63 máximo.
#define RESET_COLOR    "\x1b[0m"
#define AMARILLO_F  "\x1b[43m"
#define BLANCO_F   "\x1b[47m"
#define VERDE_F        "\x1b[42m"
#define AZUL_F      "\x1b[44m"
#define MAGENTA_F  "\x1b[45m"
#define ROJO_F     "\x1b[41m"

void copiamatriz(int fil, int col, char* m1, char* m2);
void imprime_matriz(char matriz[F][C]);
char leertecla();

#include  "liblab.c"

#endif
