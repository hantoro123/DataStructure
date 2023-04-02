#include <stdio.h>

struct student {
    // �� ����� �������� �������
    char lastName[13]; // 13bytes
    int stduentID; // 4bytes
    short grade; // 2bytes
};

int main(){
    // ����ü�� Ÿ���� �����Ǿ� ���� �ʾ� struct�� ����Ͽ� ����
    struct student pst;

    // struct student �� ��� ������ 19bytes�� ����� ����Ǿ�� �ϴµ�
    // padding�� ���ؼ� lastName[13]�� 13+3(�����) = 16bytes
    // int�� 4byte�״�� short�� ��� 2+2(�����) = 4bytes�� �� 24bytes�� ��µ�
    printf("size of student = %ld\n", sizeof(struct student));
    printf("size of int     = %ld\n", sizeof(int));
    printf("size of short   = %ld\n", sizeof(short));

    printf("[----- [�ѻ���] [2017018024] -----]");

    return 0;
}