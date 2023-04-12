#include <stdio.h>
#include <stdlib.h>

void print_matrix(int row_size, int column_size, int** matrix);
void addtion_matrix(int row_size, int column_size, int** matrixA, int** matrixB);
void subtraction_matrix(int row_size, int column_size, int** matrixA, int** matrixB);
// void traspose_matrix(int row_size, int column_size, int **matrix);
// void multiply_matrix(int** matrixA, int** matrixB);


int main(){
    // A 행렬의 각각의 행과 열의 size를 담을 변수
    int row_size_A;
    int column_size_A;

    // A 행렬의 행과 열의 사이즈를 입력
    printf("A행렬의 행 사이즈를 입력해주세요 : ");
    scanf("%d", &row_size_A);
    printf("A행렬의 열 사이즈를 입력해주세요 : ");
    scanf("%d", &column_size_A);

    // A 행렬의 row_size만큼 동적 메모리 할당하는 부분
    int **matrixA = (int **)malloc(sizeof(int*) * row_size_A);

    // A 행렬의 column_size만큼 동적 메모리 할당하는 부분
    for (int i = 0; i < row_size_A; i++){
        matrixA[i] = (int*)malloc(sizeof(int) * column_size_A);
    }

    // A 행렬의 값을 입력
    printf("A 행렬의 값을 입력해주세요 \n");
    for (int i = 0; i < row_size_A; i++){
        for (int j = 0; j < column_size_A; j++){
            scanf("%d", &matrixA[i][j]);
        }
    }

    // B행렬의 각각의 행과 열의 size를 담을 변수
    int row_size_B;
    int column_size_B;

    // B행렬의 행과 열의 사이즈를 입력
    printf("B행렬의 행 사이즈를 입력해주세요 : ");
    scanf("%d", &row_size_B);
    printf("B행렬의 열 사이즈를 입력해주세요 : ");
    scanf("%d", &column_size_B);

    // B행렬의 row_size만큼 동적 메모리 할당하는 부분
    int **matrixB = (int **)malloc(sizeof(int*) * row_size_B);

    // B행렬의 column_size만큼 동적 메모리 할당하는 부분
    for (int i = 0; i < row_size_B; i++){
        matrixB[i] = (int*)malloc(sizeof(int) * column_size_B);
    }

    // B행렬의 값을 입력
    printf("B 행렬의 값을 입력해주세요 \n");
    for (int i = 0; i < row_size_B; i++){
        for (int j = 0; j < column_size_B; j++){
            scanf("%d", &matrixB[i][j]);
        }
    }

    int number;
    

    while (number != 0) {

        printf("\n원하는 동작의 숫자를 입력하시오\n");
        printf("1. Print Matrix\n");
        printf("2. Add Matrix\n");
        printf("3. Subtract Matrix\n");
        printf("4.\n");
        printf("5.\n");
        printf("0. 종료 \n");
        scanf("%d", &number);
        switch (number)
        {
        case 1:
            print_matrix(row_size_A, column_size_A, matrixA);
            print_matrix(row_size_B, column_size_B, matrixB);
            break;
        case 2:
            addtion_matrix(row_size_A, column_size_A, matrixA, matrixB);
            break;
        case 3:
            subtraction_matrix(row_size_A, column_size_A, matrixA, matrixB);
            break;
        
        default:
            break;
        }
        
    }
    

    // 동적 할당된 메모리 해제
    for (int i = 0; i < row_size_A; i++)
        free(matrixA[i]);
    free(matrixA);

    for (int i = 0; i < row_size_B; i++)
        free(matrixB[i]);
    free(matrixB);

    return 0;

}

void print_matrix(int row_size, int column_size, int** matrix){
    for (int i = 0; i < row_size; i++){
        for (int j = 0; j < column_size; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

}

void addtion_matrix(int row_size, int column_size, int **matrixA, int**matrixB){
    int **matrix = (int **)malloc(sizeof(int*) * row_size);

    // A 행렬의 column_size만큼 동적 메모리 할당하는 부분
    for (int i = 0; i < row_size; i++){
        matrix[i] = (int*)malloc(sizeof(int) * column_size);
    }

    for (int row = 0; row < row_size; row++){
        for (int col = 0; col < column_size; col++)
            matrix[row][col] = matrixA[row][col] + matrixB[row][col];
    }

    print_matrix(row_size, column_size, matrix);

    // 동적 할당된 메모리 해제
    for (int j = 0; j < row_size; j++)
        free(matrix[j]);
    free(matrix);

}

void subtraction_matrix(int row_size, int column_size, int** matrixA, int** matrixB){
    int **matrix = (int **)malloc(sizeof(int*) * row_size);

    // A 행렬의 column_size만큼 동적 메모리 할당하는 부분
    for (int i = 0; i < row_size; i++){
        matrix[i] = (int*)malloc(sizeof(int) * column_size);
    }

    for (int row = 0; row < row_size; row++){
        for (int col = 0; col < column_size; col++)
            matrix[row][col] = matrixA[row][col] - matrixB[row][col];
    }

    print_matrix(row_size, column_size, matrix);

    // 동적 할당된 메모리 해제
    for (int j = 0; j < row_size; j++)
        free(matrix[j]);
    free(matrix);

}