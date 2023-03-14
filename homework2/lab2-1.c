#include <stdio.h>

int main()
{
    char charType;
    int integerType;
    float floatType;
    double doubleType;

    // 각각 char,int,float,double 타입의 변수들의 크기는 1,4,4,8 bytes이다.
    printf("Size of char: %ld byte\n", sizeof(charType));
    printf("Size of int: %ld bytes\n", sizeof(integerType));
    printf("Size of float: %ld byte\n", sizeof(floatType));
    printf("Size of double: %ld byte\n", sizeof(doubleType));

    printf(" ----------------------------------------- \n");

    // 각각의 char,int,float,double 타입의 크기 역시 1,4,4,8 bytes이다.
    printf("Size of char: %ld byte\n", sizeof(char));
    printf("Size of int: %ld byte\n", sizeof(int));
    printf("Size of float: %ld byte\n", sizeof(float));
    printf("Size of double: %ld byte\n", sizeof(double));

    printf(" ----------------------------------------- \n");

    // 어떤 타입이더라도 포인터변수 크기의 경우 항상 32bits에서는 4bytes이다. 
    printf("Size of char*: %ld byte\n", sizeof(char*));
    printf("Size of int*: %ld byte\n", sizeof(int*));
    printf("Size of float*: %ld byte\n", sizeof(float*));
    printf("Size of double*: %ld byte\n", sizeof(double*));

    printf("\n[----- [한상준] [2017018024] -----]\n");
}
