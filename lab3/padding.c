#include <stdio.h>
struct student // 구조체 선언
{
    char lastName[13]; /* 13 bytes */
    int studentId;     /* 4 bytes */
    short grade;       /* 2 bytes */
};
int main()
{
    struct student pst; // 구조체 생성

    printf("[----- [Jeonghyeon Kim] [2018038075] -----]\n");

    printf("size of student = %ld\n", sizeof(struct student)); // 구조체의 크기 출력
    printf("size of int = %ld\n", sizeof(int));                // int 자료형의 크기 출력
    printf("size of short = %ld\n", sizeof(short));            // short 자료형의 크기 출력
    return 0;                                                  // 반환 및 함수 종료
}