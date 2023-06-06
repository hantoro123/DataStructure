/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 배열을 초기화하고 free하고 출력하는 함수 선언 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

// 각 sorting에 대한 함수 선언
int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function�쇰줈 援ы쁽 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* hasinh하는 함수 */
int hashing(int *a, int **ht);

/* hash테이블을 통해 검색하느 ㅎ마수 */
int search(int *ht, int key);


int main()
{
    // 각 변수 선언
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');
    printf("[----- [한상준] [2017018024] -----]");
	return 1;
}

// array를 초기화 하는 함수
int initialize(int** a)
{
    // 포인터 temp를 NULL한다.
	int *temp = NULL;

	/* array가 NULL이면 */
	if(*a == NULL) {
        // temp에 int사이즈*max_array_size 만큼 동적 할당
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* a가 temp를 가리킨다. */
	} else
        // 아니라면 temp에 a를 넣는다.
		temp = *a;

	/* i의 max_array_siez만큼 반복하면서 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        // 0~max_array_size-1 만큼의 random값을 각 인덱스에 넣는다.
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

// array를 free하는 함수
int freeArray(int *a)
{
    // a가 NULL이 아니면
	if(a != NULL)
        // a를 free해준다.
		free(a);
	return 0;
}

// array를 출력하는 함수
void printArray(int *a)
{
    // a가 NULL이면 출력할게 없다고 하고 반환
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
    // i를 0부터 max_array_size보다 작을때까지 반복하며 인덱스를 출력
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
    // i를 0부터 max_array_size보다 작을때까지 반복하며 값을 출력
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

// 선택정렬에 대한 함수
int selectionSort(int *a)
{
    // 각 변수를 선언하고
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

    // a를 출력하고
	printArray(a);

    // max_array_size만큼 반복하며
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
        // minindex는 i, min은 a[i]를 넣고
		minindex = i;
		min = a[i];
        // i+1부터 끝까지 반복하며
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
            // min보다 a[j]가 작으면
			if (min > a[j])
			{
                // min을 a[j]로 바꾸고
				min = a[j];
                // minindex를 j로 바꾼다.
				minindex = j;
			}
		}
        // 찾은 minindex를 a[i]와 바꾸고
		a[minindex] = a[i];
        // a[i]는 min으로 바꾼다.
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
    // 정렬된 a를 출력하고 반환
	printArray(a);
	return 0;
}

// 삽입정렬을 위한 함수
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");
	// 기존 array를 출력하고
	printArray(a);

	// max_array_size 만큼 반복하며
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		// t에 a[i]를 넣고
		t = a[i];
		// j에 현재 위치인 i를 넣고
		j = i;
		// a[j-1]가 t가 크고 j가 0보다 크다면 반복
		while (a[j-1] > t && j > 0)
		{
			// a[j]에 j-1에 있는 값을 넣고
			a[j] = a[j-1];
			// j - 1을 해준다.
			j--;
		}
		// 반복이 종료되면 t의 값을 a[j]에 넣는다.
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	// 정렬된 a를 출력
	printArray(a);

	return 0;
}

// bubble정렬을 하는 함수
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");
	// 기존 a를 출력하고
	printArray(a);

	// i를 max_array_size만큼 반복하고
	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		// j도 1부터 max_array_size+1만큼 반복하며
		for (j = 1; j < MAX_ARRAY_SIZE+1; j++)
		{
			// a[j-1]이 a[j]보다 크다면
			if (a[j-1] > a[j])
			{
				// t를 a[j-1]로 바꾸고
				t = a[j-1];
				// a[j-1]을 a[j]로 바꾸고
				a[j-1] = a[j];
				// a[j]를 t로 바꿔서 j-1, j를 swap한다.
				a[j] = t;
			}
		}
		
	}

	printf("----------------------------------------------------------------\n");
	// 정렬된 a를 출력한다.
	printArray(a);

	return 0;
}

// shell정렬을 하기위한 함수
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");
	// 기존 array를 출력한다.
	printArray(a);

	// h를 max_array_size/2 부터 0보다 클때까지 2씩 나누면서 반복
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		// i는 0부터 h까지의 범위까지 반복
		for (i = 0; i < h; i++)
		{
			// j는 i+h부터 max_array_size까지 h씩 증가하면서 반복
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				// v에 a[j]를 넣고
				v = a[j];
				// k에 j를 넣고
				k = j;
				// k가 h-1보다 크고 a[k-h]가 v보다 크면 반복
				while (k > h-1 && a[k-h] > v)
				{
					// a[k]를 a[k-h]로 바꾸고
					a[k] = a[k-h];
					// k를 - h 한다.
					k -= h;
				}
				// 반복이 종료되면 a[k]에 v를 넣는다.
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	// 정렬된 a를 출력한다.
	printArray(a);

	return 0;
}

// quick정렬 하는 함수
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	// n이 1보다 크다면
	if (n > 1)
	{
		// v에 a[n-1]을 넣고
		v = a[n-1];
		// i는 -1, j는 n-1을 넣는다.
		i = -1;
		j = n - 1;

		while(1)
		{
			// a[++i]이 v보다 작으면 반복하며 v보다 작아지는 i를 찾는다.
			while(a[++i] < v);
			// a[--j]가 v보다 크면 반복하며 v보다 커지는 j를 찾는다.
			while(a[--j] > v);

			// i가 j보다 크거나 같으면 종료
			if (i >= j) break;
			// 아니라면 t에 a[i]를 넣고
			t = a[i];
			// a[i]에 a[j]를 넣고
			a[i] = a[j];
			// a[j]에 t를 넣고 i와 j를 swap한다.
			a[j] = t;
		}
		// 반복이 끝나면 i와 n-1을 swap한다.
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		// a와 i를 넣고 recursive하게 quick정렬을 실행
		quickSort(a, i);
		// 다음으로 a+i+1과 n-i-1을 넣고 recursive하게 quick정렬을 실행
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

// key값에 대한 hash코드를 반환하는 함수
int hashCode(int key) {
	// key의 max_hash_table_size로 나눈 나머지값을 반환
	return key % MAX_HASH_TABLE_SIZE;
}

// array를 hashing하는 함수
int hashing(int *a, int **ht)
{
	// hashtable의 포인터를 NULL로 초기화 하고
	int *hashtable = NULL;

	/* ht가 NULL이면 */
	if(*ht == NULL) {
		// hashtable을 int*(max_array_size) 사이즈 만큼 동적 할당하고
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* ht포인터가 hashtable을 가리킨다. */
	} else { // 아니라면
		hashtable = *ht;	/* hashtable이 ht의 값을 사용. */
	}

	// i가 0부터 max_hash_table_size만큼 반복하며
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		// hashtable각각에 -1을 넣고
		hashtable[i] = -1;

	// hashcode와 key, index를 -1로 초기화하여 선언하고
	int key = -1;
	int hashcode = -1;
	int index = -1;

	// i가 0부터 max_array_size만큼 반복하고
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		// key에 a[i]를 넣고
		key = a[i];
		// key를 hashcode로 바꿔 넣는다.
		hashcode = hashCode(key);

		// hashtable[hashcode]가 -1이라면
		if (hashtable[hashcode] == -1)
		{	// 해당 부분에 key값을 넣고
			hashtable[hashcode] = key;
		} else 	{
			// 아니라면 index에 hashcode값을 넣고
			index = hashcode;

			// hashtable[index]에 -1이 아니면 반복하며
			while(hashtable[index] != -1)
			{
				// index를 하나씩 증가시키고 max_hash_table_size로 나눈 나머지 값을 넣는다.
				index = (++index) % MAX_HASH_TABLE_SIZE;
			}
			// -1을 찾으면 그부분에 key값을 넣는다.
			hashtable[index] = key;
		}
	}

	return 0;
}

// hashtable의 값을 탐색하는 함수
int search(int *ht, int key)
{
	// index에 key에 해당하는 hashcode를 넣고
	int index = hashCode(key);

	// ht[index]가 key값과 같으면
	if(ht[index] == key)
		// index를 반환하고
		return index;

	// ht[++index]가 key와 다르면 반복하고
	while(ht[++index] != key)
	{
		// index의 값을 max_hash_table_size값으로 나눈 나머지 값으로 넣어 hashcode로 변환
		index = index % MAX_HASH_TABLE_SIZE;
	}
	// 찾으면 찾은 값의 index값을 반환
	return index;
}


