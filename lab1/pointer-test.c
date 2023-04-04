#include <stdio.h>
int main()
{
    int i, *p; // 변수 i와 포인터 p를 int형으로 선언
    i = 10; // i에 10 대입
    printf("value of i = %d\n", i); // i의 값 출력
    printf("address of i = %p\n", &i); // i의 주소 출력
    
    // p의 값 출력 : 선언만 하였기 때문에 정상적인 값이 들어있지 않다.
    printf("value of p = %p\n", p); 
    
    // p의 주소 출력 : i의 주소보다 4바이트 앞에 위치한 것을 알 수 있다.
    printf("address of p = %p\n", &p); 

    p = &i; // p에 i의 주소값 대입
    printf("\n\n----- after p = &i ------------\n\n"); // 전후 구분 위해 출력
    
    // p의 값 출력 : i의 주소인 값이 출력된다.
    printf("value of p = %p\n", p); 

    // p의 주소 출력 : 값만 변하고 주소는 그대로다.
    printf("address of p = %p\n", &p); 

    //p의 값을 주소로 하는 값, 즉 i의 값이 출력된다.
    printf("dereferencing *p = %d\n", *p); 

    return 0; // 반환 후 함수 종료
}
