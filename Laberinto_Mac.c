#include <stdio.h>
#include <stdlib.h>
#define AMARILLO_T "\x1b[33m"
#define RESET_COLOR    "\x1b[0m"
#define AMARILLO_F  "\x1b[43m"
#define BLANCO_F   "\x1b[47m"
#define F 16 //Como máximo 50 filas, apartir de ahí empieza a funcionar mal
#define C 17//En la pantalla caben como máximo 51 columnas, si ampliamos la terminal caben 63 máximo.
void llama_funciones(char matriz[F][C], char matrizaux[F][C]);
void imprime_matriz(char matriz[F][C]);
void crear_laberinto(char matriz[F][C], char matrizaux[F][C]);

int main()
{
    inicio();
    return 0;
}
void llama_funciones(char matriz[F][C], char matrizaux[F][C])
{
    crear_laberinto (matriz, matrizaux); //Cuando pulsas 111 sales de la función crear_laberinto
    printf("\033[2J\033[1;1H");
    Imprime_laberinto(matriz); //Imprime la matriz sustituyendo los ceros por espacios
    copia_en_fichero(matriz);
}
void crear_laberinto (char matriz[F][C], char matrizaux[F][C])
{
    int i, j, c, f, dist;
    char tipo;

    //borde del laberinto
    for ( i = 0; i < F; i++)
    {
        matriz[i][0]=' ';
        matriz[i][C-1]=' ';
    }

    //entrada y salida del laberinto

    /*matriz[0][0]=' ';
    matriz[0][1]=' ';
    matriz[0][2]=' ';
    matriz[F-1][C-1]=' ';
    matriz[F-1][C-2]=' ';
    matriz[F-1][C-3]=' ';*/
    
    //interior del laberinto
    for ( i = 0; i < F; i++)
    {
        for ( j = 1; j < C-1; j++)
        {
            if (i==1 && j==2)
            {
                matriz[i][j]='&';
            }
            else
            {
                matriz[i][j]='0';
            }
        }
    } 

    // inicializamos copia en matriz auxiliar
    for ( i = 0; i < F; i++)
    {
        for ( j = 0; j < C; j++)
        {
            matrizaux[i][j] = matriz[i][j];
        }
    }
    do
    {
        printf("\033[2J\033[1;1H");     
        imprime_matriz(matriz);
        printf("\n");
        printf("Debe construir el laberinto de forma que empieze en la fila 1 columna 2\n");
        printf("Introduzca primero la fila y luego la columna (para terminar pulse 111) (para hacer un UNDO pulse 120): \n");
        scanf(" %d", &f);

        // copia en matriz auxiliar para borrado última acción
        if (f==120)
        {
            for ( i = 0; i < F; i++)
            {
                for ( j = 0; j < C; j++)
                {
                    matriz[i][j] = matrizaux[i][j];
                }
            }
            imprime_matriz(matriz);

        } else
        {
            if (f==111) //si escribes 111 termina el búcle y pasa a la función Imprime_laberinto
            {
                break;
            }
            else
            {
                // copia de respaldo situación matriz en en matriz auxiliar
                for ( i = 0; i < F; i++)
                {
                    for ( j = 0; j < C; j++)
                    {
                        matrizaux[i][j] = matriz[i][j];
                    }
                }
                do
                {
                    scanf(" %d", &c);
                    if (c==0)
                    {
                        printf("No existe la columna 0, escriba otro número: ");
                    }
                } while (c==0);
                
        
                printf("Indique si quiere imprimir un punto (p) una fila(f) o una columna(c): \n");
                scanf(" %c", &tipo);
                if (tipo=='p' || tipo=='P')
                {
                    matriz[f][c]='*';
                    /*matriz[f+1][c]='';
                    matriz[f][c+1]='*';
                    matriz[f+1][c+1]='';*/
                }
                else if (tipo=='f' || tipo=='F')
                {
                    printf("Introduzca la longitud de la fila: \n");
                    scanf(" %d", &dist);
                    if (dist+c>=C)  //Si introduces una distancia demasiado grande el programa lo detecta.
                    {
                        dist=C-c-1;
                    }
                    for ( i = 0; i < dist; i++)
                    {
                        matriz[f][c+i]='*';
                    }
                }
                else if (tipo=='c' || tipo=='C')
                {
                    printf("Introduzca la longitud de la colulmna: \n");
                    scanf(" %d", &dist);
                    if (dist+f>=F)  //Si introduces una distancia demasiado grande el programa lo detecta.
                    {
                        dist=F-f;
                    }
                    for ( i = 0; i < dist; i++)
                    {
                        matriz[f+i][c]='*';
                    }
                }
            }
        }
    } while(1);
}
void imprime_matriz(char matriz[F][C])
{
    int i, j;
    for ( i = 0; i < F; i++)
    {   
        if (i!=0)
        {
            if (i<=9)
            {
                printf("0%d", i);
            }
            else
            {
                printf("%d", i);
            }
        }
        for ( j = 0; j < C; j++)
        {
            if (i==0 && j==0)
            {
                printf("     ");
            }
            
            if (i==0 && j!=C-1)
            {
                if (j!=0 && j<9)
                {
                    printf("  %d", j);
                }
                if (j==9)
                {
                    printf(" ");
                }

                if (j>=9 && j!=C-1)
                {
                    printf(" %d", j);
                }
                
            }
            if (i!=0)
            {
                if (matriz[i][j]=='*')
                {
                    printf(AMARILLO_F "  %c"RESET_COLOR, matriz[i][j]);
                }
                else
                {
                    printf("  %c", matriz[i][j]);
                }
            } 
        }
        printf("\n");
    }
}
