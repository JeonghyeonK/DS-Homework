/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node // headnode 제외한 나머지 node 구조체
{
	int key;			// node별로 갖는 key 값
	struct Node *llink; // 왼쪽 node의 위치
	struct Node *rlink; // 오른쪽 node의 위치
} listNode;

/* 함수 리스트 */
int initialize(listNode **h);		   // head node 초기화하는 함수
int freeList(listNode *h);			   // 연결리스트의 메모리를 모두 해제하는 함수
int insertLast(listNode *h, int key);  // list 마지막에 key에 대한 노드하나를 추가
int deleteLast(listNode *h);		   // list의 마지막 노드 삭제
int insertFirst(listNode *h, int key); // list 처음에 key에 대한 노드하나를 추가
int deleteFirst(listNode *h);		   // list의 첫번째 노드 삭제
int invertList(listNode *h);		   // 리스트의 링크를 역순으로 재 배치

int insertNode(listNode *h, int key); // 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int deleteNode(listNode *h, int key); // list에서 key에 대한 노드 삭제

void printList(listNode *h); // 연결리스트 출력하는 함수

int main()
{
	char command;			   // 명령을 입력받는 변수
	int key;				   // 노드별로 key값 입력받는 변수
	listNode *headnode = NULL; // headnode 선언

	printf("[----- [Jeonghyeon Kim] [2018038075] -----]\n");

	do
	{																				  // 안내문 출력하고 명령 입력받아 실행하는 것을 반복
		printf("----------------------------------------------------------------\n"); // 안내문 출력
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); // 명령 입력받음
		scanf(" %c", &command);

		switch (command)
		{
		case 'z':
		case 'Z':				   // initialize 명령 입력받으면
			initialize(&headnode); // headnode 초기화 함수 실행 후 종료
			break;
		case 'p':
		case 'P':				 // print 명령 입력받으면
			printList(headnode); // headnode를 인자로 받아 printList 함수를 통해 출력 후 종료
			break;
		case 'i':
		case 'I':
			printf("Your Key = ");	   // insert 명령 입력받으면
			scanf("%d", &key);		   // key값 입력받고
			insertNode(headnode, key); // insertNode 함수를 통해 연결리스트에 삽입
			break;
		case 'd':
		case 'D':
			printf("Your Key = ");	   // delete node 명령 입력받으면
			scanf("%d", &key);		   // key값 입력받고
			deleteNode(headnode, key); // deleteNode 함수를 통해 해당 key값 가진 node 삭제
			break;
		case 'n':
		case 'N':
			printf("Your Key = ");	   // insert last 명령 입력받으면
			scanf("%d", &key);		   // key값 입력받고
			insertLast(headnode, key); // insertLast 함수를 통해 해당 key값 가진 node 마지막에 삽입
			break;
		case 'e':
		case 'E':
			deleteLast(headnode); // delete last 명령 입력받으면 deleteLast 함수를 통해 마지막 node 삭제
			break;
		case 'f':
		case 'F':
			printf("Your Key = ");		// insert first 명령 입력받으면
			scanf("%d", &key);			// key값 입력받고
			insertFirst(headnode, key); // insertFirst 함수를 통해 headnode 오른쪽 위치에 node 생성
			break;
		case 't':
		case 'T':
			deleteFirst(headnode); // delete first 명령 입력받으면 deleteFirst 함수를 통해 headnode 오른쪽 node 삭제
			break;
		case 'r':
		case 'R':
			invertList(headnode); // invert list 명령 입력받으면 invertList 함수를 통해 연결리스트 역순으로 정렬
			break;
		case 'q':
		case 'Q':
			freeList(headnode); // quit 명령 입력받으면 freeList 함수를 통해 메모리 모두 해제하고 while문 조건을 통해 반복문 종료
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // q 명령을 입력받으면 반복 종료
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initialize(listNode **h)
{

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode *)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode *h)
{

	if (h->rlink == h)
	{
		free(h);
		return 1;
	}

	listNode *p = h->rlink;

	listNode *prev = NULL;
	while (p != NULL && p != h)
	{
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}

void printList(listNode *h)
{
	int i = 0;
	listNode *p;

	printf("\n---PRINT\n");

	if (h == NULL)
	{
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h)
	{
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
	while (p != NULL && p != h)
	{
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode *h, int key)
{

	if (h == NULL)
		return -1;

	listNode *node = (listNode *)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) /* 첫 노드로 삽입 */
	{
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	}
	else
	{
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}

	return 1;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode *h)
{

	if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode *nodetoremove = h->llink;

	/* link 정리 */
	nodetoremove->llink->rlink = h;
	h->llink = nodetoremove->llink;

	free(nodetoremove);

	return 1;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode *h, int key)
{

	listNode *node = (listNode *)malloc(sizeof(listNode));
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
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode *h)
{

	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode *nodetoremove = h->rlink;

	/* link 정리 */
	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink;

	free(nodetoremove);

	return 1;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode *h)
{

	if (h->rlink == h || h == NULL)
	{
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;

	while (n != NULL && n != h)
	{
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->rlink = middle;

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode *h, int key)
{

	if (h == NULL)
		return -1;

	listNode *node = (listNode *)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->rlink == h)
	{
		insertFirst(h, key);
		return 1;
	}

	listNode *n = h->rlink;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while (n != NULL && n != h)
	{
		if (n->key >= key)
		{
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if (n == h->rlink)
			{
				insertFirst(h, key);
			}
			else
			{ /* 중간이거나 마지막인 경우 */
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
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
int deleteNode(listNode *h, int key)
{

	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode *n = h->rlink;

	while (n != NULL && n != h)
	{
		if (n->key == key)
		{
			if (n == h->rlink)
			{ /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			}
			else if (n->rlink == h)
			{ /* 마지막 노드인 경우 */
				deleteLast(h);
			}
			else
			{ /* 중간인 경우 */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}
