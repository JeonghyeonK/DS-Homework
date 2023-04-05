#include <stdio.h>
void print_one(int *ptr, int rows); // 정수형 배열과 정수형 변수를 받아 배열의 원소별로 주소와 값을 출력하는 함수
int main()
{
    int one[] = {0, 1, 2, 3, 4}; // 원소가 0부터 4까지 5개인 정수형 배열 선언 및 초기화

    printf("[----- [Jeonghyeon Kim] [2018038075] -----]\n");

    printf("one = %p\n", one);         // 정수형 배열의 주소 출력
    printf("&one = %p\n", &one);       // 정수형 배열의 주소 출력
    printf("&one[0] = %p\n", &one[0]); // 정수형 배열의 첫번째 원소의 주소(=정수형 배열의 주소) 출력
    printf("\n");
    printf("------------------------------------\n");
    printf(" print_one(&one[0], 5) \n");
    printf("------------------------------------\n");
    print_one(&one[0], 5); // 정수형 배열의 첫번째 원소의 주소(=정수형 배열의 주소)와 상수 5를 받아 배열의 5개 원소의 주소와 값을 출력
    printf("------------------------------------\n");
    printf(" print_one(one, 5) \n");
    printf("------------------------------------\n");
    print_one(one, 5); // 정수형 배열의 주소와 상수 5를 받아 배열의 5개 원소의 주소와 값을 출력
    return 0;          // 반환 및 프로그램 종료
}
void print_one(int *ptr, int rows)                  // 정수형 배열과 정수형 변수를 받아 배열의 원소별로 주소와 값을 출력하는 함수
{                                                   /* print out a one-dimensional array using a pointer */
    int i;                                          // 반복문용 변수 선언
    printf("Address \t Contents\n");                // 값 정렬 위해 출력
    for (i = 0; i < rows; i++)                      // rows 수만큼 반복
        printf("%p \t %5d\n", ptr + i, *(ptr + i)); // 정수형 배열의 원소별로 주소와 값 출력
    printf("\n");
}
