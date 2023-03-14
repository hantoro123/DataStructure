#include <stdio.h>

int main()
{
    int i;
    int *ptr;
    int **dptr;

    i = 1234;

    printf("[checking values before ptr = &i] \n");
    // i�� ���� �ּҰ��� ���
    printf("value of i == %d\n", i);
    printf("address of i == %p\n", &i);
    // ������ ���� ptr�� �ʱⰪ�� �ּҰ��� ���
    printf("value of ptr == %p\n", ptr);
    printf("address of ptr == %p\n", &ptr);

    ptr = &i; // i�� �ּҰ��� ������ ���� ptr�� ����

    printf("\n[checking values after ptr = &i] \n");
    // i�� ���� �ּҰ��� ���
    printf("value of i == %d\n", i);
    printf("address of i == %p\n", &i);
    // ptr�� ��, �ּҰ��� ptr�� ����Ǿ��ִ� �ּҰ��� �ִ� ���� ���
    printf("value of ptr == %p\n", ptr);
    printf("address of ptr == %p\n", &ptr);
    printf("value of *ptr == %d\n", *ptr);

    dptr = &ptr;

    printf("\n[checking values after dptr = &ptr] \n");
    printf("\n[checking values after ptr = &i] \n");
    // i�� ���� �ּҰ��� ���
    printf("value of i == %d\n", i);
    printf("address of i == %p\n", &i);
    // ptr�� ��, �ּҰ��� ptr�� ����Ǿ��ִ� �ּҰ��� �ִ� ���� ���
    printf("value of ptr == %p\n", ptr);
    printf("address of ptr == %p\n", &ptr);
    printf("value of *ptr == %d\n", *ptr);
    printf("value of dptr == %p\n", dptr);
    // dptr�� �ּҰ��� dptr�� ����Ǿ��ִ� �ּҿ� �ִ°�,
    // dptr�� ����Ǿ��ִ� �ּ��� ������ ������ ����Ǿ��ִ� �� ��� (���� ������)
    printf("address of dptr == %p\n", &dptr);
    printf("value of *dptr == %p\n", *dptr);
    printf("value of **dptr == %d\n", **dptr);

    *ptr = 7777; // ptr�� i�� �ּҰ� ����Ǿ� �����Ƿ� *ptr�� ���� �����ϸ� i���� ����
    // �� i = 7777;

    printf("\n[after *ptr = 7777] \n");
    // ptr�� i�� ����Ű�� dptr�� ptr�� ����Ű�� �ٽ� i�� ����Ű�Ƿ� ��°��� 7777�� ����
    printf("value of i == %d\n", i);
    printf("value of *ptr == %d\n", *ptr);
    printf("value of **dptr == %d\n", **dptr);

    **dptr = 8888; // ���������ͷ� dptr�� ptr�� �ּҰ� ����Ǿ��ְ� ptr�� i�� �ּҰ� �����
    // �� **dptr�� ���� ����� i�� ���� i = 8888;  

    printf("\n[after **dptr = 8888] \n");
    // ptr�� i�� ����Ű�� dptr�� ptr�� ����Ű�� �ٽ� i�� ����Ű�Ƿ� ��°��� 8888�� ����
    printf("value of i == %d\n", i);
    printf("value of *ptr == %d\n", *ptr);
    printf("value of **dptr == %d\n", **dptr);

    printf("\n[----- [�ѻ���] [2017018024] -----]\n");

    return 0;
}