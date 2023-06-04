/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>


// node에 대한 구조체
typedef struct node {
    // node 키와
	int key;
    // node형의 포인터 left, right
	struct node *left;
	struct node *right;
} Node;

/* for stack */
// stack의 max size를 지정
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
// top을 -1로 초기화
int top = -1;

// 노드형의 pop, push 하는 함수 지정
Node* pop();
void push(Node* aNode);

/* for queue */
// queue의 사이즈 지정
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
// queue의 front와 rear를 -1로 초기화
int front = -1;
int rear = -1;



int initializeBST(Node** h);
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');
    printf("[----- [한상준] [2017018024] -----]");
	return 1;
}

// tree를 초기화 하는 함수
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
        // head가 비어있지 않으면 free
		freeBST(*h);

	/* create a head node */
    // tree의 head를 Node사이즈 만큼 동적 할당
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;
    // top과 front, rear를 초기화
	front = rear = -1;

	return 1;
}


// tree를 Inorder를 recursive하게 하는 함수
void recursiveInorder(Node* ptr)
{

	if(ptr) {
        // ptr의 왼쪽을 탐색후
		recursiveInorder(ptr->left);
        // 왼쪽이 끝나면 출력
		printf(" [%d] ", ptr->key);
        // 오른쪽으로 탐색
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
// Inorder를 iterative하게 하는 함수
void iterativeInorder(Node* node)
{
	for(;;)
	{
        // node의 left가 있으면 반복
		for(; node; node = node->left)
            // 해당 노드를 stack에 push
			push(node);
        // 왼쪽이 없으면 pop
		node = pop();

        // node가 없으면 break
		if(!node) break;
        // node의 key값을 출력
		printf(" [%d] ", node->key);
        // node의 왼쪽으로 이동
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
// levelOrder를 하는 함수
void levelOrder(Node* ptr)
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */
    // ptr을 queue에 넣고
	enQueue(ptr);

	for(;;)
	{
        // queue의 값을 가져와서
		ptr = deQueue();
		if(ptr) {
            // 출력하고
			printf(" [%d] ", ptr->key);
            // 왼쪽이 있으면 왼쪽으로 이동
			if(ptr->left)
				enQueue(ptr->left);
            // 오른쪽이 있으면 오른쪽으로 이동
			if(ptr->right)
				enQueue(ptr->right);
		}
		else
            // ptr이 존재하지 않으면 종료
			break;

	}

}

// tree에 key를 삽입 함수
int insert(Node* head, int key)
{
    // Node형 newNode에 Node사이즈 만큼 동적 할당
	Node* newNode = (Node*)malloc(sizeof(Node));
    // newNode의 값을 지정
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
        // head의 left가 비어있으면 left에 값을 넣고 return
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

// tree의 node를 삭제하는 함수
int deleteNode(Node* head, int key)
{
    // head가 없으면 바로 반환
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}
    // head의 왼쪽이 없어도 바로 반환
	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left;



	Node* parent = NULL;
	Node* ptr = root;

    // ptr이 비거나 ket값이 같을때까지 반복
	while((ptr != NULL)&&(ptr->key != key)) {
        //ptr의 key가 삭제할 key와 다르다면
		if(ptr->key != key) {

			parent = ptr;	/* save the parent */
            // key값이 ptr의 key보다 크면 왼쪽 작으면 오른쪽으로 ptr이 이동
			if(ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	/* there is no node for the key */
    // ptr이 Null이면 해당 키값이 없음 바로 return
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
    // 삭제할 ptr의 left와 right가 비어있다면
	if(ptr->left == NULL && ptr->right == NULL)
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
            // parent의 왼쪽이 ptr이라면 왼쪽을 NULL
			if(parent->left == ptr)
				parent->left = NULL;
            // 오른쪽이라면 오른쪽을 NULL
			else
				parent->right = NULL;
		} else {
            // 아니라면 head의 왼쪽을 NULL
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;

		}
        // ptr을 free하고 반환
		free(ptr);
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
    // child가 하나 있으면
	if ((ptr->left == NULL || ptr->right == NULL))
	{
		Node* child;
        // ptr의 빈쪽을 child로 하고
		if (ptr->left != NULL)
			child = ptr->left;
		else
			child = ptr->right;

        // parent가 NULL이 아니면
		if(parent != NULL)
		{
            // parent의 왼쪽이 ptr이면 왼쪽을 child로 반대면 right를 child로
			if(parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
            // parent가 비어있으면 root를 child로
			root = child;
		}
        // ptr을 free하고 반환
		free(ptr);
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;
    // candidate를 free하고 반환
	free(candidate);
	return 1;
}

// Node를 free하는 함수
void freeNode(Node* ptr)
{
    // ptr이 있으면
	if(ptr) {
        // 노드와 오른쪽 왼족을 free한다.
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

// BST를 free하는 함수
int freeBST(Node* head)
{
    // head가 왼쪽이 head면 바로 free하고 종료
	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;
    // head의 왼쪽을 freeNode하고
	freeNode(p);
    // head도 free한다.
	free(head);
	return 1;
}


// pop하는 함수
Node* pop()
{
    //top이 0보다 작으면 비어있으므로 바로 반환
	if (top < 0) return NULL;
    // 아니면 stack의 top보다 -1을 반환
	return stack[top--];
}

// stack에 push하는 함수
void push(Node* aNode)
{
    // stack의 다음 인덱스에 push
	stack[++top] = aNode;
}

// stack을 출력하는 함수
void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
    // i가 top보다 같거나 커질때까지 반복하면서
	while(i <= top)
	{
        // stack의 key값을 출력
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}

// queue의 값을 삭제하는 함수
Node* deQueue()
{
    // front와 rear가 같으면 종료
	if (front == rear) {
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}
    // front 다음 인덱스를 front로 하고
	front = (front + 1) % MAX_QUEUE_SIZE;
    // queue의 front를 반환
	return queue[front];

}

// queue에 넣는 함수
void enQueue(Node* aNode)
{
    // rear를 + 1
	rear = (rear + 1) % MAX_QUEUE_SIZE;
    // front와 rear가 같다면 종료
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}
    // queue의 rear에 값을 넣는다.
	queue[rear] = aNode;
}




