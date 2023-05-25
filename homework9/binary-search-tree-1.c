/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

// node 구조체 선언
typedef struct node {
    // node의 키
	int key;
    // node의 leftchild와 rightchild
	struct node *left;
	struct node *right;
} Node;

// tree를 초기화하는 함수
int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
    // Node형 포인터 head, ptr을 NULL로 초기화
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
            // ptr이 NULL이 아니면
			if(ptr != NULL)
                // 해당 node의 key값과 node를 반환
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
            // NULL이면 해당값이 없다고 반환
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
            // ptr이 NULL이 아니면
			if(ptr != NULL)
            // 해당 node의 key값과 node를 반환
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
            // NULL이면 해당값이 없다고 반환
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
		freeBST(*h);

	/* create a head node Node사이즈 만큼 동적 메모리 할당 */
	*h = (Node*)malloc(sizeof(Node));
    // head의 left는 NULL
	(*h)->left = NULL;	/* root */
    // right는 *h을 가리키고
	(*h)->right = *h;
    // 키값은 -9999로 초기화한다.
	(*h)->key = -9999;
	return 1;
}


// 트리를 inorder 순회하는 함수
void inorderTraversal(Node* ptr)
{
    // ptr이 NULL이 아니면
	if(ptr) {
        // ptr의 left로 쭉 이동 하고
		inorderTraversal(ptr->left);
        // left가 끝나면 출력하고
		printf(" [%d] ", ptr->key);
        // right로 이동 한다 right의 left,right가 없으면 이를 출력하고 전의 재귀함수로 반환.
		inorderTraversal(ptr->right);
	}
}

// 트리를 preorder 순회하는 함수
void preorderTraversal(Node* ptr)
{
    // ptr이 NULL이 아니면
	if(ptr) {
        // 현재 key값을 먼저 출력하고
		printf(" [%d] ", ptr->key);
        // left로 이동한다.
		preorderTraversal(ptr->left);
        // left가 없으면 right로 이동 right도 없으면 전의 재귀함수로 반환
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
    // ptr이 NULL이 아니면
	if(ptr) {
        // left로 이동하다가 
		postorderTraversal(ptr->left);
        // left가 없으면 right로 이동
		postorderTraversal(ptr->right);
        // 최종적으로 이동 불가하면 출력하고 전의 재귀함수로 반환
		printf(" [%d] ", ptr->key);
	}
}

// tree에 key를 입력하는 함수
int insert(Node* head, int key)
{
    // Node형 포인터 newNode에 Node사이즈 만크 동적 메모리 할당한다.
	Node* newNode = (Node*)malloc(sizeof(Node));
    // key는 key값을 넣고 left, right는 NULL로 초기화
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

    // head의 left가 NULL이면
	if (head->left == NULL) {
        // head의 left에 newNode를 넣고 1을 반환
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
    // ptr을 head의 left를 가리키게 한다.
	Node* ptr = head->left;

    // 부모노드는 NULL로 하고
	Node* parentNode = NULL;
    // ptr이 NULL이 아니면
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
        // ptr->key가 key랑 같다면 바로 return
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
        // 부모노드를 ptr로 하고
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
        // ptr의 key보다 key값이 크면
		if(ptr->key < key)
            // ptr의 right로
			ptr = ptr->right;
		else
            // key가 더 작으면 ptr의 left로
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
    // parendNode의 key값이 key보다 크면
	if(parentNode->key > key)
        // parentNode의 left는 newNode
		parentNode->left = newNode;
	else
        // 작다면 right가 newNode
		parentNode->right = newNode;
	return 1;
} 

// leafNode를 삭제하는 함수
int deleteLeafNode(Node* head, int key)
{
    // head가 NULL이라면
	if (head == NULL) {
        // 삭제할게 없다고 출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

    // head의 left가 NULL이면 역시
	if (head->left == NULL) {
        // 삭제할게 없다고 출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
    // Node형 포인터 ptr에 head의 left을 넣고
    Node* ptr = head->left;


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
    // Node형 포인터 parentNode를 head로 한다.
	Node* parentNode = head;

    // ptr이 NULL이 아니면
	while(ptr != NULL) {

        // ptr의 key가 key라면
		if(ptr->key == key) {
            // ptr의 left가 NULL이고 ptr의 right가 NULL이면
			if(ptr->left == NULL && ptr->right == NULL) {
                
				/* root node case */
                // parentNode가 head면
                if(parentNode == head)
                    // head의 left룰 NULL로 한다.
					head->left = NULL;

				/* left node case or right case*/
                // parentNode의 left가 ptr이면
				if(parentNode->left == ptr)
                    // left를 NULL로
					parentNode->left = NULL;
				else
                    // 다르면 right를 NULL로한다.
					parentNode->right = NULL;
                // ptr을 할당 해제한다.
				free(ptr);
			}
			else {
                // 하나라도 있다면 해당 노드가 leafnode가 아니라고 출력
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
        // parentNode를 ptr로
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
        // prt의 key가 key보다 작다면
		if(ptr->key < key)
            // ptr를 ptr의 right로 이동
			ptr = ptr->right;
		else
            // 더 크면 ptr의 left로 이동
			ptr = ptr->left;


	}
    
    // 못 찾으면 못찾았다고 출력
	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

// recursive방식으로 탐색
Node* searchRecursive(Node* ptr, int key)
{
    // ptr이 NULL이면
	if(ptr == NULL)
        // NULL을 반환
		return NULL;

    // ptr의 key가 key값보다 작으면
	if(ptr->key < key)
        // ptr을 right로 보내고 recursive한다.
		ptr = searchRecursive(ptr->right, key);
    // ptr의 key가 더 크다면
	else if(ptr->key > key)
        // ptr의 left로 recursive한다.
		ptr = searchRecursive(ptr->left, key);

	/* if ptr->key == key */
    // key값이 같으면 goekd ptr을 반환
	return ptr;

}

// Iterative방식으로 탐색
Node* searchIterative(Node* head, int key)
{
	/* root node */
    // Node형 포인터 ptr를 head의 left로
	Node* ptr = head->left;

    // ptr이 NULL이 아니면
	while(ptr != NULL)
	{   
        // ptr의 key값과 key가 같으면 
		if(ptr->key == key)
            // ptr 반환
			return ptr;

        // ptr의 key보다 key가 크면 ptr을 right로 이동
		if(ptr->key < key) ptr = ptr->right;
		// ptr의 key가 더 크면
        else// left로 이동
			ptr = ptr->left;
	}

    // 못팢으면 NULLL을 반환
	return NULL;
}

// Node의 할당을 해제하는 함수
void freeNode(Node* ptr)
{
    // ptr이 존재하면
	if(ptr) {
        // ptr의 left와 right 그리고 ptr자신을 할당 해제
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

// BST를 할당 해제하는 함수
int freeBST(Node* head)
{

    // head의 left가 head면
	if(head->left == head)
	{
        // head를 할당해제 하고 종료
		free(head);
		return 1;
	}

    // Node형 포인터 p가 head의 left를 가리키고
	Node* p = head->left;

    // p의 Node를 할당해제한다.
	freeNode(p);

    // 그리고 head를 할당 해제한다.
	free(head);
	return 1;
}




