#include <stdio.h>

int main()
{
    int i;
    int *ptr;
    int **dptr;

    i = 1234;

    printf("[checking values before ptr = &i] \n");
    // i의 값과 주소값을 출력
    printf("value of i == %d\n", i);
    printf("address of i == %p\n", &i);
    // 포인터 변수 ptr의 초기값과 주소값을 출력
    printf("value of ptr == %p\n", ptr);
    printf("address of ptr == %p\n", &ptr);

    ptr = &i; // i의 주소값을 포인터 변수 ptr에 대입

    printf("\n[checking values after ptr = &i] \n");
    // i의 값과 주소값을 출력
    printf("value of i == %d\n", i);
    printf("address of i == %p\n", &i);
    // ptr의 값, 주소값과 ptr에 저장되어있는 주소값에 있는 값을 출력
    printf("value of ptr == %p\n", ptr);
    printf("address of ptr == %p\n", &ptr);
    printf("value of *ptr == %d\n", *ptr);

    dptr = &ptr;

    printf("\n[checking values after dptr = &ptr] \n");
    printf("\n[checking values after ptr = &i] \n");
    // i의 값과 주소값을 출력
    printf("value of i == %d\n", i);
    printf("address of i == %p\n", &i);
    // ptr의 값, 주소값과 ptr에 저장되어있는 주소값에 있는 값을 출력
    printf("value of ptr == %p\n", ptr);
    printf("address of ptr == %p\n", &ptr);
    printf("value of *ptr == %d\n", *ptr);
    printf("value of dptr == %p\n", dptr);
    // dptr의 주소값과 dptr에 저장되어있는 주소에 있는값,
    // dptr에 저장되어있는 주소의 포인터 변수에 저장되어있는 값 출력 (이중 포인터)
    printf("address of dptr == %p\n", &dptr);
    printf("value of *dptr == %p\n", *dptr);
    printf("value of **dptr == %d\n", **dptr);

    *ptr = 7777; // ptr에 i의 주소가 저장되어 있으므로 *ptr의 값을 변경하면 i값이 변경
    // 즉 i = 7777;

    printf("\n[after *ptr = 7777] \n");
    // ptr은 i를 가리키고 dptr은 ptr을 가리키고 다시 i를 가리키므로 출력값은 7777로 같다
    printf("value of i == %d\n", i);
    printf("value of *ptr == %d\n", *ptr);
    printf("value of **dptr == %d\n", **dptr);

    **dptr = 8888; // 이중포인터로 dptr에 ptr의 주소가 저장되어있고 ptr은 i의 주소가 저장됨
    // 즉 **dptr의 값을 변경시 i값 변경 i = 8888;  

    printf("\n[after **dptr = 8888] \n");
    // ptr은 i를 가리키고 dptr은 ptr을 가리키고 다시 i를 가리키므로 출력값은 8888로 같다
    printf("value of i == %d\n", i);
    printf("value of *ptr == %d\n", *ptr);
    printf("value of **dptr == %d\n", **dptr);

    printf("\n[----- [한상준] [2017018024] -----]\n");

    return 0;
}