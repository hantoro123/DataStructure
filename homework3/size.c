#include <stdio.h>
#include <stdlib.h>

void main(){
    int **x;

    // x는 포인터가 가지고 잇는 사이즈를 출력한다.
    printf("sizeof(x) = %lu\n" , sizeof(x));
    // *x와 **x는 각각 포인터에 저장되는 사이즈, 이중포인터에 저장되는 사이즈를 출력한다.
    printf("sizeof(*x) = %lu\n" , sizeof(*x));
    printf("sizeof(**x) = %lu\n" , sizeof(**x));

    printf("[----- [한상준] [2017018024] -----]");

}