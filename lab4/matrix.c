#include <stdio.h>
#include <stdlib.h> 

int main() {
    int row, column;
    printf("input row : ");
    scanf("%d", &row);
    printf("input column : ");
    scanf("%d", &column);

    //row만큼 배열의 세로 동적할당
    int** arr = (int**)malloc(sizeof(int*) * row);
    
    //row만큼 배열의 가로 동적할당 
    for (int i = 0; i < column; i++) { 
        arr[i] = (int*)malloc(sizeof(int) * column); 
    }

    for (int i = 0; i < row; i++) {
        printf("input %d row : ", i);
        for (int j = 0; j < column; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    //배열의 값 출력
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("arr[%d][%d] : %d   ", i, j, arr[i][j]);
        }
        printf("\n");
    }

    //메모리 해제
    for (int i = 0; i < row; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}