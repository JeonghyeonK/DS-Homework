#include <stdio.h>
int main()
{
    int i;
    int *ptr;
    int **dptr;
    i = 1234;
    // 정수형 변수, 정수형 포인터, 정수형 더블포인터를 선언하고 정수형 변수 i에 1234라는 정수를 대입하였다.

    printf("[----- [Jeonghyeon Kim] [2018038075] -----]");
    printf("[checking values before ptr = &i] \n"); // ptr에 i의 주소값을 대입하기 전 값 체크
    printf("value of i == %d\n", i);                // i의 값은 위에서 대입한 대로 1234가 출력된다.
    printf("address of i == %p\n", &i);             // i의 주소는 061FF1C
    printf("value of ptr == %p\n", ptr);            // ptr의 값은 초기화가 되어있지 않아 00000000으로 출력된다.
    printf("address of ptr == %p\n", &ptr);         // ptr의 주소는 0061FF18

    ptr = &i;                                        /* ptr is now holding the address of i */
    printf("\n[checking values after ptr = &i] \n"); // ptr에 i의 주소값을 대입하였다.
    printf("value of i == %d\n", i);                 // i의 값은 변하지 않았다.
    printf("address of i == %p\n", &i);              // i의 주소는 변하지 않았다.
    printf("value of ptr == %p\n", ptr);             // ptr의 값은 i의 주소값과 같아졌다.
    printf("address of ptr == %p\n", &ptr);          // ptr의 주소는 변하지 않았다.
    printf("value of *ptr == %d\n", *ptr);           // ptr의 값이 주소인, 즉 i의 값이 출력된다.

    dptr = &ptr;                                        /* dptr is now holding the address of ptr */
    printf("\n[checking values after dptr = &ptr] \n"); // dptr에 ptr의 주소값을 대입하였다.
    printf("value of i == %d\n", i);                    // i의 값은 변하지 않았다.
    printf("address of i == %p\n", &i);                 // i의 주소는 변하지 않았다.
    printf("value of ptr == %p\n", ptr);                // ptr의 값은 i의 주소값과 같다.
    printf("address of ptr == %p\n", &ptr);             // ptr의 주소는 변하지 않았다.
    printf("value of *ptr == %d\n", *ptr);              // ptr의 값이 주소인, 즉 i의 값이 출력된다.
    printf("value of dptr == %p\n", dptr);              // dptr의 값은 ptr의 주소값과 같아졌다.
    printf("address of dptr == %p\n", &dptr);           // dptr의 주소는 0061FF14
    printf("value of *dptr == %p\n", *dptr);            // dptr의 값이 주소인, 즉 ptr의 값(=i의 주소)이 출력된다.
    printf("value of **dptr == %d\n", **dptr);          // dptr의 값, 즉 ptr의 값을 주소로 갖는 값, 즉 i의 값이 출력된다.

    *ptr = 7777;                               /* changing the value of *ptr */
    printf("\n[after *ptr = 7777] \n");        // ptr의 값을 주소로 갖는 값에 7777을 대입했다. i에 7777을 대입한 셈이다.
    printf("value of i == %d\n", i);           // i의 값은 7777이 출력된다.
    printf("value of *ptr == %d\n", *ptr);     // *ptr은 i의 값과 같으므로 7777이 출력된다.
    printf("value of **dptr == %d\n", **dptr); // **dptr은 *ptr과 같고 i의 값과도 같으므로 7777이 출력된다.

    **dptr = 8888;                             /* changing the value of **dptr */
    printf("\n[after **dptr = 8888] \n");      // **dptr, 즉 ptr의 값을 주소로 갖는 값에 8888을 대입했다. i에 8888을 대입한 셈이다.
    printf("value of i == %d\n", i);           // i의 값은 8888이 출력된다.
    printf("value of *ptr == %d\n", *ptr);     // *ptr은 i의 값과 같으므로 8888이 출력된다.
    printf("value of **dptr == %d\n", **dptr); // **dptr은 *ptr과 같고 i의 값과도 같으므로 8888이 출력된다.
    return 0;
}