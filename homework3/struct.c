#include <stdio.h>

// 구조체 student1
struct student1
{
    char lastName;
    int studentID;
    char grade;
};

// typedef을 이용하여 만든 구조체 student2 
typedef struct 
{
    char lastName;
    int studentID;
    char grade;
} student2;

int main(){
    // student1은 type이 지정되지 않아 struct를 써서 student1이 
    // 구조체라는것을 알려주고 변수 선언을 해야한다.
    struct student1 st1 = {'A', 100, 'A'};

    // st1의 lastName, studentID, grade 출력
    printf("st1.lastName = %c\n", st1.lastName);
    printf("st1.studentID = %d\n", st1.studentID);
    printf("st1.grade = %c\n", st1.grade);
    
    // typedef로 타입을 지정해줬기 때문에 struct없이
    // 바로 student2 로 변수를 선언 가능
    student2 st2 = {'B', 200, 'B'};

    // st2의 lastName, studentID, grade 출력
    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentID = %d\n", st2.studentID);
    printf("st2.grade = %c\n", st2.grade);

    // st2처럼 바로 변수 선언 가능
    student2 st3;

    // st2의 구조체 치환값이 복사됨
    st3 = st2;

    // st3의 lastName, studentID, grade 출력
    printf("\nst3.lastName = %c\n", st3.lastName);
    printf("st3.studentID = %d\n", st3.studentID);
    printf("st3.grade = %c\n", st3.grade);

    // if(st3 == st2) not working
    // 구조체의 동등성 검사의 경우 한번에 검사를 하지 못하고 각각의 값이 같은지를 비교해야한다.
    // 따라서 다음과 같이 if 문을 수정하여 사용 가능하다.
    if(st3.lastName == st2.lastName && st3.studentID == st2.studentID && st3.grade == st2.grade)
        printf("equal\n");
    else
        printf("not equal\n");

    return 0;
}
