#include <stdio.h>
#include <stdlib.h>
#define AMARILLO_T "\x1b[33m"
#define RESET_COLOR    "\x1b[0m"
#define AMARILLO_F  "\x1b[43m"
#define BLANCO_F   "\x1b[47m"
#define F 16 //Como máximo 50 filas, apartir de ahí empieza a funcionar mal
#define C 17//En la pantalla caben como máximo 51 columnas, si ampliamos la terminal caben 63 máximo.

int main()
{
    inicio();
    return 0;
}
