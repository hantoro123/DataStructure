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
/* �꾩슂�� �ㅻ뜑�뚯씪 異붽� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �⑥닔 由ъ뒪�� */
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
	char command;
	int key;
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

		printf("Command = ");
		scanf(" %c", &command);

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

	return 1;
}


int initialize(listNode** h) {

	/* headNode媛� NULL�� �꾨땲硫�, freeNode瑜� �몄텧�섏뿬 �좊떦�� 硫붾え由� 紐⑤몢 �댁젣 */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� 硫붾え由щ� �좊떦�섏뿬 由ы꽩 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 硫붾え由� �댁젣 */
int freeList(listNode* h){
    if(h->rlink == h){
        free(h);
        return 1;
    }

    listNode* p = h->rlink;
    listNode* prev = NULL;

    while(p != NULL && p != h){
        prev = p;
        p = p->rlink;
        free(prev);
    }

    free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
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
 * list�� key�� ���� �몃뱶�섎굹瑜� 異붽�
 */
int insertLast(listNode* h, int key) {
    if(h == NULL) return -1;

    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->rlink = NULL;
    node->llink = NULL;

    if (h->rlink == h){
        h->rlink = node;
        h->llink = node;
        node->rlink = h;
        node->llink = h;
    }else{
        h->llink->rlink = node;
        node->llink = h->llink;
        h->llink = node;
        node->rlink = h;
    }

	return 1;
}


/**
 * list�� 留덉�留� �몃뱶 ��젣
 */
int deleteLast(listNode* h) {
    if (h == NULL || h->llink == h){
        printf("nothing to delete.\n");
        return 1;
    }

    listNode* nodetoremove = h->llink;

    nodetoremove->llink->rlink = h;
    h->llink = nodetoremove->llink;

    free(nodetoremove);

	return 1;
}


/**
 * list 泥섏쓬�� key�� ���� �몃뱶�섎굹瑜� 異붽�
 */
int insertFirst(listNode* h, int key) {

    listNode* node = (listNode*)mallco(sizeof(listNode));
    node->key = key;
    node->rlink = NULL;
    node->llink = NULL;

    node->rlink = h->rlink;
    h->rlink->llink = node;
    node->llink = h;
    h->rlink = node;

	return 1;
}

/**
 * list�� 泥ル쾲吏� �몃뱶 ��젣
 */
int deleteFirst(listNode* h) {

    if(h == NULL || h->rlink == h){
        printf("nothing to delete.\n");
        return 0;
    }

    listNode* nodetoremove = h->rlink;

    nodetoremove->rlink->llink = h;
    h->rlink = nodetoremove->rlink;

    free(nodetoremove);

	return 1;

}


/**
 * 由ъ뒪�몄쓽 留곹겕瑜� ��닚�쇰줈 �� 諛곗튂
 */
int invertList(listNode* h) {

    if(h->rlink == h || h==NULL){
        printf("nothing to invert.\n");
        return 0;
    }
    listNode* n = h->rlink;
    listNode* trail = h;
    listNode* middle = h;

    h->llink = h->rlink;

    while (n != NULL && n != h){
        trail = middle;
        middle = n;
        n = n->rlink;
        middle->rlink = trail;
        middle->llink = n;
    }
    
    h->rlink = middle;

	return 0;
}



/* 由ъ뒪�몃� 寃��됲븯��, �낅젰諛쏆� key蹂대떎 �곌컪�� �섏삤�� �몃뱶 諛붾줈 �욎뿉 �쎌엯 */
int insertNode(listNode* h, int key) {

    if (h == NULL) return -1;

    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->llink = node->rlink = NULL;

    if(h->rlink = h){
        insertFirst(h, key);
        return 1;
    }

    listNode* n = h->rlink;

    while (n != NULL && n != h){
        if (n->key >= key){
            if (n == h->rlink){
                insertFirst(h, key);
            }else {
                node->rlink = n;
                node->llink = n->llink;
                n->llink->rlink;
                n->llink = node;
            }
            return 0;
        }
        n = n->rlink;
    }

    insertLast(h, key);
	return 0;
}


/**
 * list�먯꽌 key�� ���� �몃뱶 ��젣
 */
int deleteNode(listNode* h, int key) {

    if (h->rlink == h || h == NULL){
        printf("nothing to delete\n");
        return 0;
    }

    listNode* n = h->rlink;

    while (n != NULL && n != h){
        if (n->key == key){
            if (n == h->rlink){
                deleteFirst(h);
            } else if (n->rlink == h){
                deleteLast(h);
            } else {
                n->llink->rlink = n->rlink;
                n->rlink->llink = n->llink;
                free(n);
            }
            return 0;
        }
        n = n->rlink;
    }

    printf("cannot find the node for key = %d\n", key);
	return 0;
}

