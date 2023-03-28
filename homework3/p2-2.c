#include <stdio.h>

// print_one 함수 선언
void print_one(int *ptr, int rows);

int main(){
    int one[] = {0, 1, 2, 3, 4};

    // one, &one, %one[0] 모두 one배열의 첫번째 주소를 가리킨다.
    printf("one      =%p\n", one);
    printf("&one     =%p\n", &one);
    printf("&one[0]  =%p\n", &one[0]);
    printf("\n");

    printf("-----------------------------------\n");
    printf(" print_one(&one[0], 5)\n");
    printf("-----------------------------------\n");
    print_one(&one[0], 5);
    // 따라서 &one[0], one 모두 one배열의 첫번째 주소를 넣어준다. 
    printf("-----------------------------------\n");
    printf(" print_one(one, 5)\n");
    printf("-----------------------------------\n");
    print_one(one, 5);
        
    return 0;
}

void print_one(int *ptr, int rows){
    int i;
    printf("Address \t Contents\n");
    for (i=0; i<rows; i++)
        // 포인터 ptr은 초기 주소값이며 포인터이기 때문에 int 만큼의 메모리를 갖는다.
        // 따라서 address가 4bytes만큼 커지고 다음값을 가져온다.
        printf("%p \t %5d\n", ptr + i, *(ptr + i));
    printf("\n");
}