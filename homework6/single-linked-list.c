/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>


// Node를 구조체로 선언하며
typedef struct Node {
    // Key값과 다음을 가리키는 link로 이루어져있다.
	int key;
	struct Node* link;
} listNode;

// headnode를 구조체로 선언
typedef struct Head {
    // linked-list에 첫번째를 가리킬 값.
	struct Node* first;
}headNode;


// 각 함수들을 선언
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
    // command와 key값으로 들어갈 변수 선언
	char command;
	int key;
    // 아직 list의 head값이 없기 때문에 null값으로 초기화
	headNode* headnode=NULL;

	do{
        // 간단한 UI
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
        // command를 입력받으면
		scanf(" %c", &command);

        // command에 따라 해당 함수를 실행
		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

    printf("[----- [한상준] [2017018024] -----]");

	return 1;
}

// headNode를 초기화 하는 함수
headNode* initialize(headNode* h) {

	// Head가 0이면 free해준다.
	if(h != NULL)
		freeList(h);

	// temp를 headNode형 변수로 동적 할당 하고
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	// temp에 첫번째 link를 NULL값으로 초기화하여 반환한다.
	temp->first = NULL;
	return temp;
}

// linked list의 동적 할당을 해제
int freeList(headNode* h){
	
	// listNode형 포인터 p에 head의 first link를 준다.
	listNode* p = h->first;

	// listNode형의 포인터 prev를 Null로 초기화 하고
	listNode* prev = NULL;
	// p가 null이 아닐때까지
	while(p != NULL) { 
		// prev에 p를 저장하고
		prev = p; 
		// p에 p가 가리키는 link를 넣어준다.
		p = p->link;
		// prev의 동적 할당을 해제
		free(prev);
	}
	// headnode까지 동적 할당을 한다.
	free(h);
	return 0;
}


// linked list에 노드를 삽입하는 함수
int insertNode(headNode* h, int key) {

	// listNode형의 포인터 node를 동적 할당 받는다.
	listNode* node = (listNode*)malloc(sizeof(listNode));
	// node의 key값은 key로 받고, link는 null값으로 초기화 한다.
	node->key = key;
	node->link = NULL;

	// head의 first가 Null값이면
	if (h->first == NULL)
	{
		// 처음 만든 node를 headnode의 first로 지정
		h->first = node;
		return 0;
	}

	// listNode의 포인터로 n과 trail에 head의 first 주소를 저장
	listNode* n = h->first;
	listNode* trail = h->first;

	/* key를 기준으로 위치를 찾는다. */
	// n이 null이 아니면 반복
	while(n != NULL) {
		// n의 key이 받아온 key값보다 크거나 같다면 
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야하는 경우 */
			if(n == h->first) {
				// head의 first를 node의 주소로 변경
				h->first = node;
				// node의 link는 n의 주소로 변경
				node->link = n;
			} else { /* 그외의 위치는 */
				// node의 link를 n의 주소로 변경
				node->link = n;
				// trail의 link를 node의 주소로 변경
				trail->link = node;
			}
			return 0;
		}

		// 받아온 key값이 더 크면
		// trail에 n을 저장하고 n이 n의 link값이 된다.
		trail = n;
		n = n->link;
	}

	/* 마지막 노드까지 찾지 모하면 마지막에 넣는다. */
	// trail의 link에 node의 주소로 변경
	trail->link = node;
	return 0;
}

/**
 * list의 마지막에 key에 대한 노드를 추가
 */
// key값을 head에 연결된 list의 마지막에 삽입하는 함수
int insertLast(headNode* h, int key) {

	// listNode형의 포인터 node를 동적 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	// node의 key값은 받은 key값으로
	node->key = key;
	// node의 link는 null값으로 초기화
	node->link = NULL;

	// head의 first가 null이라면
	if (h->first == NULL)
	{
		// head의 first에 node의 주소를 넘겨준다   
		h->first = node;
		return 0;
	}

	// listNode형 포인터 n에 head의 first 주소값을 받는다.
	listNode* n = h->first;
	// n의 link값이 null이 아니면 반복
	while(n->link != NULL) {
		// n의 link값을 n에 넣는다.
		n = n->link;
	}
	// node의 주소를 n의 link에 넣는다.
	n->link = node;
	return 0;
}

/**
 * list의 처음에 key에 대한 노드를 추가 하는 함수
 */
int insertFirst(headNode* h, int key) {

	// listNode형 포인터 node를 동적 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	// node의 key에 받은 key값을 넣어준다.
	node->key = key;

	// node의 link에 head의 first값으로 변경
	node->link = h->first;
	// head의 first를 node의 주소로 변경
	h->first = node;

	return 0;
}

/**
 * list에서 key값이 있는 노드 삭제 하는 함수
 */
// 
int deleteNode(headNode* h, int key) {

	// head의 first가 null값이면
	if (h->first == NULL)
	{
		// 삭제할 수 없다는 것을 출력
		printf("nothing to delete.\n");
		return 0;
	}

	// listNode형의 포인터 n, trail을 선언후
	// n에는 head의 first, trail에는 null값으로 초기화
	listNode* n = h->first;
	listNode* trail = NULL;

	/* key를 기준으로 삭제 */
	// n값이 null이 아니면 반복
	while(n != NULL) {
		// n의 key값이 받은 key값과 같다면
		if(n->key == key) {
			// n이 head의 first즉 첫번째 노드인지 검사
			if(n == h->first) {
				// 맞으면 head의 first를 n의 link로 변경
				h->first = n->link;
			} else { // 첫번째가 아니면
				// trail의 link에 n의 link를 넣어준다.
				trail->link = n->link;
			}
			// 삭제된 node는 할당을 해제
			free(n);
			return 0;
		}
		// trail에 n을 넣고 n에 n의 link를 넣는다.
		trail = n;
		n = n->link;
	}

	/* 찾지 못하면 값이 없다는 메세지 출력 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드를 삭제하는 함수
 */
int deleteLast(headNode* h) {

	// head의 first가 Null이면
	if (h->first == NULL)
	{
		// 삭제할게 없다고 메세지 출력
		printf("nothing to delete.\n");
		return 0;
	}

	// listNode형의 포인터 n, trail선언 후
	// n은 head의 first, trail은 Null값으로 초기화
	listNode* n = h->first;
	listNode* trail = NULL;

	// n의 link가 null이라면 노드가 하나이다
	if(n->link == NULL) {
		// head의 first를 null로 초기화 해주고
		h->first = NULL;
		// 노드를 할당 해제해준다.
		free(n);
		return 0;
	}

	// n의 link가 null이 아니면 반복
	while(n->link != NULL) {
		// trail에 n을 넣어주고
		trail = n;
		// n은 n의 link로 변경
		n = n->link;
	}

	// 마지막으로 와서 trail의 link를 Null로 초기화 해주고
	trail->link = NULL;
	// 노드를 할당 해제 한다.
	free(n);

	return 0;
}
/**
 * list의 첫번째 노드를 삭제하는 함수
 */
int deleteFirst(headNode* h) {

	// head의 first가 Null값이면
	if (h->first == NULL)
	{
		// 삭제게 수 없다는 메세지 출력
		printf("nothing to delete.\n");
		return 0;
	}
	// listNode형 포인터 n에 head의 first를 넣어준다.
	listNode* n = h->first;

	// head의 first를 n의 link로 변경해주고
	h->first = n->link;
	// 노드를 할당 해제 한다.
	free(n);

	return 0;
}


/**
 * list를 역으로 배치하는 함수
 */
int invertList(headNode* h) {

	// head의 first가 null이라면
	if(h->first == NULL) {
		// 재배치 할 list가 없다고 출력
		printf("nothing to invert...\n");
		return 0;
	}

	// listNode의 포인터로 n, trail, middle을 선언
	// n에 head의 first, trail과 middle에 null값으로 초기화
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	// n가 null이 아니면 반복
	while(n != NULL){
		// trail은 middle
		trail = middle;
		// middle은 n
		middle = n;
		// n은 n의 link로 변경
		n = n->link;
		// middle의 link에 trail을 넣는다.
		middle->link = trail;
	}

	// head의 first에 middle값을 넣는다.
	h->first = middle;

	return 0;
}

// List를 출력하는 함수
void printList(headNode* h) {
	// index를 받을 변수 0으로 초기화
	int i = 0;
	// listNode형 포인터 p 선어
	listNode* p;

	printf("\n---PRINT\n");
	// head가 null 이면 출력값이 없다는 메세지 출력
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	// 출력할게 있으면 p에 head의 first값을 넣어준다.
	p = h->first;

	// p가 null이 아니면 반복
	while(p != NULL) {
		// index와 p의 key값을 출력
		printf("[ [%d]=%d ] ", i, p->key);
		// p값을 p가 가리키는 link로 변경
		p = p->link;
		// i값도 증가
		i++;
	}
	// 몇개의 item이 있는지 출력
	printf("  items = %d\n", i);
}
