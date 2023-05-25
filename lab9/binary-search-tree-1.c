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

typedef struct node
{ // 정수형 key값, 왼쪽, 오른쪽 자식노드를 갖는 구조체 선언
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node **h); // 이진탐색트리 초기화하는 함수

/* functions that you have to implement */
void inorderTraversal(Node *ptr);			/* recursive inorder traversal */
void preorderTraversal(Node *ptr);			/* recursive preorder traversal */
void postorderTraversal(Node *ptr);			/* recursive postorder traversal */
int insert(Node *head, int key);			/* insert a node to the tree */
int deleteLeafNode(Node *head, int key);	/* delete the leaf node for the key */
Node *searchRecursive(Node *ptr, int key);	/* search the node for the key */
Node *searchIterative(Node *head, int key); /* search the node for the key */
int freeBST(Node *head);					/* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
	char command;	   // 명령 입력받을 변수
	int key;		   // key 값 입력받을 변수
	Node *head = NULL; // 초기 node로 사용
	Node *ptr = NULL;  /* temp */

	do
	{
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

		printf("Command = "); // 명령 입력받음
		scanf(" %c", &command);

		switch (command)
		{ // z 입력시 이진탐색트리 초기화
		case 'z':
		case 'Z':
			initializeBST(&head);
			break;
		case 'q':
		case 'Q': // q 입력시 메모리 해제 및 반복문 종료
			freeBST(head);
			break;
		case 'n':
		case 'N': // n입력시 key값 입력받고 트리에 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd':
		case 'D': // d 입력시 리프노드 중 key값 일치하는 노드 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f':
		case 'F': // f 입력시 key값 입력받고 searchIterative 함수로 노드 검색
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's':
		case 'S': // s 입력시 key값 입력받고 searchRecursive 함수로 노드 검색
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': // i 입력시 중위순회 방식으로 트리 출력
		case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': // p 입력시 전위순회 방식으로 트리 출력
		case 'P':
			preorderTraversal(head->left);
			break;
		case 't': // t 입력시 후위순회 방식으로 트리 출력
		case 'T':
			postorderTraversal(head->left);
			break;
		default: // 그 외 입력시 안내문 출력후 다시 입력받음
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q'); /// q 입력받으면 반복문 종료 후 반환 후 프로그램 종료

	return 1;
}

int initializeBST(Node **h) // BST 초기화하는 함수
{

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL) // freeBST 함수를 통해 기존 tree를 없앰
		freeBST(*h);

	/* create a head node */
	*h = (Node *)malloc(sizeof(Node)); // 새로운 root node 생성 및 메모리 동적할당
	(*h)->left = NULL;				   /* root node에 맞게 초기화 후 반환 후 함수 종료*/
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node *ptr) // 중위순회 함수
{
	if (ptr) // 존재하는 경우만 실행
	{
		inorderTraversal(ptr->left);  // 재귀적으로 실행됨, 왼쪽 자식노드를 기준으로 중위순회 후
		printf(" [%d] ", ptr->key);	  // 자기자신의 key값을 출력 후
		inorderTraversal(ptr->right); // 오른쪽 자식노드를 기준으로 중위 순회
	}
}

void preorderTraversal(Node *ptr) // 전위순회 함수
{
	if (ptr) // 존재하는 경우만 실행
	{
		printf(" [%d] ", ptr->key);	   // 재귀적으로 실행됨, 자기자신의 key값을 출력 후
		preorderTraversal(ptr->left);  // 왼쪽 자식노드를 기준으로 중위순회 후
		preorderTraversal(ptr->right); // 오른쪽 자식노드를 기준으로 중위 순회
	}
}

void postorderTraversal(Node *ptr) // 후위순회 함수
{
	if (ptr) // 존재하는 경우만 실행
	{
		postorderTraversal(ptr->left);	// 재귀적으로 실행됨, 왼쪽 자식노드를 기준으로 중위순회 후
		postorderTraversal(ptr->right); // 오른쪽 자식노드를 기준으로 중위 순회 후
		printf(" [%d] ", ptr->key);		// 자기자신의 key값을 출력
	}
}

int insert(Node *head, int key) // tree에 node 삽입하는 함수
{
	Node *newNode = (Node *)malloc(sizeof(Node)); // 새로운 node 선언 및 동적 할당
	newNode->key = key;							  // key값 저장
	newNode->left = NULL;						  // 자식 node는 null로 초기화
	newNode->right = NULL;

	if (head->left == NULL) // headnode가 유일한 노드일 경우
	{
		head->left = newNode; // 새 노드는 headnode의 왼쪽 자식
		return 1;			  // 반환 후 함수 종료
	}

	/* head->left is the root */
	Node *ptr = head->left; // headnode의 왼쪽 자식은 root node

	Node *parentNode = NULL; // 부모노드 역할을 할 포인터 node 선언
	while (ptr != NULL)		 // ptr이 null이 되기 전까지 반복
	{

		/* if there is a node for the key, then just return */
		if (ptr->key == key) // 중복되는 값이 이미 있다면 반환 후 함수 종료
			return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; // 기존 ptr 노드를 부모노드가 되도록 함

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)	  //  현재 위치의 key가 입력받은 key보다 작다면
			ptr = ptr->right; // ptr의 오른쪽 자식노드로 이동해 다시 탐색
		else				  //  현재 위치의 key가 입력받은 key보다 크다면
			ptr = ptr->left;  // ptr의 왼쪽 자식노드로 이동해 다시 탐색
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)		 // 마지막 노드의 key값이 입력받은 key값보다 크다면
		parentNode->left = newNode;	 // 입력받은 key값을 가진 노드는 마지막 노드의 왼쪽 자식이 됨
	else							 // 마지막 노드의 key값이 입력받은 key값보다 작다면
		parentNode->right = newNode; // 입력받은 key값을 가진 노드는 마지막 노드의 오른쪽 자식이 됨
	return 1;						 // 반환 후 함수 종료
}

int deleteLeafNode(Node *head, int key) // 리프노드 삭제하는 함수
{
	if (head == NULL) // headnode null이면 안내문 출력 후 반환 후 함수 종료
	{
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) // root node가 없으면 안내문 출력 후 반환 후 함수 종료
	{
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node *ptr = head->left; // 자식노드 역할을 할 포인터 노드 선언 후 root node로 초기화

	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node *parentNode = head; // 부모노드 역할을 할 포인터 node 선언 후 headnode로 초기화

	while (ptr != NULL) // 자식노드가 null이 되기 전까지
	{

		if (ptr->key == key) // 입력받은 key값과 노드의 key값이 일치하면
		{
			if (ptr->left == NULL && ptr->right == NULL) // 만약 딩크족이라면
			{

				/* root node case */
				if (parentNode == head) // 부모노드가 head node 라면, 즉 자기자신이 rootnode라면
					head->left = NULL;	// headnode가 자신을 가리키지 않도록 함

				/* left node case or right case*/
				if (parentNode->left == ptr)  // 자신이 부모노드의 왼쪽자식이라면
					parentNode->left = NULL;  // 호적에서 팜
				else						  // 자신이 부모노드의 오른쪽자식이라면
					parentNode->right = NULL; // 부모노드가 오른쪽 자식노드를 null로 바꿈

				free(ptr); // 자기 자신을 메모리 해제함
			}
			else // 만약 자식이 있다면
			{
				printf("the node [%d] is not a leaf \n", ptr->key); // 리프노드가 아니라고 안내문 출력
			}
			return 1; // 반환 후 함수 종료
		}

		/* keep the parent node */
		parentNode = ptr; // key값이 일치하지 않으면, 자식노드를 부모노드에 대입하고

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)	  // 입력받은 key보다 자식노드의 key가 작으면
			ptr = ptr->right; // 자식노드는 기존 자기 자신의 오른쪽 자식노드가 됨
		else				  // 입력받은 key보다 자식노드의 key가 크면
			ptr = ptr->left;  // 자식노드는 기존 자기 자신의 왼쪽 자식노드가 됨
	}

	printf("Cannot find the node for key [%d]\n ", key); // 안내문 출력 후 반환 후 함수 종료

	return 1;
}

Node *searchRecursive(Node *ptr, int key) // 재귀적으로 탐색하는 함수
{
	if (ptr == NULL) // node가 null이면 null 반환 후 함수 종료
		return NULL;

	if (ptr->key < key)							// node의 key값이 입력받은 key값보다 작으면
		ptr = searchRecursive(ptr->right, key); // node의 오른쪽 자식노드를 인자로 searchRecursive 함수 실행
	else if (ptr->key > key)					// node의 key값이 입력받은 key값보다 크면
		ptr = searchRecursive(ptr->left, key);	// node의 왼쪽 자식노드를 인자로 searchRecursive 함수 실행

	/* if ptr->key == key */
	return ptr; // key값이 일치하면 주소 반환 후 함수 종료
}
Node *searchIterative(Node *head, int key) // 반복적으로 탐색하는 함수
{
	/* root node */
	Node *ptr = head->left; // rootnode부터 시작

	while (ptr != NULL) // ptr이 null이 아닌 동안
	{
		if (ptr->key == key) // key값이 일치하면 ptr 반환
			return ptr;

		if (ptr->key < key)	  // 입력받은 key값이 자신의 key값보다 크면
			ptr = ptr->right; // 오른쪽 자식노드로 이동 후 다시 반복문 실행
		else				  // 입력받은 key값이 자신의 key값보다 작으면
			ptr = ptr->left;  // 왼쪽 자식노드로 이동 후 다시 반복문 실행
	}

	return NULL; // 일치하는 key값 찾지 못한 경우 null 반환
}

void freeNode(Node *ptr) // node 메모리 해제하는 함수
{
	if (ptr)
	{
		freeNode(ptr->left); // 재귀적으로 작동함, 자식노드들에 대해서 먼저 freeNode 함수 실행 후
		freeNode(ptr->right);
		free(ptr); // 마지막으로 자기 자신을 메모리 해제
	}
}

int freeBST(Node *head) // BST의 메모리를 해제하는 함수
{

	if (head->left == head) // 노드가 자기 자신밖에 없을 때
	{
		free(head); // 메모리 해제 후 반환 후 함수 종료
		return 1;
	}

	Node *p = head->left; // head 노드의 왼쪽 자식노드를

	freeNode(p); // freeNode 함수로 메모리 해제, 이를 통해 자기자신만 남음

	free(head); // 마지막으로 head 메모리 해제 후 반환 후 함수 종료
	return 1;
}
