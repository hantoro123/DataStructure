#include <stdio.h>
#include <stdlib.h>

// 모든 행렬에 대한 함수를 선언
void print_matrix(int row_size, int column_size, int** matrix);
void addtion_matrix(int row_size, int column_size, int** matrixA, int** matrixB);
void subtraction_matrix(int row_size, int column_size, int** matrixA, int** matrixB);
void transpose_matrix(int row_size, int column_size, int **matrix);
void multiply_matrix(int row_sizeA, int column_sizeA, int row_sizeB, int column_sizeB, int** matrixA, int** matrixB);
void free_matrix(int row_size, int** matrix);

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
        // number를 입력해서 원하는 동작을 수행
        printf("\n원하는 동작의 숫자를 입력하시오\n");
        printf("1. Print Matrix\n");
        printf("2. Add Matrix\n");
        printf("3. Subtract Matrix\n");
        printf("4. Transpose Matrix\n");
        printf("5. Multiply Matrix\n");
        printf("0. 종료 \n\n");
        scanf("%d", &number);
        switch (number)
        {
        case 1:
        // case1의 경우 A, B 각 행렬을 print_matrix로 출력한다.
            printf("\nA 행렬 \n");
            print_matrix(row_size_A, column_size_A, matrixA);
            printf("\nB 행렬 \n");
            print_matrix(row_size_B, column_size_B, matrixB);
            break;
        case 2:
        // 덧셈 연산 의 경우 행, 열이 다르면 연산 불가
            if (row_size_A != row_size_B){
                printf("\n행이 달라서 연산 불가\n");
                break;
            }
            else if (column_size_A != column_size_B){
                printf("\n열이 달라서 연산 불가\n");
                break;
            }
        // case2의 경우 A, B 행렬의 합을 출력한다.
            printf("\nA 행렬 + B 행렬\n");
            addtion_matrix(row_size_A, column_size_A, matrixA, matrixB);
            break;
        case 3:
        // 뺄셈 연산 의 경우 행, 열이 다르면 연산 불가
            if (row_size_A != row_size_B){
                printf("\n행이 달라서 연산 불가\n");
                break;
            }
            else if (column_size_A != column_size_B){
                printf("\n열이 달라서 연산 불가\n");
                break;
            }
        // case3의 경우 A, B 행렬의 차를 출력한다.
            printf("\nA 행렬 - B 행렬\n");
            subtraction_matrix(row_size_A, column_size_A, matrixA, matrixB);
            break;
        case 4:
        // case4의 경우 A, B 각 행렬의 전치행렬을 출력한다.
            printf("\nA 행렬의 전치행렬 \n");
            transpose_matrix(row_size_A, column_size_A, matrixA);
            printf("\nB 행렬의 전치행렬 \n");
            transpose_matrix(row_size_B, column_size_B, matrixB);
            break;
        case 5:
        // 곱셈 연산 의 경우 A의열과 B의행이 다르면 연산 불가
            if (row_size_B != column_size_A){
                printf("\n A의열과 B의행이 달라서 연산 불가\n");
                break;
            }
        // case5의 경우 A, B 행렬의 곱을 출력한다.
            printf("\nA 행렬 * B 행렬\n");
            multiply_matrix(row_size_A, column_size_A, row_size_B, column_size_B, matrixA, matrixB);
            break;
        case 0:
            printf("\n종료합니다.\n");
            break; 

        default:
            printf("\n없는 동작입니다.\n");
            break;
        }
        
    }
    

    // A, B 행렬의 동적 할당된 메모리를 해제한다.
    free_matrix(row_size_A, matrixA);
    free_matrix(row_size_B, matrixB);

    printf("\n ------- 종료 -------\n");
    printf("[----- [한상준] [2017018024] -----]");

    return 0;

}

// 행렬을 출력하는 함수
void print_matrix(int row_size, int column_size, int** matrix){
    // 행렬의 행, 열 size를 통해서 각 값을 출력한다.
    for (int i = 0; i < row_size; i++){
        for (int j = 0; j < column_size; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

}

// 두 행렬의 합을 구하는 함수
void addtion_matrix(int row_size, int column_size, int **matrixA, int**matrixB){
    // 합한 값을 받을 최종 행렬에 row_size만큼 동적 할당 하는 부분
    int **matrix = (int **)malloc(sizeof(int*) * row_size);

    // 합한 값을 받을 행렬의 column_size만큼 동적 메모리 할당하는 부분
    for (int i = 0; i < row_size; i++){
        matrix[i] = (int*)malloc(sizeof(int) * column_size);
    }

    // 행렬의 같은 행, 같은 열 끼리 더해서 값을 받을 행렬에 저장
    for (int row = 0; row < row_size; row++){
        for (int col = 0; col < column_size; col++)
            matrix[row][col] = matrixA[row][col] + matrixB[row][col];
    }

    // 최종 행렬을 출력한다.
    print_matrix(row_size, column_size, matrix);

    // 최종 행렬에 동적 할당된 메모리를 해제한다.
    free_matrix(row_size, matrix);

}

// 두 행렬의 차를 구하는 함수
void subtraction_matrix(int row_size, int column_size, int** matrixA, int** matrixB){
    // 뺀 값을 받을 최종 행렬에 row_size만큼 동적 할당 하는 부분
    int **matrix = (int **)malloc(sizeof(int*) * row_size);

    // 뺀 값을 받을 행렬의 column_size만큼 동적 메모리 할당하는 부분
    for (int i = 0; i < row_size; i++){
        matrix[i] = (int *)malloc(sizeof(int) * column_size);
    }

    // 행렬의 같은 행, 같은 열 끼리 빼고 값을 받을 행렬에 저장
    for (int row = 0; row < row_size; row++){
        for (int col = 0; col < column_size; col++)
            matrix[row][col] = matrixA[row][col] - matrixB[row][col];
    }

    // 최종 행렬을 출력한다.
    print_matrix(row_size, column_size, matrix);

    // 최종 행렬에 동적 할당된 메모리를 해제한다.
    free_matrix(row_size, matrix);

}

// 전치행렬을 구하는 함수
void transpose_matrix(int row_size, int column_size, int **matrix){
    // 전치를 할 빈 전치 행렬에 column_size만큼 동적 할당을 하는 부분
    int **transmatrix = (int **)malloc(sizeof(int *) * column_size);

    // 전치를 할 행렬에 row_size만큼 동적 할당을 하는 부분
    for (int i = 0; i < column_size; i++){
        transmatrix[i] = (int *)malloc(sizeof(int) * row_size);
    }

    // 전치하고 싶은 행렬의 행, 열 값을 바꾸어 전치행렬에 저장
    for (int row = 0; row < row_size; row++){
        for (int col = 0; col < column_size; col++)
            transmatrix[col][row] = matrix[row][col];
    }

    // 최종 전치 행렬을 출력한다.
    print_matrix(column_size, row_size, transmatrix);

    // 전치 행렬에 동적 할당된 메모리를 해제한다.
    free_matrix(column_size, transmatrix);
}

// 두 행렬을 곱하는 함수
void multiply_matrix(int row_sizeA, int column_sizeA, int row_sizeB, int column_sizeB, int** matrixA, int** matrixB){
    // 곱한 값이 들어갈 행렬에 row_sizeA만큼 동적 할당 하는 부분
    int **matrix = (int **)malloc(sizeof(int *) * row_sizeA);

    // 곱한 값이 들어갈 행렬에 column_sizeB만큼 동적 할당 하는 부분
    for (int i = 0; i < row_sizeA; i++){
        matrix[i] = (int *)malloc(sizeof(int) * column_sizeB);
    }

    // 두 행렬의 1행 1열, 1행 2열, ... 식으로 값을 곱하고 더한다 이값을 matrix에 저장
    for (int row = 0; row < row_sizeA; row++){
        for (int col = 0; col < column_sizeB; col++){
            // 기존 matrix에 쓰레기값이 있을 수 있기 때문에 0으로 초기화
            matrix[row][col] = 0;
            for (int same = 0; same < column_sizeA; same++){
                matrix[row][col] += matrixA[row][same]*matrixB[same][col];
            }
            
        }
    }

    // 최종 행렬을 출력한다.
    print_matrix(row_sizeA, column_sizeB, matrix);

    // 최종 행렬의 동적 할당된 메모리를 해제한다.
    free_matrix(column_sizeB, matrix);

}

// 동적 할당된 메모리를 해제하는 함수
void free_matrix(int row_size, int** matrix){
    // matrix에 동적 할당된 메모리를 해제한다.
    for (int i = 0; i < row_size; i++)
            free(matrix[i]);
        free(matrix);
}