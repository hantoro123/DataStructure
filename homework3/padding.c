#include <stdio.h>

struct student {
    // 각 선언된 변수들은 사이즈는
    char lastName[13]; // 13bytes
    int stduentID; // 4bytes
    short grade; // 2bytes
};

int main(){
    // 구조체의 타입이 지정되어 있지 않아 struct를 사용하여 선언
    struct student pst;

    // struct student 의 경우 원래는 19bytes의 사이즈가 출려되어야 하는데
    // padding에 의해서 lastName[13]이 13+3(빈공간) = 16bytes
    // int는 4byte그대로 short의 경우 2+2(빈공간) = 4bytes로 총 24bytes가 출력됨
    printf("size of student = %ld\n", sizeof(struct student));
    printf("size of int     = %ld\n", sizeof(int));
    printf("size of short   = %ld\n", sizeof(short));

    printf("[----- [한상준] [2017018024] -----]");

    return 0;
}