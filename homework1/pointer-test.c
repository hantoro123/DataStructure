#include <stdio.h>

int main()
{
    int i, *p;
    
    i = 10;

    // i가 가진 데이터 값을 10진수 정수 형태로 출력
    printf("value of i = %d\n", i);   
    // i의 현재 주소를 출력                   
    printf("address of 1 = %p\n", &i);      
    // 임의로 저장된 p의 초기 값을 출력
    printf("value of p = %p\n", p); 
    // p의 현재 주소 출력                     
    printf("address of p = %p\n", &p);                   

    // p에 i의 주소값을 대입
    p = &i;                                              

    // p의 주소값을 10진 정수 형태로 출력
    printf("\n\n---- after p = %i ------------\n\n");    

    // p가 가진 값을 주소값 형태로 출력
    printf("value of p = %p\n", p);   
    // p의 현재 주소 값을 출력                    
    printf("address of p = %p\n", &p);      
    // 포인터 변수p에 있는 주소에 저장되어 있는 데이터 값을 출력              
    printf("dereferencing *p = %d\n", *p);               

    return 0;
}