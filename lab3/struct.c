#include <stdio.h>
struct student1 //구조체 선언
{
    char lastName;
    int studentId;
    char grade;
};
typedef struct //구조체 선언, struct없이 구조체 이름만으로 사용할 수 있도록 typedef로 선언, 내용은 student1과 동일
{
    char lastName;
    int studentId;
    char grade;
} student2;
int main()
{
    struct student1 st1 = {'A', 100, 'A'}; //이름이 'A', 학번이 100, 성적이 'A'인 student1 구조체 선언 및 초기화

    printf("[----- [Jeonghyeon Kim] [2018038075] -----]\n");

    printf("st1.lastName = %c\n", st1.lastName); //st1 구조체의 멤버인 lastName 출력
    printf("st1.studentId = %d\n", st1.studentId); //st1 구조체의 멤버인 studentId 출력
    printf("st1.grade = %c\n", st1.grade); //st1 구조체의 멤버인 grade 출력
    student2 st2 = {'B', 200, 'B'}; //이름이 'B', 학번이 200, 성적이 'B'인 student2 구조체 선언 및 초기화
    printf("\nst2.lastName = %c\n", st2.lastName); //st2 구조체의 멤버인 lastName 출력
    printf("st2.studentId = %d\n", st2.studentId); //st2 구조체의 멤버인 studentId 출력
    printf("st2.grade = %c\n", st2.grade); //st2 구조체의 멤버인 grade 출력
    student2 st3; // student2 구조체 선언
    st3 = st2; // 기존 student2 구조체를 새 student 구조체에 대입
    printf("\nst3.lastName = %c\n", st3.lastName); //st3 구조체의 멤버인 lastName 출력
    printf("st3.studentId = %d\n", st3.studentId); //st3 구조체의 멤버인 studentId 출력
    printf("st3.grade = %c\n", st3.grade); //st3 구조체의 멤버인 grade 출력

    /* equality test */
    /*같은 구조체 타입도 변수 직접 비교는 불가능합니다. 그래서 멤버별로 각각 비교하는 코드로 수정하였습니다.*/
    if (st3.lastName == st2.lastName&&st3.studentId == st2.studentId&&st3.grade == st2.grade) /* working */
        printf("equal\n");
    else
        printf("not equal\n");
    return 0;
}
