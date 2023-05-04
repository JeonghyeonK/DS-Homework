
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

#include <stdio.h>
#include <stdlib.h>
/* 필요한 헤더파일 추가 if necessary */

typedef struct Node // headnode 제외한 나머지 node 구조체
{
	int key;			// node별로 갖는 key 값
	struct Node *llink; // 왼쪽 node의 위치
	struct Node *rlink; // 오른쪽 node의 위치
} listNode;

typedef struct Head // headnode 구조체
{
	struct Node *first; // headnode가 가리키는 node가 실질적으로 key값을 가지는 첫번째 node가 됨
} headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음 */
int initialize(headNode **h); // headnode 초기화하는 함수

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode *h);  // 연결리스트의 메모리를 모두 해제하는 함수

int insertNode(headNode *h, int key);
int insertLast(headNode *h, int key);
int insertFirst(headNode *h, int key);
int deleteNode(headNode *h, int key);
int deleteLast(headNode *h);
int deleteFirst(headNode *h);
int invertList(headNode *h);

void printList(headNode *h);

int main()
{
	char command;
	int key;
	headNode *headnode = NULL;

	do
	{
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

		switch (command)
		{
		case 'z':
		case 'Z':
			initialize(&headnode);
			break;
		case 'p':
		case 'P':
			printList(headnode);
			break;
		case 'i':
		case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd':
		case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n':
		case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e':
		case 'E':
			deleteLast(headnode);
			break;
		case 'f':
		case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't':
		case 'T':
			deleteFirst(headnode);
			break;
		case 'r':
		case 'R':
			invertList(headnode);
			break;
		case 'q':
		case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initialize(headNode **h)
{

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)	  // headnode가 NULL이 아니라면
		freeList(*h); // freeList 함수를 이용해 기존 연결리스트 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode *)malloc(sizeof(headNode)); // headnode에 메모리 동적 할당
	(*h)->first = NULL;						   // headnode가 가리키고 있는 node는 null로 초기화
	return 1;								   // headnode 반환
}

int freeList(headNode *h)
{
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
    listNode *p = h->first; // headnode가 가리키는 node부터 시작

    listNode *prev = NULL; // 이전 node를 나타내는 구조체 선언 및 NULL로 초기화
    while (p != NULL)
    {                // headnode가 가리키는 first node가 NULL일 때 까지
        prev = p;    // 현재 일반 node 중 가장 앞에 있는 node를 prev에 대입하고
        p = p->rlink; // p가 앞에서 두번째에 있는 node로 변경됨
        free(prev);  // 가장 앞에 있는 node 메모리 해제
    }
    free(h); // 마지막으로 headnode 메모리 해제 후 반환
}

void printList(headNode *h)
{
	int i = 0;
	listNode *p;

	printf("\n---PRINT\n");

	if (h == NULL)
	{
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL)
	{
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode *h, int key)
{

	listNode *node = (listNode *)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode *n = h->first;
	while (n->rlink != NULL)
	{
		n = n->rlink;
	}
	n->rlink = node;
	node->llink = n;
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode *h)
{

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode *n = h->first;
	listNode *trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if (n->rlink == NULL)
	{
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while (n->rlink != NULL)
	{
		trail = n;
		n = n->rlink;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;
	free(n);

	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode *h, int key)
{

	listNode *node = (listNode *)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 1;
	}

	node->rlink = h->first;
	node->llink = NULL;

	listNode *p = h->first;
	p->llink = node;
	h->first = node;

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode *h)
{

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode *n = h->first;
	h->first = n->rlink;

	free(n);

	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode *h)
{

	if (h->first == NULL)
	{
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while (n != NULL)
	{
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->first = middle;

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode *h, int key)
{

	listNode *node = (listNode *)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode *n = h->first;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while (n != NULL)
	{
		if (n->key >= key)
		{
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if (n == h->first)
			{
				insertFirst(h, key);
			}
			else
			{ /* 중간이거나 마지막인 경우 */
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode *h, int key)
{

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode *n = h->first;

	while (n != NULL)
	{
		if (n->key == key)
		{
			if (n == h->first)
			{ /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			}
			else if (n->rlink == NULL)
			{ /* 마지막 노드인 경우 */
				deleteLast(h);
			}
			else
			{ /* 중간인 경우 */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n = n->rlink;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}
