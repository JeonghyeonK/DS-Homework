#include <stdio.h>
#include <stdlib.h>
void main()
{
    int **x; // 정수형 더블포인터 선언

    printf("[----- [Jeonghyeon Kim] [2018038075] -----]\n");

    printf("sizeof(x) = %lu\n", sizeof(x));     // 더블포인터 변수의 크기 출력
    printf("sizeof(*x) = %lu\n", sizeof(*x));   // 더블포인터가 가리키는 포인터 변수의 크기 출력
    printf("sizeof(**x) = %lu\n", sizeof(**x)); // 더블포인터가 가리키는 포인터가 가리키는 변수(int)의 크기 출력
}
