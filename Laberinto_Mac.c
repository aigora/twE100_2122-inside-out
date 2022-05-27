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
void Imprime_laberinto(char matriz[F][C]);
void copia_en_fichero(char matriz[F][C]);
void inicio();



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

void Imprime_laberinto(char matriz[F][C])
{
    int i, j;
    for ( i = 0; i < F; i++)
    {   
        if (i!=0)
        {
            if (i<=9)
            {
                printf("  ");
            }
            else
            {
                printf(" ");
            }
        }
        for ( j = 0; j < C; j++)
        {
            if (i==0 && j==0)
            {
                printf("     ");
            }
            
            if (i==0)
            {
                if (j!=0 && j<=9)
                {
                    printf("   ");
                }
                if (j>9 && j!=C-1)
                {
                    printf("  ");
                }
            }
            if (i!=0)
            {
                if (matriz[i][j]=='0') 
                {
                    matriz[i][j]=' '; //donde había ceros coloca un espacio
                }
                if (matriz[i][j]=='*')
                {
                    printf( AMARILLO_F"  %c"RESET_COLOR, matriz[i][j]);
                }
                else
                {
                    printf( "  %c", matriz[i][j]);
                }
            }
        }
        printf("\n");
    }
}

void copia_en_fichero(char matriz[F][C])
{
    FILE *pf;
    int i, j, t=0;
    char g;
    // Abrimos fichero para escritura
    printf("Elija donde quiere guardar el laberinto (1, 2, 3 o 4): ");

    do
    {
        scanf(" %c", &g);
        switch (g)
        {
            case '1':
                pf = fopen("Laberinto 1.txt", "w");
                t=1;
                break;
            case '2':
                pf = fopen("Laberinto 2.txt", "w");
                t=1;
                break;
            case '3':
                pf = fopen("Laberinto 3.txt", "w");
                t=1;
                break;
            case '4':
                pf = fopen("Laberinto 4.txt", "w");
                t=1;
                break;
            default:

            printf("Input no válido\n");
                break;
        }
    }while (t==0);

    if (pf == NULL) 
    {   
        // Si el resultado es NULL mensaje de error
        printf("Error al abrir el fichero.\n");
    }
    else 
    {   
        // Si ha funcionado, comienza escritura
        fprintf(pf, "%d", F-1);
        fprintf(pf, "\n");
        fprintf(pf, "%d", C-2);
        fprintf(pf, "\n");

        for ( i = 1; i < F; i++)
        {
            for ( j = 1; j < C-1; j++)
            {   
                if (matriz[i][j]=='*')
                {
                    fprintf(pf, "1");
                }
                else
                {
                fprintf(pf, "0");
                }
            }
            fprintf(pf, "\n");
        }
        fclose(pf);
    }

} 

void inicio()
{
    char matriz[F][C];
    char matrizaux[F][C];
    char opcion;
   
    int t=0;
    
    printf("   ------------------------\n");
    printf("  -  M E N Ú  de J U E G O  -  \n");
    printf("   ------------------------\n\n");
    printf(" A. Laberinto 1  \n");
    printf(" B. Laberinto 2  \n");
    printf(" C. Laberinto 3  \n");
    printf(" D. Laberinto 4  \n");
    printf(" E. Crer laberinto \n");

    do
    {
        scanf (" %c", &opcion);

        switch (opcion)
        {
            case 'a':
            case 'A':
 
                printf("Bienvenido al laberinto 1\n\n");
                lectura_de_fichero(1);
                t=1;
                break;

            case 'b':
            case 'B':
   
                printf("Bienvenido al laberinto 2\n\n");
                lectura_de_fichero(2);
                t=1;
                break;

            case 'c':
            case 'C':

                printf("Bienvenido al laberinto 3\n\n");
                lectura_de_fichero(3);
                t=1;
                break;

            case 'd':
            case 'D':
    
                printf("Bienvenido al laberinto 4\n\n");
                lectura_de_fichero(4);
                t=1;
                break;

            case 'e':
            case 'E':
    
            printf("¡¡Crea tu propio laberinto!!\n\n");
    
            t=1;
            llama_funciones(matriz, matrizaux);
            break;

            default:

            printf("LETRA INCORRECTA!!!! VUELVE A INTENTARLO <\n\n");
            break;
        }
    }while (t==0);

}
