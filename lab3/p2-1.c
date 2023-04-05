#include <stdio.h>
#define MAX_SIZE 100            // 매크로함수
float sum1(float list[], int);  // 실수형 배열과 정수형 변수를 입력받아 합계를 계산하는 함수
float sum2(float *list, int);   // 실수형 포인터 배열과 정수형 변수를 입력받아 합계를 계산하는 함수
float sum3(int n, float *list); // 정수형 변수와 실수형 포인터변수를 입력받아 합계를 계산하는 함수
float input[MAX_SIZE], answer;  // 요소가 100개인 실수형 배열과 실수형 변수 선언
int i;                          // 반복문에 사용할 정수형 변수 선언
void main(void)
{

    printf("[----- [Jeonghyeon Kim] [2018038075] -----]\n");

    for (i = 0; i < MAX_SIZE; i++) // 배열에 0부터 99까지의 자연수를 저장
        input[i] = i;
    /* for checking call by reference */
    printf("--------------------------------------\n");
    printf(" sum1(input, MAX_SIZE) \n"); // 실수형 배열과 정수형 변수를 입력받아 합계를 계산
    printf("--------------------------------------\n");
    printf("input \t= %p\n", input);      // 배열의 주소를 출력
    answer = sum1(input, MAX_SIZE);       // answer sum1 함수의 반환값 대입
    printf("The sum is: %f\n\n", answer); // 합계 출력
    printf("--------------------------------------\n");
    printf(" sum2(input, MAX_SIZE) \n"); // 실수형 포인터 배열과 정수형 변수를 입력받아 합계를 계산
    printf("--------------------------------------\n");
    printf("input \t= %p\n", input);      // 배열의 주소를 출력
    answer = sum2(input, MAX_SIZE);       // answer sum2 함수의 반환값 대입
    printf("The sum is: %f\n\n", answer); // 합계 출력
    printf("--------------------------------------\n");
    printf(" sum3(MAX_SIZE, input) \n"); // 정수형 변수와 실수형 포인터변수를 입력받아 합계를 계산
    printf("--------------------------------------\n");
    printf("input \t= %p\n", input);      // 배열의 주소를 출력
    answer = sum3(MAX_SIZE, input);       // answer sum3 함수의 반환값 대입
    printf("The sum is: %f\n\n", answer); // 합계 출력
}

float sum1(float list[], int n) // 실수형 배열과 정수형 변수를 입력받아 합계를 계산하는 함수
{
    printf("list \t= %p\n", list);     // 실수형 배열의 주소값 출력
    printf("&list \t= %p\n\n", &list); // 실수형 배열의 주소값 출력
    int i;                             // 반복문에 이용할 정수형 변수 선언
    float tempsum = 0;                 // 합계를 저장할 실수형 변수 선언
    for (i = 0; i < n; i++)            // 실수형 배열의 모든 원소의 값을 tempsum에 더함
        tempsum += list[i];            // 원소의 값을 직접 더함
    return tempsum;                    // 모든 원소의 합 반환
}

float sum2(float *list, int n) // 실수형 포인터 배열과 정수형 변수를 입력받아 합계를 계산하는 함수
{
    printf("list \t= %p\n", list);     // 실수형 포인터 배열의 주소값 출력
    printf("&list \t= %p\n\n", &list); // 실수형 포인터 배열의 주소값 출력
    int i;                             // 반복문에 이용할 정수형 변수 선언
    float tempsum = 0;                 // 합계를 저장할 실수형 변수 선언
    for (i = 0; i < n; i++)            // 실수형 포인터 배열의 모든 원소의 값을 tempsum에 더함
        tempsum += *(list + i);        // 원소별 주소에 저장된 값을 더함
    return tempsum;                    // 모든 원소의 합 반환
}

/* stack variable reuse test */
float sum3(int n, float *list) // 정수형 변수와 실수형 포인터변수를 입력받아 합계를 계산하는 함수
{
    printf("list \t= %p\n", list);     // 실수형 포인터 배열의 주소값 출력
    printf("&list \t= %p\n\n", &list); // 실수형 포인터 배열의 주소값 출력
    int i;                             // 반복문에 이용할 정수형 변수 선언
    float tempsum = 0;                 // 합계를 저장할 실수형 변수 선언
    for (i = 0; i < n; i++)            // 실수형 포인터 배열의 모든 원소의 값을 tempsum에 더함
        tempsum += *(list + i);        // 원소별 주소에 저장된 값을 더함
    return tempsum;                    // 모든 원소의 합 반환
}
