#include <stdio.h>

#define MAX_SIZE 100

// sum1, sum2, sum3 각 함수를 선언
float sum1(float list[], int);
float sum2(float *list, int);
float sum3(int n, float *list);

// 변수 선언
float input[MAX_SIZE], answer;
int i;
void main(void){
    for(i=0; i < MAX_SIZE; i++)
        input[i] = i;
    
    // sum1함수를 통해 총합을 계산
    printf("-------------------------------\n");
    printf(" sum1(input, MAX_SIZE) \n");
    printf("-------------------------------\n");
    // input배열의 주소값을 출력
    printf("input \t= %p\n", input);

    
    answer = sum1(input, MAX_SIZE);
    // sum1에서 input, MAX_SIZE를 넣어 나온 총 합의 값을 float형태로 출력
    printf("The sum is: %f\n\n", answer);

    // sum2함수를 통해 총합을 계산
    printf("-------------------------------\n");
    printf(" sum2(input, MAX_SIZE) \n");
    printf("-------------------------------\n");
    // input배열의 주소값을 출력
    printf("input \t= %p\n", input);

    answer = sum2(input, MAX_SIZE);
     // sum2에서 input, MAX_SIZE를 넣어 나온 총 합의 값을 float형태로 출력
    printf("The sum is: %f\n\n", answer);

    // sum3함수를 통해 총합을 계산
    printf("-------------------------------\n");
    printf(" sum3(input, MAX_SIZE) \n");
    printf("-------------------------------\n");
    // input배열의 주소값을 출력
    printf("input \t= %p\n", input);

    answer = sum3(MAX_SIZE, input);
    // sum3에서 MAX_SIZE, input를 넣어 나온 총 합의 값을 float형태로 출력
    printf("The sum is: %f\n\n", answer);

    printf("[----- [한상준] [2017018024] -----]");
}

// list[]는 call by reference n은 call by value로 접근
float sum1(float list[], int n){
    // list는 input배열의 주소 &list는 input배열 주소를 저장할 배열의 현 주소값을 출력한다.
    printf("list \t= %p\n", list);
    printf("&list \t= %p\n\n", &list);

    int i;
    float tempsum = 0;
    // 반복문을 통해 list[i] 주소에 있는 값을 계속 더해 총합을 구한다.
    for(i=0; i<n; i++)
        tempsum += list[i];
    // tempsum을 return
    return tempsum;
}

// *list는 call by reference n은 call by value로 접근
float sum2(float *list, int n){
    // list는 input배열의 주소 &list는 input배열 주소를 저장할 배열의 현 주소값을 출력한다.
    printf("list \t= %p\n", list);
    printf("&list \t= %p\n\n", &list);

    int i;
    float tempsum = 0;
    // 반복문을 통해 list[i] 주소에 있는 값을 계속 더해 총합을 구한다.
    for(i=0; i<n; i++)
        tempsum += *(list + i);
    // tempsum을 return
    return tempsum;
}

// n은 call by value *list는 call by reference로 접근
float sum3(int n, float *list){
    // list는 input배열의 주소 &list는 input배열 주소를 저장할 배열의 현 주소값을 출력한다.
    printf("list \t= %p\n", list);
    // &list의 경우 매개변수의 위치가 달라져 sum1과 sum2와 달리 int n이 먼저 stack에 쌓임
    // 따라서 sum1,sum2와 달리 list배별 주소가 4bytes 더크다.
    printf("&list \t= %p\n\n", &list);

    int i;
    float tempsum = 0;
    // 반복문을 통해 list[i] 주소에 있는 값을 계속 더해 총합을 구한다.
    for(i=0; i<n; i++)
        tempsum += *(list + i);
    // tempsum을 return
    return tempsum;
}