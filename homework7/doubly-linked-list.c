/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>

/* �꾩슂�� �ㅻ뜑�뚯씪 異붽� if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �⑥닔 由ъ뒪�� */

/* note: initialize�� �댁쨷�ъ씤�곕� 留ㅺ컻蹂��섎줈 諛쏆쓬 */
int initialize(headNode** h);

/* note: freeList�� �깃��ъ씤�곕� 留ㅺ컻蹂��섎줈 諛쏆쓬
        - initialize�� �� �ㅻⅨ吏� �댄빐 �좉쾬
        - �댁쨷�ъ씤�곕� 留ㅺ컻蹂��섎줈 諛쏆븘�� �댁젣�� �� �덉쓣 寃� */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	// command와 key가 들어갈 변수 선언
	char command;
	int key;
	// headNode형 포한터 headnode를 Null값으로 초기화
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);
		// command를 입력받고

		// command가 해당 case에 존재하면 해당하는 함수를 실행
		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
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

// Linked list를 초기화 하는 함수
int initialize(headNode** h) {

	// Head가 Null이 아니면 free해준다.
	if(*h != NULL)
		freeList(*h);

	// 포인터 h를 headNode형 변수로 동적 할당 하고
	*h = (headNode*)malloc(sizeof(headNode));
	// temp에 첫번째 link를 NULL값으로 초기화하여 반환한다.
	(*h)->first = NULL;
	return 1;
}

// linked list에 동적 할당을 해제하는 함수
int freeList(headNode* h){
	// listNode형 포인터 p에 head의 first link를 준다.
	listNode* p = h->first;
	// listNode형의 포인터 prev를 Null로 초기화 하고
	listNode* prev = NULL;
	// p가 null이 아닐때까지
	while(p != NULL) { 
		// prev에 p를 저장하고
		prev = p; 
		// p에 p가 가리키는 rlink를 넣어준다.
        p = p->rlink;
		// prev의 동적 할당을 해제
		free(prev);
	}
	// headnode까지 동적 할당을 한다.
	free(h);
	return 0;
}

// linked list를 출력하는 함수
void printList(headNode* h) {
	// i를 0으로 초기화해서 선언
	int i = 0;
	// listNode형 포인터 p
	listNode* p;

	printf("\n---PRINT\n");

	// headnode가 Null이면 list가 없다고 출력
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	// 있다면 p에 head의 first를 저장하고
	p = h->first;

	// p가 Null이 아니라면 반복
	while(p != NULL) {
		// 현채 p의 key값, i값을 출력
		printf("[ [%d]=%d ] ", i, p->key);
		// p의 rlink값을 p로
		p = p->rlink;
		// i도 1을 추가한다.
		i++;
	}
	// 총 item의 개수를 출력한다.
	printf("  items = %d\n", i);
}


// Key값을 node에 넣는 함수
int insertNode(headNode* h, int key) {

	// listNode형 포인터 node에 listNode의 사이즈 만큼 동적 할당한다.
	listNode* node = (listNode*)malloc(sizeof(listNode));
	// node의 key에 key값을 넣고 llink rlink를 Null로 초기화 한다.
	node->key = key;
	node->llink = node->rlink = NULL;

	// head의 first가 Null이면 node를 head의 first로 한다.
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	// listNode형 포인터 n에 head의 first를 넣는다.
	listNode* n = h->first;

	// n이 Null이 아니라면
	while(n != NULL) {
		// n의 key값이 입력된 key보다 크거나 같다면
		if(n->key >= key) {
			 
			// n이 head의 first와 같다면
			if(n == h->first) {
				// 처음에 삽입하고
				insertFirst(h, key);
			} else { // head와 다르다면
				// node의 rlink에 n, llink에 n의llink를 넣고
				node->rlink = n;
				node->llink = n->llink;
				// n의 llink의 rlink가 node를 가리키도록 넣는다.
				n->llink->rlink = node;
			}
			return 0;
		}
		// n에 n의 rlink값을 넣는다.
		n = n->rlink;
	}

	// 마지막 노드까지 못찾았다면
	// 마지막에 key를 삽입
	insertLast(h, key);
	return 0;
}


/**
 * list의 key값을 삭제하는 함수
 */
int deleteNode(headNode* h, int key) {

	// head의 first가 비어있으면 없다는
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	// listNode형 포인터 n에 head의 first를 넣는다.
	listNode* n = h->first;

	// n이 Null이 아니면 반복
	while(n != NULL) {
		// n의 key값과 입력받은 key값이 같다면
		if(n->key == key) {
			if(n == h->first) { // n값과 head의 first가 같으면 
				// list의 첫번째 값을 삭제
				deleteFirst(h);
			} else if (n->rlink == NULL){ // n의 rlink값이 Null이라면
				// list의 마지막 값을 삭제
				deleteLast(h);
			} else { 
				// n의 llink의 rlink에 n의 rlink값을 넣고
				n->llink->rlink = n->rlink;
				// n의 rlink의 llink에 n의 llink값을 넣고
				n->rlink->llink = n->llink;
				// n의 동적할당을 해제한다.
				free(n);
			}
			return 1;
		}
		// n의 key값이 입력한 key값과 다르면 rlink로 이동한다.
		n = n->rlink;
	}

	// key가 존재하지 않으면 존재하지 않는다고 출력한다.
	printf("cannot find the node for key = %d\n", key);
	return 1;
}




/**
 * list의 key값을 list의 마지막에 삽입하는 함수
 */
int insertLast(headNode* h, int key) {

	// listNode형 포인터 node를 listNode 사이즈만큼 동적 할당 한다.
	listNode* node = (listNode*)malloc(sizeof(listNode));
	// node의 key값에 입력한 key값을 넣어주고
	node->key = key;
	// node의 rlink, llink를 Null로 초기화 한다.
	node->rlink = NULL;
	node->llink = NULL;

	// head의 first값이 Null이라면
	if (h->first == NULL)
	{
		// head의 first에 node값을 넣어준다.
		h->first = node;
		return 0;
	}

	// listNode형 포인터 n에 head의 first를 넣는다.
	listNode* n = h->first;
	// n의 rlink가 Null이 아니면 반복하며
	while(n->rlink != NULL) {
		// n의 rlink의 값을 넣는다.
		n = n->rlink;
	}
	// n의 rlink에 node를 넣고
	n->rlink = node;
	// node의 llink를 n을 가리키게 한다.
	node->llink = n;
	return 0;
}



/**
 * list의 마지막 값을 삭제하는 함수
 */
int deleteLast(headNode* h) {

	// head의 first가 Null이면 
	if (h->first == NULL)
	{
		// 삭제할게 없다고 출력
		printf("nothing to delete.\n");
		return 0;
	}

	// listNode형 포인터 n에 head의 fisrt를 넣고
	listNode* n = h->first;
	// listNode형 포인터 trail은 Null
	listNode* trail = NULL;

	// n의 rlink가 Null이라면
	if(n->rlink == NULL) {
		// head의 first를 Null값을 넣고
		h->first = NULL;
		// n을 할당 해제한다.
		free(n);
		return 0;
	}

	// n의 rlink가 Null이 아니면 반복하고
	while(n->rlink != NULL) {
		// trail에 n을 저장하고
		trail = n;
		// n은 rlink로 이동한다.
		n = n->rlink;
	}

	// trail의 rlink를 Null로 하고
	trail->rlink = NULL;
	// n을 할당 해제한다.
	free(n);

	return 0;
}



/**
 * list의 key값을 list의 첫번째에 삽입하는 함수
 */
int insertFirst(headNode* h, int key) {

	// listNode형 포인터 node를 listNode 사이즈만큼 동적 할당 한다.
	listNode* node = (listNode*)malloc(sizeof(listNode));
	// node의 key값에 입력한 key값을 넣어주고
	node->key = key;
	// node의 rlink, llink를 Null로 초기화
	node->rlink = node->llink = NULL;

	// head의 first가 Null이면
	if(h->first == NULL)
	{
		// head의 first를 node로 한다.
		h->first = node;
		return 1;
	}

	// node의 rlink를 head의 frist로 하고
	node->rlink = h->first;
	// node의 llink는 Null로 한다.
	node->llink = NULL;

	// listNode형 포인터 p에 head의 first를 넣고
	listNode *p = h->first;
	// p의 llink에 node를 넣고
	p->llink = node;
	// head의 first에 node를 넣는다.
	h->first = node;

	return 0;
}

/**
 * list의 첫번째를 삭제하는 함수
 */
int deleteFirst(headNode* h) {

	// head의 first가 Null값이면
	if (h->first == NULL)
	{
		// 삭제할게 없다고 출력
		printf("nothing to delete.\n");
		return 0;
	}
	// listNode형 포인터 n에 head의 first를 넣고
	listNode* n = h->first;
	// head의 first에 n의 rlink를 넣는다.
	h->first = n->rlink;

	// n의 할당을 해제한다.
	free(n);

	return 0;
}



/**
 * list를 역순으로 바꾸는 함수
 */
int invertList(headNode* h) {

	// head의 first가 Null이면
	if(h->first == NULL) {
		// 역순으로 바꿀게 없다고 출력
		printf("nothing to invert...\n");
		return 0;
	}
	// listNode형 포인터 n에 head의 first를 넣고
	listNode *n = h->first;
	// listNode형 포인터 trail, middle에 Null값을 넣는다.
	listNode *trail = NULL;
	listNode *middle = NULL;

	// n이 Null이 아니면 반복하고
	while(n != NULL){
		// trail에 middle값을 넣고
		trail = middle;
		// middle에 n값을 넣는다.
		middle = n;
		// n은 rlink로 이동하고
		n = n->rlink;
		// middle의 rlink를 trail로 하고
		middle->rlink = trail;
		// middle의 llink를 n으로 한다.
		middle->llink = n;
	}

	// head의 first를 middle로 연결한다.
	h->first = middle;

	return 0;
}




