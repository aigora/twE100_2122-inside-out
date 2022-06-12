#include "liblab.h"

void copiamatriz(int fil, int col, char* m1, char* m2) {

    int i, j;
    
    for ( i = 0; i < fil; i++)
    {
        for ( j = 0; j < col; j++)
        {
            *((m2 + i* col) + j) = *((m1 + i* col) + j);
        }
    }
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


char leertecla() 
{
    char input;

    #ifdef _WIN32        // si compilamos en win32 /win64
        input = getch();
    #else
        system("/bin/stty raw");
        input = getchar();
        system("/bin/stty cooked");
    #endif

    return input;
}
