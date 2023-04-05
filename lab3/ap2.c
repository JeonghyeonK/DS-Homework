#include <stdio.h>
#include <stdlib.h>
void main()
{
    int list[5];                           // 정수형 배열 선언
    int *plist[5];                         // 포인터 배열 선언
    list[0] = 10;                          // 정수형 배열의 0번째 원소에 10 대입
    list[1] = 11;                          // 정수형 배열의 1번째 원소에 11 대입
    plist[0] = (int *)malloc(sizeof(int)); // 포인터 배열의 첫번째

    printf("[----- [Jeonghyeon Kim] [2018038075] -----]\n");

    printf("list[0] \t= %d\n", list[0]);   // 정수형 배열의 0번째 원소값 출력
    printf("list \t\t= %p\n", list);       // 정수형 배열의 주소값 출력
    printf("&list[0] \t= %p\n", &list[0]); // 정수형 배열의 0번째 원소의 주소값(==정수형 배열의 주소값) 출력
    printf("list + 0 \t= %p\n", list + 0); // 정수형 배열의 0번째 원소의 주소값(==정수형 배열의 주소값) 출력
    printf("list + 1 \t= %p\n", list + 1); // 정수형 배열의 1번째 원소의 주소값 출력
    printf("list + 2 \t= %p\n", list + 2); // 정수형 배열의 2번째 원소의 주소값 출력
    printf("list + 3 \t= %p\n", list + 3); // 정수형 배열의 3번째 원소의 주소값 출력
    printf("list + 4 \t= %p\n", list + 4); // 정수형 배열의 4번째 원소의 주소값 출력
    printf("&list[4] \t= %p\n", &list[4]); // 정수형 배열의 4번째 원소의 주소값 출력
    free(plist[0]);                        // 동적할당
}
