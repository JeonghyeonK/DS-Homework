#include <stdio.h>
struct student1 //구조체 선언
{
    char lastName;
    int studentId;
    char grade;
};
typedef struct //구조체 선언, struct없이 구조체 이름만으로 사용할 수 있도록 typedef로 선언
{
    char lastName;
    int studentId;
    char grade;
} student2;
int main()
{
    struct student1 st1 = {'A', 100, 'A'};

    printf("[----- [Jeonghyeon Kim] [2018038075] -----]\n");

    printf("st1.lastName = %c\n", st1.lastName);
    printf("st1.studentId = %d\n", st1.studentId);
    printf("st1.grade = %c\n", st1.grade);
    student2 st2 = {'B', 200, 'B'};
    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentId = %d\n", st2.studentId);
    printf("st2.grade = %c\n", st2.grade);
    student2 st3;
    st3 = st2;
    printf("\nst3.lastName = %c\n", st3.lastName);
    printf("st3.studentId = %d\n", st3.studentId);
    printf("st3.grade = %c\n", st3.grade);
    /* equality test */
    if (st3.grade == st2.grade) /* not working */
        printf("equal\n");
    else
        printf("not equal\n");
    return 0;
}
