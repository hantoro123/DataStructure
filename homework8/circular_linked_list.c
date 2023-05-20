/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>

// 구조체 Node로
typedef struct Node {
	// int형의 key값을 받고
    int key;
    // 구조체 Node형의 포인터 llink, rlink생성
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 선언 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
    // command와 key값
	char command;
	int key;
    // listNode형 포인터 headnode를 NULL값으로 초기화
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

        // command를 입력받고
		printf("Command = ");
		scanf(" %c", &command);

        // 각 case의 함수 실행
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

    // command가 q이면 빠져 나간다.
	}while(command != 'q' && command != 'Q');

    printf("[----- [한상준] [2017018024] -----]");
	return 1;
}


// list를 초기화 하는 함수
int initialize(listNode** h) {

	/* headNode가 NULL값이 아니라면 headNode를 free해준다. */
	if(*h != NULL)
		freeList(*h);

	/* headNode를 listNode크기 만큼 동적 메모리 할당을 한다. */
	*h = (listNode*)malloc(sizeof(listNode));
    // h의 rlink, llink를 h에 연결한다.
	(*h)->rlink = *h;
	(*h)->llink = *h;
    // key값은 -9999로 초기화
	(*h)->key = -9999;

	return 1;
}

/* list를 할당 해제하는 함수 */
int freeList(listNode* h){
    // h의 rlink가 h면 head만 있다
    if(h->rlink == h){
        // 따라서 h만 할당 해제해주고 return
        free(h);
        return 1;
    }

    // listNode형 포인터 p에 head의 rlink를 넣고
    listNode* p = h->rlink;
    // listNode형 포인터 prev는 NULL로 둔다.
    listNode* prev = NULL;

    // p가 NULL이거나 h이면 멈춘다.
    while(p != NULL && p != h){
        // prev가 p를 가리키고
        prev = p;
        // p를 rlink로 넘긴다.
        p = p->rlink;
        // prev를 할당 해제한다.
        free(prev);
    }

    // 최종적으로 head도 할당 해제한다.
    free(h);
	return 0;
}


// list를 출력하는 함수
void printList(listNode* h) {
    // index를 알려줄 i = 0으로 선언
	int i = 0;
    // listNode형 포인터 p
	listNode* p;

	printf("\n---PRINT\n");

    // head가 NULL이면 출력할거 없음을 출력
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

    // p가 head의 rlink로 이동
	p = h->rlink;

    // p가 NULL이거나 head이면 종료
	while(p != NULL && p != h) {
        // index와 현재 p의 key값을 출력
		printf("[ [%d]=%d ] ", i, p->key);
        // p는 다음 rlink로 이동하고 i++
		p = p->rlink;
		i++;
	}
    // 총 몇개 인지 출력
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
    // headnode의 h,rlink,llink값
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 마지막에 key값을 삽입하는 함수
 */
int insertLast(listNode* h, int key) {
    // head가 NULL이면 바로 return
    if(h == NULL) return -1;

    // listNode형 포인터 node에 listNode크기 만큼 동적 메모리 할당을 한다.
    listNode* node = (listNode*)malloc(sizeof(listNode));
    // node의 key값에 key르 넣고
    node->key = key;
    // rlink, llink는 NULL로 초기화
    node->rlink = NULL;
    node->llink = NULL;

    // h의 rlink가 h면
    if (h->rlink == h){
        // head의 rlink, llink를 node로 하고
        h->rlink = node;
        h->llink = node;
        // node의 rlink, llink에 h를 넣는다.
        node->rlink = h;
        node->llink = h;
    }else{ // 그 외에는
        // h의 llink에rlink를 node로 하고 
        h->llink->rlink = node;
        // node의 llink를 h의 llink로
        node->llink = h->llink;
        // h의 llink를 node
        h->llink = node;
        // node의 rlink를 h를 가리키게 한다.
        node->rlink = h;
    }

    // 끝났으면 1을 반환
	return 1;
}


/**
 * list의 마지막을 삭제하는 함수
 */
int deleteLast(listNode* h) {
    // h가 NULL이거나 llink가 h라면 삭제할게 없다고 출력
    if (h == NULL || h->llink == h){
        printf("nothing to delete.\n");
        return 1;
    }

    // listNode형의 포인터 nodetoremove에 h의 llink를 넣는다.
    listNode* nodetoremove = h->llink;

    // nodetoremove의 llink에rlink를 h로
    nodetoremove->llink->rlink = h;
    // h의 llink는 nodetoremove의 llink를 가리킨다.
    h->llink = nodetoremove->llink;

    // nodetoremove는 할당 해제
    free(nodetoremove);

	return 1;
}


/**
 * list의 첫번째 부분에 삽입하는 함수
 */
int insertFirst(listNode* h, int key) {

    // listNode형 포인터 node에 listNode사이즈 만큼 동적 메모리 할당
    listNode* node = (listNode*)malloc(sizeof(listNode));
    // node의 key는 key고 rlink, llink는 NULL로 초기화
    node->key = key;
    node->rlink = NULL;
    node->llink = NULL;

    // node의 rlink는 h의 rlink로
    node->rlink = h->rlink;
    // h의 rlink에llink는 node로
    h->rlink->llink = node;
    // node의 llink는 h로
    node->llink = h;
    // h의 rlink는 node를 가리킨다.
    h->rlink = node;

	return 1;
}

/**
 * list의 첫번째 부분을 삭제하는 함수
 */
int deleteFirst(listNode* h) {
    // h가 NULL이거나 rlink가 h이면 삭제할게 없다고 출력
    if(h == NULL || h->rlink == h){
        printf("nothing to delete.\n");
        return 0;
    }

    // listNode형 포인터 nodetoremove에 h의 rlink를 넣는다.
    listNode* nodetoremove = h->rlink;

    // nodetoremove의 rlink에 llink를 h로
    nodetoremove->rlink->llink = h;
    // h의 rlink는 nodetoremove의 rlink를 가리킨다.
    h->rlink = nodetoremove->rlink;

    // nodetoremove는 할당 해제한다.
    free(nodetoremove);

	return 1;

}


/**
 * list를 역순으로 만드는 함수
 */
int invertList(listNode* h) {
    // h가 rlink가 h거나 NULL이면 역순할게 없다고 출력
    if(h->rlink == h || h==NULL){
        printf("nothing to invert.\n");
        return 0;
    }
    // listNode형 포인터 n은 h의 rlink을 넣고 trail, middle은 h를 넣는다.
    listNode* n = h->rlink;
    listNode* trail = h;
    listNode* middle = h;

    // h의 llink는 h의 rlink를 가리킨다.
    h->llink = h->rlink;

    // n이 NULL이거나 h랑 같으면 멈춘다.
    while (n != NULL && n != h){
        // trail은 middle을 넣고
        trail = middle;
        // middle은 n을 넣고
        middle = n;
        // n은 n의 rlink로 이동
        n = n->rlink;
        // middle의 rlink는 trail
        middle->rlink = trail;
        // middle의 llink는 n을 가리킨다.
        middle->llink = n;
    }
    // h의 rlink는 middle을 가리킨다.
    h->rlink = middle;

	return 0;
}



/* list에 key를 위치에 맞게 삽입하는 함수 */
int insertNode(listNode* h, int key) {
    // h가 NULL이면 바로 return
    if (h == NULL) return -1;

    // listNode형 포인터 node를 listNode의 크기만큼 동적 메모리 할당
    listNode* node = (listNode*)malloc(sizeof(listNode));
    // node의 key는 key값 llink, rlink는 NULL로 한다.
    node->key = key;
    node->llink = node->rlink = NULL;

    // h의 rllink가 h면 첫번째에 바로 key를 삽입한다.
    if(h->rlink = h){
        insertFirst(h, key);
        return 1;
    }

    // listNode형 포인터 n에 h의 rlink를 넣고
    listNode* n = h->rlink;

    // n이 NULL이거나 h가 되면 멈춘다.
    while (n != NULL && n != h){
        // n의 key가 node의 key값보다 크거나 같아지면
        if (n->key >= key){
            // n이 h의 rlink라면
            if (n == h->rlink){
                // 첫번째에 삽입한다.
                insertFirst(h, key);
            }else {// 그 외에 라면
                // node의 rlink는 n, llink는 n의 llink를 가리키고
                node->rlink = n;
                node->llink = n->llink;
                // n의 llink에 rlink를 node, n의 llink도 node를 카리킨다.
                n->llink->rlink = node;
                n->llink = node;
            }
            return 0;
        }
        // key가 n의 key보다 작으면 n을 rlink로 이동
        n = n->rlink;
    }
    // 끝까지 key값이 n의 key값보다 크면 마지막에 삽입
    insertLast(h, key);
	return 0;
}


/**
 * list에 key값을 삭제하는 함수
 */
int deleteNode(listNode* h, int key) {
    // h의 rlink가 h거나 NULL이면 삭제할게 없다고 출력
    if (h->rlink == h || h == NULL){
        printf("nothing to delete\n");
        return 0;
    }

    // listNode형 포인터 n에 h의 rlink를 넣는다.
    listNode* n = h->rlink;

    // n이 NULL이거나 h이면 멈춘다.
    while (n != NULL && n != h){
        // n의 key값과 삭제할 key값이 같을때
        if (n->key == key){
            // n이 h의 rlink면
            if (n == h->rlink){
                // 첫번째를 삭제
                deleteFirst(h);
                // n의 rlink가 h면 
            } else if (n->rlink == h){
                // 마지막을 삭제
                deleteLast(h);
            } else { // 그 외에는
                // n의 llink에 rlink를 n의 rlink로
                n->llink->rlink = n->rlink;
                // n의 rlink에 llink는 n의 llink를 가리킨다
                n->rlink->llink = n->llink;
                // n은 할당 해제해준다.
                free(n);
            }
            return 0;
        }
        // key값과 다르면 n을 rlink로 이동
        n = n->rlink;
    }
    // 끝까지 못찾으면 key값을 못찾았다고 출력
    printf("cannot find the node for key = %d\n", key);
	return 0;
}

