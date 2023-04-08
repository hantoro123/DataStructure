#include <stdio.h>
#include <stdlib.h>

int main(){
    // 각각의 행과 열의 size를 담을 변수
    int row_size;
    int column_size;

    // 행과 열의 사이즈를 입력
    printf("행의 사이즈를 입력해주세요 : ");
    scanf("%d", &row_size);
    printf("열의 사이즈를 입력해주세요 : ");
    scanf("%d", &column_size);

    // row_size만큼 동적 메모리 할당하는 부분
    int **matrix = (int **)malloc(sizeof(int*) * row_size);

    // column_size만큼 동적 메모리 할당하는 부분
    for (int i = 0; i < row_size; i++){
        matrix[i] = (int*)malloc(sizeof(int) * column_size);
    }

    // 행렬을 값을 입력
    for (int i = 0; i < row_size; i++){
        for (int j = 0; j < column_size; j++){
            scanf("%d", &matrix[i][j]);
        }
    }

    // 행렬 확인
    for (int i = 0; i < row_size; i++){
        for (int j = 0; j < column_size; j++){
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }

    // 동적 할당된 메모리 해제
    for (int i = 0; i < row_size; i++)
        free(matrix[i]);
    free(matrix);

    return 0;

}