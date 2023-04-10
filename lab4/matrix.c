#include <stdio.h>
#include <stdlib.h>

void print_matrix(int **matrixA, int **matrixB, int matrixA_row, int matrixA_column, int matrixB_row, int matrixB_column)
{

    printf("********print_matrix********\n");
    for (int i = 0; i < matrixA_row; i++)
    {
        for (int j = 0; j < matrixA_column; j++)
        {
            printf("%d ", matrixA[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < matrixB_row; i++)
    {
        for (int j = 0; j < matrixB_column; j++)
        {
            printf("%d ", matrixB[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int addition_matrix(int **matrixA, int **matrixB, int matrixA_row, int matrixA_column, int matrixB_row, int matrixB_column)
{
    if (!(matrixA_row == matrixB_row) || !(matrixA_column == matrixB_column))
    {
        printf("cannot add them :(\n");
        return 0;
    }

    printf("********addition_matrix********\n");
    for (int i = 0; i < matrixA_row; i++)
    {
        for (int j = 0; j < matrixA_column; j++)
        {
            printf("%d ", matrixA[i][j] + matrixB[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int subtraction_matrix(int **matrixA, int **matrixB, int matrixA_row, int matrixA_column, int matrixB_row, int matrixB_column)
{

    if (!(matrixA_row == matrixB_row) || !(matrixA_column == matrixB_column))
    {
        printf("cannot subtract them :(\n");
        return 0;
    }

    printf("********subtraction_matrix********\n");
    for (int i = 0; i < matrixA_row; i++)
    {
        for (int j = 0; j < matrixA_column; j++)
        {
            printf("%d ", matrixA[i][j] - matrixB[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

void transpose_matrix(int **matrixA, int matrixA_row, int matrixA_column)
{

    printf("********transpose_matrix********\n");
    for (int i = 0; i < matrixA_column; i++)
    {
        for (int j = 0; j < matrixA_row; j++)
        {
            printf("%d ", matrixA[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int multiply_matrix(int **matrixA, int **matrixB, int matrixA_row, int matrixA_column, int matrixB_row, int matrixB_column)
{

    if (!(matrixA_column == matrixB_row))
    {
        printf("cannot multiply them :(\n");
        return 0;
    }

    printf("********multiply_matrix********\n");
    for (int i = 0; i < matrixA_row; i++)
    {
        for (int j = 0; j < matrixB_column; j++)
        {
            int n = 0;
            for (int k = 0; k < matrixA_column; k++)
            {
                n += matrixA[i][k] * matrixB[k][j];
            }
            printf("%d ", n);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int free_matrix(int **matrix, int row){
        for (int i = 0; i < row; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int main()
{

    int matrixA_row, matrixA_column;
    printf("input matrix A's row : ");
    scanf("%d", &matrixA_row);
    printf("input matrix A's column : ");
    scanf("%d", &matrixA_column);
    printf("\n");

    int **matrixA = (int **)malloc(sizeof(int *) * matrixA_row);
    for (int i = 0; i < matrixA_column; i++)
    {
        matrixA[i] = (int *)malloc(sizeof(int) * matrixA_column);
    }

    for (int i = 0; i < matrixA_row; i++)
    {
        printf("input matrix A's %d row : ", i);
        for (int j = 0; j < matrixA_column; j++)
        {
            scanf("%d", &matrixA[i][j]);
        }
    }
    printf("\n");

    int matrixB_row, matrixB_column;
    printf("input matrix B's row : ");
    scanf("%d", &matrixB_row);
    printf("input matrix B's column : ");
    scanf("%d", &matrixB_column);
    printf("\n");

    int **matrixB = (int **)malloc(sizeof(int *) * matrixB_row);
    for (int i = 0; i < matrixB_column; i++)
    {
        matrixB[i] = (int *)malloc(sizeof(int) * matrixB_column);
    }

    for (int i = 0; i < matrixB_row; i++)
    {
        printf("input matrix B's %d row : ", i);
        for (int j = 0; j < matrixB_column; j++)
        {
            scanf("%d", &matrixB[i][j]);
        }
    }
    printf("\n");

    print_matrix(matrixA, matrixB, matrixA_row, matrixA_column, matrixB_row, matrixB_column);
    addition_matrix(matrixA, matrixB, matrixA_row, matrixA_column, matrixB_row, matrixB_column);
    subtraction_matrix(matrixA, matrixB, matrixA_row, matrixA_column, matrixB_row, matrixB_column);
    transpose_matrix(matrixA, matrixA_row, matrixA_column);
    multiply_matrix(matrixA, matrixB, matrixA_row, matrixA_column, matrixB_row, matrixB_column);

    free_matrix(matrixA, matrixA_row);
    free_matrix(matrixB, matrixB_row);

    return 0;
}