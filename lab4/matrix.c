#include <stdio.h>
#include <stdlib.h>

void get_row_column(int *row, int *column, char *matrix_name)
{
    printf("input %s's row : ", matrix_name);
    scanf("%d", row);
    printf("input %s's column : ", matrix_name);
    scanf("%d", column);
    printf("\n");
}

void get_matrix(int **matrix, int row, int column, char *matrix_name)
{
    for (int i = 0; i < row; i++)
    {
        printf("input %s's %d row : ", matrix_name, i);
        for (int j = 0; j < column; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\n");
}

void print_matrix(int **matrix, int matrix_row, int matrix_column, char *result)
{

    printf("******** %s ******** \n", result);
    for (int i = 0; i < matrix_row; i++)
    {
        for (int j = 0; j < matrix_column; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int addition_matrix(int **matrixA, int **matrixB, int matrixA_row, int matrixA_column, int matrixB_row, int matrixB_column, int **add_result)
{
    if (!(matrixA_row == matrixB_row) || !(matrixA_column == matrixB_column))
    {
        printf("cannot add them :(\n");
        return 0;
    }

    for (int i = 0; i < matrixA_row; i++)
    {
        for (int j = 0; j < matrixA_column; j++)
        {
            add_result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    return 0;
}

int subtraction_matrix(int **matrixA, int **matrixB, int matrixA_row, int matrixA_column, int matrixB_row, int matrixB_column, int **subtract_result)
{

    if (!(matrixA_row == matrixB_row) || !(matrixA_column == matrixB_column))
    {
        printf("cannot subtract them :(\n");
        return 0;
    }

    for (int i = 0; i < matrixA_row; i++)
    {
        for (int j = 0; j < matrixA_column; j++)
        {
            subtract_result[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
    return 0;
}

void transpose_matrix(int **matrix, int row, int column, int **transpose_result)
{

    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < row; j++)
            transpose_result[i][j] = matrix[j][i];
    }
}

int multiply_matrix(int **matrixA, int **matrixB, int matrixA_row, int matrixA_column, int matrixB_row, int matrixB_column, int **multiply_matrix)
{

    if (!(matrixA_column == matrixB_row))
    {
        printf("cannot multiply them :(\n");
        return 0;
    }

    for (int i = 0; i < matrixA_row; i++)
    {
        for (int j = 0; j < matrixB_column; j++)
        {
            int n = 0;
            for (int k = 0; k < matrixA_column; k++)
                n += matrixA[i][k] * matrixB[k][j];

            multiply_matrix[i][j] = n;
        }
    }
    return 0;
}

int free_matrix(int **matrix, int row)
{
    for (int i = 0; i < row; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int main()
{
    
    printf("[----- [Jeonghyeon Kim] [2018038075] -----]\n\n");

    int matrixA_row, matrixA_column, matrixB_row, matrixB_column;
    
    get_row_column(&matrixA_row, &matrixA_column, "matrix A");
    get_row_column(&matrixB_row, &matrixB_column, "matrix B");

    int **matrixA = (int **)malloc(sizeof(int *) * matrixA_row);
    for (int i = 0; i < matrixA_column; i++)
        matrixA[i] = (int *)malloc(sizeof(int) * matrixA_column);

    get_matrix(matrixA, matrixA_row, matrixA_column, "matrix A");

    int **matrixB = (int **)malloc(sizeof(int *) * matrixB_row);
    for (int i = 0; i < matrixB_column; i++)
        matrixB[i] = (int *)malloc(sizeof(int) * matrixB_column);

    get_matrix(matrixB, matrixB_row, matrixB_column, "matrix B");

    int **add_result = (int **)malloc(sizeof(int *) * matrixA_row);
    for (int i = 0; i < matrixA_column; i++)
        add_result[i] = (int *)malloc(sizeof(int) * matrixA_column);

    int **subtract_result = (int **)malloc(sizeof(int *) * matrixA_row);
    for (int i = 0; i < matrixA_column; i++)
        subtract_result[i] = (int *)malloc(sizeof(int) * matrixA_column);

    int **transpose_result = (int **)malloc(sizeof(int *) * matrixA_column);
    for (int i = 0; i < matrixA_column; i++)
        transpose_result[i] = (int *)malloc(sizeof(int) * matrixA_row);

    int **multiply_result = (int **)malloc(sizeof(int *) * matrixA_row);
    for (int i = 0; i < matrixA_column; i++)
        multiply_result[i] = (int *)malloc(sizeof(int) * matrixB_column);

    print_matrix(matrixA, matrixA_row, matrixA_column, "matrix A");
    print_matrix(matrixB, matrixB_row, matrixB_column, "matrix B");

    addition_matrix(matrixA, matrixB, matrixA_row, matrixA_column, matrixB_row, matrixB_column, add_result);
    subtraction_matrix(matrixA, matrixB, matrixA_row, matrixA_column, matrixB_row, matrixB_column, subtract_result);
    transpose_matrix(matrixA, matrixA_row, matrixA_column, transpose_result);
    multiply_matrix(matrixA, matrixB, matrixA_row, matrixA_column, matrixB_row, matrixB_column, multiply_result);

    print_matrix(add_result, matrixA_row, matrixA_column, "addition result");
    print_matrix(subtract_result, matrixA_row, matrixA_column, "subtraction result");
    print_matrix(transpose_result, matrixA_column, matrixA_row, "transpose result");
    print_matrix(multiply_result, matrixA_row, matrixB_column, "multiply result");

    free_matrix(matrixA, matrixA_row);
    free_matrix(matrixB, matrixB_row);
    free_matrix(add_result, matrixA_row);
    free_matrix(subtract_result, matrixA_row);
    free_matrix(transpose_result, matrixA_column);
    free_matrix(multiply_result, matrixA_row);

    return 0;
}