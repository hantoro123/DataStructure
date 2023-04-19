/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  School of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

// queue의 element를 char로 타입 지정
typedef char element;
// QueueType으로 queue를 구조체로 선언
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

// 각 함수를 선언
QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
    // 구조체로 cQ라는 queue생성, data라는 element생성
	QueueType *cQ = createQueue();
	element data;
    // 동작할 command 변수
	char command;

    // command를 먼저 입력하고 q,Q를 입력하면 반복 종료
	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

        // command를 입력하면 해당 command를 실행
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
            // command가 입력되면 각 case를 실행
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
            // case에 없는 command를 입력하면 출력 
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

    printf("[----- [한상준] [2017018024] -----]");
	return 1;
}

// QueueType을 이용한 Queue를 생성하는 포인터 함수
QueueType *createQueue()
{
    // cQ의 값을 바꾸기 위해서 포인터로 생성
	QueueType *cQ;
    // queue의 사이즈를 QueueType만큼 동적할당
	cQ = (QueueType *)malloc(sizeof(QueueType));
	// queue의 front와 rear을 0으로 초기화
    cQ->front = 0;
	cQ->rear = 0;
    // 최종적으로 생성된 cQ return
	return cQ;
}

// Queue의 동적할당을 해제하는 함수
int freeQueue(QueueType *cQ)
{
    // queue가 없으면 바로 return
    if(cQ == NULL) return 1;
    // queue가 있으면 free
    free(cQ);
    return 1;
}

// Queue의 enqueue 할때 element의 data를 받을 함수
element getElement()
{
    // element의 item 변수
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
    // char형태로 받아 return
	return item;
}


// Queue가 비었는지 확인하는 함수
int isEmpty(QueueType *cQ)
{
    // queue의 front와 rear가 같다면 비어있는것
    if (cQ -> front == cQ -> rear){
        // 비어있음을 출력하고 1을 return
        printf("Circular Queue is empty");
        return 1;
    }
    // 비어있지 않다면 0을 return
    else return 0;
}

// Queue가 다 찼는지 확인하는 함수
int isFull(QueueType *cQ)
{
    // queue에서 (rear+1)%MAX_QUEUE_SIZE와 front가 같다면 다 찼다는 것
    if (((cQ -> rear + 1)%MAX_QUEUE_SIZE) == cQ -> front){
        // 다 찼다는 것을 출력하고 1을 return
        printf("Circular Queue is full!");
        return 1;
    }
    // 다 차지 않았다면 0을 return
    else return 0;
}

// Queue에 item을 넣는 함수
void enQueue(QueueType *cQ, element item)
{
    // queue가 다 찼다면 바로 return
    if(isFull(cQ)) return;
    // queue가 아직 자리가 있다면
    else{
        // rear가 (rear+1)%MAX_QUEUE_SIZE로 증가하고
        cQ -> rear = (cQ -> rear + 1)%MAX_QUEUE_SIZE;
        // 바뀐 rear에 item을 넣고 return
        cQ -> queue[cQ->rear] = item;
        return;
    }
}

// Queue에 item을 제거하는 함수
void deQueue(QueueType *cQ, element *item)
{
    // queue가 비어있다면 바로 return
    if (isEmpty(cQ)) return;
    // queue가 비어있지 않으면
    else{
        // front가 (front+1)%MAX_QUEUE_SIZE로 증가하고
        cQ -> front = (cQ -> front + 1)%MAX_QUEUE_SIZE;
        // item의 값을 front에 있는 값으로 바꾸고 return
        *item = cQ -> queue[cQ -> front];
        return;
    }
}

// Queue를 print하는 함수
void printQ(QueueType *cQ)
{
    // 각 위치를 받을 변수를 int형으로 선언
	int i, first, last;

    // first와 last를 cQ의 (front + 1)%MAX_QUEUE_SIZE, (rear + 1)%MAX_QUEUE_SIZE
	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");
    // i에 first를 넣고
	i = first;
    // i가 last가 될때까지 queue를 돌며 하나씩 출력
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}

// Queue를 디버그 하기위한 함수
void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
    // MAX_QUEUE_SIZE 만큼 반복하면서
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
        // cQ의 i가 front라면 [i] = front를 출력
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
        // i가 증가함에 따라 각 인덱스의 값을 출력
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
    // 현재 front와 rear가 어떤 인덱스에 있는지 출력
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

