#include <stdio.h>
#include <stdlib.h>

int main()
{

    int **matrixA = (int **)malloc(sizeof(int *) * 4);
    for (int i = 0; i < 4; i++)
    {
        matrixA[i] = (int *)malloc(sizeof(int) * 3);
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrixA[i][j] = i + j;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d", matrixA[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 4; i++)
    {
        free(matrixA[i]);
    }
    free(matrixA);

    return 0;
}