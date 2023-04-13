#include <stdio.h>
#include <stdlib.h>

void get_row_column(int *row, int *column, char *matrix_name); // 행렬의 행과 열 개수 입력받는 함수

void get_matrix(int **matrix, int row, int column, char *matrix_name); // 행렬을 입력받는 함수

void print_matrix(int **matrix, int matrix_row, int matrix_column, char *result); // 행렬을 출력하는 함수

// 두 행렬의 합을 구하는 함수
int addition_matrix(int **matrixA, int **matrixB, int matrixA_row, int matrixA_column, int matrixB_row, int matrixB_column, int **add_result);

// 두 행렬의 차를 구하는 함수
int subtraction_matrix(int **matrixA, int **matrixB, int matrixA_row, int matrixA_column, int matrixB_row, int matrixB_column, int **subtract_result);

// 행렬의 전치행렬을 구하는 함수
void transpose_matrix(int **matrix, int row, int column, int **transpose_result);

// 두 행렬의 곱을 구하는 함수
int multiply_matrix(int **matrixA, int **matrixB, int matrixA_row, int matrixA_column, int matrixB_row, int matrixB_column, int **multiply_matrix);

int free_matrix(int **matrix, int row); // 동적할당된 변수의 메모리를 해제하는 함수

int main()
{

    printf("[----- [Jeonghyeon Kim] [2018038075] -----]\n\n");

    int matrixA_row, matrixA_column, matrixB_row, matrixB_column; // 두 행렬의 행과 열 개수를 입력받을 변수 선언

    get_row_column(&matrixA_row, &matrixA_column, "matrix A"); // 행과 열 개수 입력받기
    get_row_column(&matrixB_row, &matrixB_column, "matrix B");

    int **matrixA = (int **)malloc(sizeof(int *) * matrixA_row); // 행렬 A를 2차원 배열로 동적할당
    for (int i = 0; i < matrixA_column; i++)
        matrixA[i] = (int *)malloc(sizeof(int) * matrixA_column);

    get_matrix(matrixA, matrixA_row, matrixA_column, "matrix A"); // 행렬 A 입력받기

    int **matrixB = (int **)malloc(sizeof(int *) * matrixB_row); // 행렬 B를 2차원 배열로 동적할당
    for (int i = 0; i < matrixB_column; i++)
        matrixB[i] = (int *)malloc(sizeof(int) * matrixB_column);

    get_matrix(matrixB, matrixB_row, matrixB_column, "matrix B"); // 행렬 B 입력받기

    int **add_result = (int **)malloc(sizeof(int *) * matrixA_row); // 합의 결과를 입력받을 행렬 2차원 배열로 동적할당
    for (int i = 0; i < matrixA_column; i++)
        add_result[i] = (int *)malloc(sizeof(int) * matrixA_column);

    int **subtract_result = (int **)malloc(sizeof(int *) * matrixA_row); // 차의 결과를 입력받을 행렬 2차원 배열로 동적할당
    for (int i = 0; i < matrixA_column; i++)
        subtract_result[i] = (int *)malloc(sizeof(int) * matrixA_column);

    int **transpose_result = (int **)malloc(sizeof(int *) * matrixA_column); // 전치행렬의 결과를 입력받을 행렬 2차원 배열로 동적할당
    for (int i = 0; i < matrixA_column; i++)
        transpose_result[i] = (int *)malloc(sizeof(int) * matrixA_row);

    int **multiply_result = (int **)malloc(sizeof(int *) * matrixA_row); // 곱의 결과를 입력받을 행렬 2차원 배열로 동적할당
    for (int i = 0; i < matrixA_column; i++)
        multiply_result[i] = (int *)malloc(sizeof(int) * matrixB_column);

    // 두 행렬을 출력
    print_matrix(matrixA, matrixA_row, matrixA_column, "matrix A");
    print_matrix(matrixB, matrixB_row, matrixB_column, "matrix B");

    // 연산 함수 4가지 실행, 결과는 위에서 선언하고 동적할당한 result들에 저장됨
    int addition_check = addition_matrix(matrixA, matrixB, matrixA_row, matrixA_column, matrixB_row, matrixB_column, add_result);
    int subtraction_check = subtraction_matrix(matrixA, matrixB, matrixA_row, matrixA_column, matrixB_row, matrixB_column, subtract_result);
    transpose_matrix(matrixA, matrixA_row, matrixA_column, transpose_result);
    int multiply_check = multiply_matrix(matrixA, matrixB, matrixA_row, matrixA_column, matrixB_row, matrixB_column, multiply_result);

    // 연산 결과 출력
    if(addition_check==1) print_matrix(add_result, matrixA_row, matrixA_column, "addition result");
    if(subtraction_check==1) print_matrix(subtract_result, matrixA_row, matrixA_column, "subtraction result");
    print_matrix(transpose_result, matrixA_column, matrixA_row, "transpose result");
    if(multiply_check==1) print_matrix(multiply_result, matrixA_row, matrixB_column, "multiply result");

    // 동적할당했던 최초 행렬 2개와 결과 저장용 행렬 4개 모두 해제
    free_matrix(matrixA, matrixA_row);
    free_matrix(matrixB, matrixB_row);
    free_matrix(add_result, matrixA_row);
    free_matrix(subtract_result, matrixA_row);
    free_matrix(transpose_result, matrixA_column);
    free_matrix(multiply_result, matrixA_row);

    return 0; // 반환 후 함수 종료
}

void get_row_column(int *row, int *column, char *matrix_name) // 행렬의 행과 열 개수 입력받는 함수
{
    printf("input %s's row : ", matrix_name);    // 행의 개수 입력받으라는 안내문 출력
    scanf("%d", row);                            // 행의 개수 입력
    printf("input %s's column : ", matrix_name); // 열의 개수 입력받으라는 안내문 출력
    scanf("%d", column);                         // 열의 개수 입력
    printf("\n");
}


void get_matrix(int **matrix, int row, int column, char *matrix_name) // 행렬을 입력받는 함수
{
    for (int i = 0; i < row; i++) // 각 행마다 반복
    {
        printf("input %s's %d row : ", matrix_name, i); // 몇 번째 행의 내용을 입력해야 하는지 안내문 출력
        for (int j = 0; j < column; j++)                // 열의 개수만큼 정수를 입력받아 순차적으로 저장
            scanf("%d", &matrix[i][j]);
    }
    printf("\n");
}

void print_matrix(int **matrix, int matrix_row, int matrix_column, char *result) // 행렬을 출력하는 함수
{

    printf("******** %s ******** \n", result); // 어떤 행렬을 출력하는지 안내문 출력
    for (int i = 0; i < matrix_row; i++)       // 각 행마다 반복
    {
        for (int j = 0; j < matrix_column; j++) // 행마다 각 열을 순차적으로 모두 출력 후 줄바꿈
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

// 두 행렬의 합을 구하는 함수
int addition_matrix(int **matrixA, int **matrixB, int matrixA_row, int matrixA_column, int matrixB_row, int matrixB_column, int **add_result)
{

    // 두 행렬의 행 개수, 열 개수가 일치하지 않으면 안내문 출력 및 반환 후 함수 종료
    if (!(matrixA_row == matrixB_row) || !(matrixA_column == matrixB_column))
    {
        printf("cannot add them :(\n\n");
        return 0;
    }

    for (int i = 0; i < matrixA_row; i++) // 각 행마다 반복
    {
        for (int j = 0; j < matrixA_column; j++) // 각 열마다 두 행렬의 원소의 합을 구해 결과행렬에 저장
            add_result[i][j] = matrixA[i][j] + matrixB[i][j];
    }
    return 1; // 반환 후 함수 종료
}

// 두 행렬의 차를 구하는 함수
int subtraction_matrix(int **matrixA, int **matrixB, int matrixA_row, int matrixA_column, int matrixB_row, int matrixB_column, int **subtract_result)
{

    // 두 행렬의 행 개수, 열 개수가 일치하지 않으면 안내문 출력 및 반환 후 함수 종료
    if (!(matrixA_row == matrixB_row) || !(matrixA_column == matrixB_column))
    {
        printf("cannot subtract them :(\n\n");
        return 0;
    }

    for (int i = 0; i < matrixA_row; i++) // 각 행마다 반복
    {
        for (int j = 0; j < matrixA_column; j++) // 각 열마다 두 행렬의 원소의 차를 구해 결과행렬에 저장
            subtract_result[i][j] = matrixA[i][j] - matrixB[i][j];
    }
    return 1; // 반환 후 함수 종료
}

// 행렬의 전치행렬을 구하는 함수
void transpose_matrix(int **matrix, int row, int column, int **transpose_result)
{

    for (int i = 0; i < column; i++) // 각 열마다 반복
    {
        for (int j = 0; j < row; j++) // 원래 행렬의 i열을 전치행렬 결과행렬의 i행으로 저장
            transpose_result[i][j] = matrix[j][i];
    }
}

// 두 행렬의 곱을 구하는 함수
int multiply_matrix(int **matrixA, int **matrixB, int matrixA_row, int matrixA_column, int matrixB_row, int matrixB_column, int **multiply_matrix)
{

    // 첫 번째 행렬의 열 개수와 두 번째 행렬의 행 개수가 일치하지 않으면 안내문 출력 및 반환 후 함수 종료
    if (!(matrixA_column == matrixB_row))
    {
        printf("cannot multiply them :(\n\n");
        return 0;
    }

    for (int i = 0; i < matrixA_row; i++) // 각 열마다 반복
    {
        for (int j = 0; j < matrixB_column; j++) // 각 행마다 반복
        {
            int n = 0;                               // 결과행렬의 원소로 저장될 변수 선언 및 초기화
            for (int k = 0; k < matrixA_column; k++) // 행렬의 곱을 구하는 공식에 맞게 n을 계산
                n += matrixA[i][k] * matrixB[k][j];

            multiply_matrix[i][j] = n; // 결과행렬의 원소로 저장
        }
    }
    return 1; // 반환 후 함수 종료
}

int free_matrix(int **matrix, int row) // 동적할당된 변수의 메모리를 해제하는 함수
{
    for (int i = 0; i < row; i++) // 행렬의 행마다 동적할당된 일차원배열의 메모리를 모두 해제
        free(matrix[i]);

    free(matrix); // 전체 행렬의 메모리를 마지막으로 해제
}
