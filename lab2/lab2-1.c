#include <stdio.h>
int main()
{
    char charType;
    int integerType;
    float floatType;
    double doubleType;
    // 변수들을 4가지 자료형으로 선언한다.

    printf("[----- [Jeonghyeon Kim] [2018038075] -----]");

    printf("Size of char: %ld byte\n", sizeof(charType));
    printf("Size of int: %ld bytes\n", sizeof(integerType));
    printf("Size of float: %ld bytes\n", sizeof(floatType));
    printf("Size of double: %ld bytes\n", sizeof(doubleType));
    // 위의 코드는 각 자료형으로 선언된 변수의 크기를 출력한다.
    // 변수들은 각각의 자료형만큼의 크기를 할당받으므로 자료형의 크기를 출력한다.

    printf("-----------------------------------------\n");
    printf("Size of char: %ld byte\n", sizeof(char));
    printf("Size of int: %ld bytes\n", sizeof(int));
    printf("Size of float: %ld bytes\n", sizeof(float));
    printf("Size of double: %ld bytes\n", sizeof(double));
    // 위의 코드는 각 자료형의 크기를 그대로 출력한다.

    printf("-----------------------------------------\n");
    printf("Size of char*: %ld byte\n", sizeof(char *));
    printf("Size of int*: %ld bytes\n", sizeof(int *));
    printf("Size of float*: %ld bytes\n", sizeof(float *));
    printf("Size of double*: %ld bytes\n", sizeof(double *));
    // 위의 코드는 각 자료형으로 선언된 포인터의 크기를 출력한다.
    // 특정 주소를 가리키기 위한 값을 저장하는 포인터변수는 자료형에 상관없이 모두 int형으로 취급되어 4바이트를 가진다.

    return 0;
}
