#include <stdio.h>
#include <stdlib.h>
void main()
{
    int list[5]; // 정수형 배열 선언
    int *plist[5] = {
        // 포인터 배열 선언 및 NULL로 초기화
        NULL,
    };
    plist[0] = (int *)malloc(sizeof(int)); // 포인터 배열의 첫번째 원소를 int 사이즈만큼 동적할당
    list[0] = 1;                           // 배열의 0번째 원소에 1 대입
    list[1] = 100;                         // 배열의 1번째 원소에 100 대입
    *plist[0] = 200;

    printf("[----- [Jeonghyeon Kim] [2018038075] -----]\n");

    printf("list[0] = %d\n", list[0]);   // 배열의 0번째 원소의 값 출력
    printf("&list[0] = %p\n", &list[0]); // 배열의 0번째 원소의 주소 출력
    printf("list = %p\n", list);         // 배열의 주소 출력
    printf("&list = %p\n", &list);       // 배열의 주소 출력
    printf("----------------------------------------\n\n");
    printf("list[1] = %d\n", list[1]);       // 배열의 1번째 원소의 값 출력
    printf("&list[1] = %p\n", &list[1]);     // 배열의 1번째 원소의 주소 출력
    printf("*(list+1) = %d\n", *(list + 1)); // 배열의 시작 주소 기준으로 한 칸 떨어져 있는(1번째 원소) 값 출력
    printf("list+1 = %p\n", list + 1);       // 배열의 1번째 원소의 주소 출력
    printf("----------------------------------------\n\n");
    printf("*plist[0] = %d\n", *plist[0]); // 포인터배열의 0번째 원소에 담긴 값이 주소인 원소의 값 출력
    printf("&plist[0] = %p\n", &plist[0]); // 포인터배열의 0번째 원소의 주소 출력
    printf("&plist = %p\n", &plist);       // 포인터배열의 주소 출력
    printf("plist = %p\n", plist);         // 포인터배열의 주소 출력
    printf("plist[0] = %p\n", plist[0]);   // 포인터배열의 0번째 원소의 주소 출력
    printf("plist[1] = %p\n", plist[1]);   // 포인터배열의 1번째 주소 출력, 원소에 NULL값이 들어있으므로 쓰레기값 출력
    printf("plist[2] = %p\n", plist[2]);   // 포인터배열의 2번째 주소 출력, 원소에 NULL값이 들어있으므로 쓰레기값 출력
    printf("plist[3] = %p\n", plist[3]);   // 포인터배열의 3번째 주소 출력, 원소에 NULL값이 들어있으므로 쓰레기값 출력
    printf("plist[4] = %p\n", plist[4]);   // 포인터배열의 4번째 주소 출력, 원소에 NULL값이 들어있으므로 쓰레기값 출력
    free(plist[0]);                        // 동적할당 해제
}
