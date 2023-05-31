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

typedef struct node
{ // 정수형 key값, 왼쪽, 오른쪽 자식노드를 갖는 구조체 선언
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE 20	 // 최대 스택 크기 정의
Node *stack[MAX_STACK_SIZE]; // 노드 스택 선언
int top = -1;				 // 스택 내 위치 변수 선언 및 초기화

Node *pop();			// stack에 pop하는 함수
void push(Node *aNode); // stack에 push하는 함수

/* for queue */
#define MAX_QUEUE_SIZE 20	 // 최대 큐 크기 정의
Node *queue[MAX_QUEUE_SIZE]; // 노드 큐 선언
int front = -1;				 // 큐 내 처음 위치 변수 선언 및 초기화
int rear = -1;				 // 큐 내 끝 위치 변수 선언 및 초기화

int initializeBST(Node **h);	  // 이진탐색트리 초기화하는 함수
void recursiveInorder(Node *ptr); /* recursive inorder traversal */
int insert(Node *head, int key);  /* insert a node to the tree */
int freeBST(Node *head);		  /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node *ptr);	 /* iterative inorder traversal */
void levelOrder(Node *ptr);			 /* level order traversal */
int deleteNode(Node *head, int key); /* delete the node for the key */
Node *pop();						 // stack에 pop하는 함수
void push(Node *aNode);				 // stack에 push하는 함수
Node *deQueue();					 // queue에서 원소 제거하는 함수
void enQueue(Node *aNode);			 // aueue에 원소 추가하는 함수

/* you may add your own defined functions if necessary */

void printStack(); // stack 출력하는 함수

int main()
{
	char command;	   // 명령 입력받을 변수
	int key;		   // key 값 입력받을 변수
	Node *head = NULL; // 초기 node로 사용

	do
	{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
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
		case 'i':
		case 'I': // i입력시 key값 입력받고 트리에 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd':
		case 'D': // d 입력시 리프노드 중 key값 일치하는 노드 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r':
		case 'R': // r 입력시 중위순회, 재귀 방식으로 트리 출력
			recursiveInorder(head->left);
			break;
		case 't':
		case 'T': // t 입력시 중위순회, 반복 방식으로 트리 출력
			iterativeInorder(head->left);
			break;

		case 'l':
		case 'L': // l 입력시 레벨 순서 순회
			levelOrder(head->left);
			break;

		case 'p':
		case 'P': // p 입력시 stack 출력
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q'); // q 입력받으면 반복문 종료

	return 1;
}

int initializeBST(Node **h)
{

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL) // freeBST 함수를 통해 기존 tree를 없앰
		freeBST(*h);

	/* create a head node */
	*h = (Node *)malloc(sizeof(Node)); // 새로운 root node 생성 및 메모리 동적할당
	(*h)->left = NULL;				   /* root node에 맞게 초기화 후 반환 후 함수 종료*/
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1; // stack의 top 위치 초기화

	front = rear = -1; // queue의 front, rear 위치 초기화

	return 1; // 반환 후 함수 종료
}

void recursiveInorder(Node *ptr)
{
	if (ptr) // 존재하는 경우만 실행
	{
		recursiveInorder(ptr->left);  // 재귀적으로 실행됨, 왼쪽 자식노드를 기준으로 중위순회 후
		printf(" [%d] ", ptr->key);	  // 자기자신의 key값을 출력 후
		recursiveInorder(ptr->right); // 오른쪽 자식노드를 기준으로 중위 순회
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node *node) // 반복적 중위 순회 함수
{
	for (;;)
	{
		for (; node; node = node->left) // 노드의 왼쪽자식으로 이동하며 반복
			push(node);					// 인자로 받은  node를 push
		node = pop();					// 마지막에 push했던 node를 pop해 node에 재저장

		if (!node) // pop할 노드 없으면 반복문 종료
			break;
		printf(" [%d] ", node->key); // node의 key값 출력

		node = node->right; // 노드의 오른쪽 자식으로 이동해 다시 반복
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node *ptr) // 레벨 단위 순회
{
	// int front = rear = -1;

	if (!ptr)	// 인자로 받은 ptr node 존재하지 않으면 반환 후 함수 종료
		return; /* empty tree */

	enQueue(ptr); // queue에 ptr 저장

	for (;;) // queue에 원소 있는 동안 반복
	{
		ptr = deQueue(); // ptr에 queue의 마지막 원소 꺼내서 저장
		if (ptr)		 // 존재하는 경우
		{
			printf(" [%d] ", ptr->key); // key 값 출력

			if (ptr->left) // ptr의 왼쪽 자식이 있는 경우 왼쪽 자식 큐에 저장
				enQueue(ptr->left);
			if (ptr->right) // 오른쪽 자식이 있는 경우 오른쪽 자식 큐에 저장
				enQueue(ptr->right);
		}
		else // queue에 원소가 없었던 경우 반복문 종료
			break;
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

int deleteNode(Node *head, int key) // 노드 삭제하는 함수
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
	Node *root = head->left; // root node

	Node *parent = NULL; // 부모 노드 역할을 할 포인터 노드 선언 후 초기화
	Node *ptr = root;	 // 순회할 노드 선언 및 root부터 시작하도록 초기화

	while ((ptr != NULL) && (ptr->key != key)) // ptr이 null이 아니고 key값이 일치하지 않는 동안 실행
	{
		if (ptr->key != key) // key값이 일치하지 않으면
		{

			parent = ptr; /* save the parent */

			if (ptr->key > key)	  // 입력받은 key보다 자식노드의 key가 크면
				ptr = ptr->left;  // 자식노드는 기존 자기 자신의 왼쪽 자식노드가 됨
			else				  // 입력받은 key보다 자식노드의 key가 작으면
				ptr = ptr->right; // 자식노드는 기존 자기 자신의 오른쪽 자식노드가 됨
		}
	}

	/* there is no node for the key */
	if (ptr == NULL) // key에 맞는 node 못찾았을 때
	{
		printf("No node for key [%d]\n ", key); // 안내문 출력 후 반환 후 함수 종료
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if (ptr->left == NULL && ptr->right == NULL) // ptr이 leaf node라면
	{
		if (parent != NULL)			  // 부모노드가 존재하는 경우
		{							  /* parent exists, parent's left and right links are adjusted */
			if (parent->left == ptr)  // ptr이 부모노드의 왼쪽 자식일 경우
				parent->left = NULL;  // null 대입
			else					  // 오른쪽 자식일 경우
				parent->right = NULL; // 오른쪽 자식 자리에 null
		}
		else // 부모노드가 존재하지 않는 경우
		{
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL; // root node이므로 head node의 왼쪽 자식을 null로 함
		}

		free(ptr); // ptr 메모리 해제
		return 1;  // 반환 후 함수 종료
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) // ptr의 자식이 하나면
	{
		Node *child;			// 자식 노드 선언, 동적 메모리 할당을 하지 않은 빈 노드임
		if (ptr->left != NULL)	// 왼쪽 자식이 존재하면
			child = ptr->left;	// child는 왼쪽 자식
		else					// 오른쪽 자식이 존재하면
			child = ptr->right; // child는 오른쪽 자식

		if (parent != NULL) // 부모가 있다면
		{
			if (parent->left == ptr)   // 만약 부모의 왼쪽 자식이 ptr이면
				parent->left = child;  // 왼쪽 자식을 child로 교체
			else					   // 오른쪽 자식이면
				parent->right = child; // 오른쪽 자식을 child로 교체
		}
		else // 부모가 없다면
		{
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; // root node를 child로 교체
		}

		free(ptr); // 기존 ptr 메모리 해제 후 반환 및 함수 종료
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

	// 자식이 둘이면
	Node *candidate; // 후보 노드 선언
	parent = ptr;	 // 부모 역할 노드에 ptr 대입

	candidate = ptr->right; // 후보 노드에 오른쪽 자식 대입

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while (candidate->left != NULL) // 왼쪽 자식이 없을 때 까지
	{
		parent = candidate;			 // 부모 노드에 후보 노드 대입
		candidate = candidate->left; // 후보 노드는 본인의 왼쪽 자식 대입
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)		  // 부모의 오른쪽 자식이 후보 노드와 같으면
		parent->right = candidate->right; // 부모의 오른쪽 자식을 후보 노드의 오른쪽 자식으로 대입
	else								  // 같지 않으면
		parent->left = candidate->right;  // 부모의 왼쪽 자식을 후보 노드의 오른쪽 자식으로 대입

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; // ptr의 key를 candidate의 key로 교체하고

	free(candidate); // 기존 candidate를 메모리 해제 후 반환 후 함수 종료
	return 1;
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

Node *pop() // stack에서 pop해주는 함수
{
	if (top < 0) // stack이 비어있으면 null 반환
		return NULL;
	return stack[top--]; // 맨 위 원소 반환하고 top 값 낮춤
}

void push(Node *aNode) // stack에 push해주는 함수
{
	stack[++top] = aNode; // stack의 맨 위에 node 저장하고 top 값 높임
}

void printStack() // stack 출력해주는 함수
{
	int i = 0; // 반복문용 변수
	printf("--- stack ---\n");
	while (i <= top) // 0부터 top까지 반복
	{
		printf("stack[%d] = %d\n", i, stack[i]->key); // stack 내용 출력
	}
}

Node *deQueue() // queue에서 첫번째 원소 제거하는 함수
{
	if (front == rear) // 원소가 없다면 null 반환 후 함수 종료
	{
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; // 원소가 있으면 front 위치 한칸 앞으로 옮기고
	return queue[front];				  // 새 front 위치의 queue 값 반환 후 함수 종료
}

void enQueue(Node *aNode) // queue에서 마지막 부분에 원소 추가하는 함수
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; // 마지막 부분을 한 칸 뒤로 옮김
	if (front == rear)					// 큐가 꽉 찼으면 함수 종료
	{
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; // 새로운 마지막 칸에 인자로 받은 node 저장
}
