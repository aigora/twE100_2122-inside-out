#include <stdio.h>
#include <stdlib.h>
#define RESET_COLOR    "\x1b[0m"
#define AMARILLO_F  "\x1b[43m"
#define BLANCO_F   "\x1b[47m"
#define VERDE_F        "\x1b[42m"
#define AZUL_F      "\x1b[44m"
#define MAGENTA_F  "\x1b[45m"
#define ROJO_F     "\x1b[41m"
#define F 16 //Como máximo 50 filas, apartir de ahí empieza a funcionar mal
#define C 17//En la pantalla caben como máximo 51 columnas, si ampliamos la terminal caben 63 máximo.

void llama_funciones(char matriz[F][C], char matrizaux[F][C]);
void imprime_matriz(char matriz[F][C]);
void crear_laberinto(char matriz[F][C], char matrizaux[F][C]);
void Imprime_laberinto(char matriz[F][C]);
void copia_en_fichero(char matriz[F][C]);
void inicio();
void lectura_de_fichero(int n);
int movimiento (int matriz[100][100], int fil, int col, char color);
char leertecla();
void historial(int movimiento, int laberinto);
void lectura_del_historial();
void imprime_estadisticas();

typedef struct 
{
    int movimientos;
    int record;
}estadisticas;


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
    int i, j, c, f, dist, g;
    char tipo;

    for ( i = 0; i < F; i++)
    {
        matriz[i][0]=' ';
        matriz[i][C-1]=' ';
    }
    
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
                printf("Seleccione el final del laberinto\n");
                scanf(" %d", &g);
                scanf(" %d", &c);
                matriz[g][c]='$';
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
int i, j, t=0, r=0;
char g;
char color;
printf("Elija de que color quiere que sea el laberinto (r=rojo, a=amarillo, w=azul, b=blanco, v=verde, m=magenta)\n");
do
{
    scanf("%c", &color);
    if (color=='r' || color=='a' || color=='w' || color=='b' || color=='v' || color=='m')
    {
        r=1;
    }
    
} while (r==0);

// Abrimos fichero para escritura
printf("Elija donde quiere guardar el laberinto (1, 2, 3, 4, 5 o 6): ");


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
case '5':
    pf = fopen("Laberinto 5.txt", "w");
    t=1;
    break;
case '6':
    pf = fopen("Laberinto 6.txt", "w");
    t=1;
    break;
default:

printf("Input no válido\n");
    break;
}
} while (t==0);

if (pf == NULL) 
{// Si el resultado es NULL mensaje de error
printf("Error al abrir el fichero.\n");
}
else 
{// Si ha funcionado, comienza escritura
fprintf(pf, "%d", F-1);
fprintf(pf, "\n");
fprintf(pf, "%d", C-2);
fprintf(pf, "\n");
fprintf(pf, "%c", color);
fprintf(pf, "\n");
for ( i = 1; i < F; i++)
{
    for ( j = 1; j < C-1; j++)
    {
        if (matriz[i][j]=='*')
        {
            fprintf(pf, "1");
        }
        else if (matriz[i][j]=='$')
        {
            fprintf(pf, "3");
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
printf("\n");
printf("  -  M E N Ú  de J U E G O  -  \n");
printf("   ------------------------\n\n");
printf("Elige:\n\n");
printf(" A. Laberinto 1  \n");
printf(" B. Laberinto 2  \n");
printf(" C. Laberinto 3  \n");
printf(" D. Laberinto 4  \n");
printf(" E. Laberinto 5  \n");
printf(" F. Laberinto 6  \n");
printf(" G. Crea laberinto \n");
printf(" H. Historial de partidas \n");

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
    
    printf("Bienvenido al laberinto 4\n\n");
    lectura_de_fichero(5);
    t=1;
    break;
case 'f':
case 'F':
    
    printf("Bienvenido al laberinto 4\n\n");
    lectura_de_fichero(6);
    t=1;
    break;
case 'g':
case 'G':
    
    printf("¡¡Crea tu propio laberinto!!\n\n");
    t=1;
    llama_funciones(matriz, matrizaux);
    break;
case 'h':
case 'H':

    printf("\033[2J\033[1;1H");  
    t=1;
    imprime_estadisticas();
    break;


default:

printf("LETRA INCORRECTA!!!! VUELVE A INTENTARLO <\n\n");
break;
}
}while (t==0);

}
void lectura_de_fichero(int n)
{
    char color;
    int x;
FILE *file;

    switch (n)
    {
    case 1:
        file = fopen("Laberinto 1.txt", "r");
        break;
    case 2:
        file = fopen("Laberinto 2.txt", "r");
        break;
    case 3:
        file = fopen("Laberinto 3.txt", "r");
        break;
    case 4:
        file = fopen("Laberinto 4.txt", "r");
        break;
    case 5:
        file = fopen("Laberinto 5.txt", "r");
        break;
    case 6:
        file = fopen("Laberinto 6.txt", "r");
        break;
    
    default:
        break;
    }
    if (file == NULL) {
        printf("\nError; Cannot open file");
        exit(1);
    }

    // leemos diensiónes laberinto
    char r;
    int i, j, k, kant, fil, col;

    for ( i = 0; i < 2; i++ ) 
    {
        j = 1;
        k = 0;
        do {
            r = fgetc(file);
            if (r == '\n') break;

            kant = r - '0';
            /*printf("%d leido\n", kant);*/

            k = kant + (k * j);
            j = 10;
        } while (1);
        
        /*printf("%d leido total\n", k);*/

        if (i == 0) {
            fil = k;
        }
        else {
            col = k;
        }
    }
    //leemos el color del laberinto
    color=fgetc(file);
    // cargamos array
    int lab[100][100];
    i = 0;
    j = 0;

    r = fgetc(file);
    do
    {
        do
        {
            if (r != '\n') // para la primera vez que entra
            {
                lab[i][j] = r - '0';
                j++;
            }
            r = fgetc(file);
        } while (r != '\n' || j < col);

        i++;
        j = 0;
        r = fgetc(file);

       /* printf("\n");*/

    }  while (r != EOF || i < fil);

    /*printf("fin lectura fichero\n");*/
    fclose(file);
    historial(movimiento(lab, fil, col, color), n);
    
}
int movimiento (int matriz[100][100], int fil, int col, char color)
{
    int i, j, k=0, q=1, aux1=0, aux2=1, x=0;
    char l;
    int t;
    int aux3=k, aux4=q, aux5, aux6;
    for (t = 0; x==0; t++)
    {
    printf("\033[2J\033[1;1H");

    for ( i = 0; i < fil; i++)
    {
        for ( j = 0; j < col; j++)
        {
            if (matriz[i][j]==1)
            {
                switch (color)
                {
                case 'a':
                    printf(AMARILLO_F" * "RESET_COLOR);
                    break;
                case 'b':
                    printf(BLANCO_F" * "RESET_COLOR);
                    break;
                case 'r':
                    printf(ROJO_F" * "RESET_COLOR);
                    break;
                case 'w':
                    printf(AZUL_F" * "RESET_COLOR);
                    break;
                case 'm':
                    printf(MAGENTA_F" * "RESET_COLOR);
                    break;
                case 'v':
                    printf(VERDE_F" * "RESET_COLOR);
                    break;
                
                default:
                    break;
                }

            }

            else if (matriz[i][j]==2 || (aux3==i && aux4==j))
            {
                printf(" & ");
            }
            else if (matriz[i][j]==3)
            {
                printf(" $ ");
                aux5=i;
                aux6=j;
            }
            else
            {
                printf("   ");
            }
        }
        
        printf("\n");
    }
    
        //l = getch ();
        printf("w=arriba, s=abajo, a=izquierda, d=derecha\n");
        printf("Número de movimientos: %d\n", t);

        /*scanf("%c", &l);*/
        l=leertecla();

       
        if (l=='s')
        {   k=aux1;
            if (matriz[k+1][aux2]!=1)
        {
            matriz[k+1][aux2]=2;
            matriz[k][aux2]=0;
            aux1=k+1;
        }
        }
        else if (l=='w')
        {
            k=aux1;
            if (matriz[k-1][aux2]!=1)
            {
            matriz[k-1][aux2]=2;
            matriz[k][aux2]=0;
            aux1=k-1;
            }
        }
        else if (l=='d')
        {
            q=aux2;
            if (matriz[aux1][q+1]!=1)
            {
            matriz[aux1][q+1]=2;
            matriz[aux1][q]=' ';
            aux2=q+1;
            }
        }
        else if (l=='a')
        {
            q=aux2;
            if (matriz[aux1][q-1]!=1)
            {
            matriz[aux1][q-1]=2;
            matriz[aux1][q]=0;
            aux2=q-1;
            }
        }
        if (matriz[aux5][aux6]!=3)
        {
            x=1;
        }
    }
    return t;

}
char leertecla() 
{
    char input;
    system("/bin/stty raw");
    input = getchar();
    system("/bin/stty cooked");

    return input;
}
void historial(int movimiento, int laberinto)
{
    int i, lastgame[6], record[6];

    FILE *pf, *pr;

    pf=fopen("Estadistica.csv", "r");
    if (pf == NULL)
    {
    printf("Error al abrir el fichero.");
    exit(1);
    }
    else
    {// Fichero abierto correctamente
    // Lee datos y almacena en vectores
    i = 0;
    while(i<6)
    {
        fscanf(pf, " %i; %i", &lastgame[i], &record[i]);
        i++;
    }

    fclose(pf);
    }
    
    
    pr=fopen("Estadistica.csv", "w");
    if (pr == NULL)
    {
    printf("Error al abrir el fichero.");
    exit(1);
    }
    else
    {// Fichero abierto correctamente
    for ( i = 0; i < 6; i++)
    {
        if (i==laberinto-1)
        {
            if (movimiento<record[i])
            {
                fprintf(pr, "%d; %d\n", movimiento, movimiento);
            }
            else
            {
                fprintf(pr, "%d; %d\n", movimiento, record[i]);
            }
        }
        else
        {
        fprintf(pr, "%d; %d\n", lastgame[i], record[i]);
        }
        
    }
    
    fclose(pr);
    }

}
void imprime_estadisticas()
   {
    int i;
    estadisticas juego[6];
    FILE *f;
    f=fopen("Estadistica.csv", "r");
    if (f==NULL)
    {
        printf("Error al abrir el fichero");
        exit(1);
    }
    else
    {
    for ( i = 0; i < 6; i++)
    {
        fscanf(f, " %d; %d", &juego[i].movimientos, &juego[i].record);
    }
    fclose(f);
    printf("\t\tÚltima partida \t Record\n");
    for ( i = 0; i < 6; i++)
    {
        if (juego[i].movimientos==10000)
        {
        printf("Laberinto %d:\t\t-\t   -\n", i+1);
        }
        else
        {
        printf("Laberinto %d:\t\t%d\t   %d\n", i+1, juego[i].movimientos, juego[i].record);
        }
    }
    }
}
