#include <stdio.h>

int main()
{
    char charType;
    int integerType;
    float floatType;
    double doubleType;

    // ���� char,int,float,double Ÿ���� �������� ũ��� 1,4,4,8 bytes�̴�.
    printf("Size of char: %ld byte\n", sizeof(charType));
    printf("Size of int: %ld bytes\n", sizeof(integerType));
    printf("Size of float: %ld byte\n", sizeof(floatType));
    printf("Size of double: %ld byte\n", sizeof(doubleType));

    printf(" ----------------------------------------- \n");

    // ������ char,int,float,double Ÿ���� ũ�� ���� 1,4,4,8 bytes�̴�.
    printf("Size of char: %ld byte\n", sizeof(char));
    printf("Size of int: %ld byte\n", sizeof(int));
    printf("Size of float: %ld byte\n", sizeof(float));
    printf("Size of double: %ld byte\n", sizeof(double));

    printf(" ----------------------------------------- \n");

    // � Ÿ���̴��� �����ͺ��� ũ���� ��� �׻� 32bits������ 4bytes�̴�. 
    printf("Size of char*: %ld byte\n", sizeof(char*));
    printf("Size of int*: %ld byte\n", sizeof(int*));
    printf("Size of float*: %ld byte\n", sizeof(float*));
    printf("Size of double*: %ld byte\n", sizeof(double*));

    printf("\n[----- [�ѻ���] [2017018024] -----]\n");
}
