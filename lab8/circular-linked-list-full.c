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
	if (*h != NULL)	  // headnode가 NULL이 아니라면
		freeList(*h); // freeList 함수를 이용해 기존 연결리스트 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode *)malloc(sizeof(listNode)); // headnode에 메모리 동적 할당
	(*h)->rlink = *h;						   // 일단 자기 자신을 가리키도록 함
	(*h)->llink = *h;
	(*h)->key = -9999; // 임시값
	return 1;		   // headnode 반환
}

int freeList(listNode *h)
{

	if (h->rlink == h) // 헤드노드의 다음노드가 자기자신으로 지정되어있으면
	{
		free(h); // 메모리 헤제 및 반환
		return 1;
	}

	listNode *p = h->rlink; //  헤드노드의 다음노드부터 시작

	listNode *prev = NULL; // 이전 node를 나타내는 구조체 선언 및 NULL로 초기화
	while (p != NULL && p != h)
	{				  // headnode가 가리키는 다음 node가 NULL일 때 까지
		prev = p;	  // 현재 일반 node 중 가장 앞에 있는 node를 prev에 대입하고
		p = p->rlink; // p가 앞에서 두번째에 있는 node로 변경됨
		free(prev);	  // 가장 앞에 있는 node 메모리 해제
	}
	free(h); // 마지막으로 headnode 메모리 해제 후 반환
	return 0;
}

void printList(listNode *h)
{				 // 연결리스트 출력하는 함수
	int i = 0;	 // node 개수 저장하는 변수
	listNode *p; // node 구조체

	printf("\n---PRINT\n"); // 안내문 출력

	if (h == NULL) // headnode가 NULL이면
	{
		printf("Nothing to print....\n"); // 안내문 출력 후 반환
		return;
	}

	p = h->rlink; // headnode가 NULL이 아니면 node구조체에 headnode가 가리키는 다음 node를 대입

	while (p != NULL && p != h) // p가 NULL이 아니면서 head node도 아닌 동안 실행
	{
		printf("[ [%d]=%d ] ", i, p->key); // i번째 node의 key를 출력
		p = p->rlink;					   // 출력한 node의 다음 node로 link 변경
		i++;							   // node 개수 증가
	}
	printf("  items = %d\n", i); // 출력한 node의 개수 출력

	/* print addresses */
	printf("\n---checking addresses of links\n"); // 연결리스트의 address 출력
	printf("-------------------------------\n");
	// head node부터 왼쪽, 자기자신, 오른쪽 node 주소 출력
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;						// node 순서 출력용 변수 초기화
	p = h->rlink;				// head node의 다음(오른쪽) 노드부터 시작
	while (p != NULL && p != h) // p가 NULL이 아니면서 head node도 아닌 동안 실행
	{
		// 왼쪽, 자기자신, 오른쪽 node 주소 출력
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink; // p를 다음 노드로 변경, 순서 출력용 변수 1 증가
		i++;
	}
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode *h, int key)
{

	if (h == NULL) // head node가 존재하지 않으면 반환후 실행 종료
		return -1;

	listNode *node = (listNode *)malloc(sizeof(listNode)); // 새로운 node 선언 및 메모리 동적할당
	node->key = key;									   // key값 저장
	node->rlink = NULL;									   // 오른쪽 node의 link는 null
	node->llink = NULL;									   // 왼쪽 node의 link는 null

	if (h->rlink == h) /* 첫 노드로 삽입 */
	{
		h->rlink = node; // head의 왼쪽, 오른쪽 노드를 새 노드로 지정
		h->llink = node;
		node->rlink = h; // 새 노드의 왼쪽, 오른쪽 노드를 head로 지정
		node->llink = h;
	}
	else // 첫 노드가 아닐 경우
	{
		h->llink->rlink = node; // head와 기존 llink 노드 사이에 새 node 삽입
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}

	return 1; // 반환 후 함수 종료
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode *h)
{

	if (h->llink == h || h == NULL) // headnode밖에 없거나 headnode도 없을 때
	{
		printf("nothing to delete.\n"); // 안내문 출력 후 반환 후 함수 종료
		return 1;
	}

	listNode *nodetoremove = h->llink; // 삭제할 노드 구조체 변수를 head의 왼쪽 노드로 초기화

	/* link 정리 */
	nodetoremove->llink->rlink = h; // 삭제할 노드의 왼쪽 node와 오른쪽(head) node가 서로 붙어있게 함
	h->llink = nodetoremove->llink;

	free(nodetoremove); // 해당 노드 메모리 해제 후 반환 후 함수 종료

	return 1;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode *h, int key)
{

	listNode *node = (listNode *)malloc(sizeof(listNode)); // 새로운 node 선언 및 메모리 동적 할당
	node->key = key;									   // 새로운 node에 key값 저장
	node->rlink = NULL;									   // 양쪽 node 주소는 null로 초기화
	node->llink = NULL;

	node->rlink = h->rlink; // headnode와 headnode의 오른쪽 노드 사이에 새 node를 끼우고 서로를 link하게 함
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;

	return 1; // 반환 후 함수 종료
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode *h)
{

	if (h == NULL || h->rlink == h) // headnode 혹은 그가 가리키고 있는 다음 node가 없으면
	{
		printf("nothing to delete.\n"); // 안내문 출력 후 반환 후 함수 종료
		return 0;
	}

	listNode *nodetoremove = h->rlink; // 삭제할 node 구조체 변수를 head의 다음 node로 초기화

	/* link 정리 */
	nodetoremove->rlink->llink = h; // 삭제할 node의 양쪽 node가 서로를 link하게 함
	h->rlink = nodetoremove->rlink;

	free(nodetoremove); // 메모리 해제 후 반환 후 함수 종료

	return 1;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode *h)
{

	if (h->rlink == h || h == NULL) // head node가 자기 자신밖에 없거나 존재하지 않으면
	{
		printf("nothing to invert...\n"); // 안내문 출력 후 반환 후 함수 종료
		return 0;
	}
	listNode *n = h->rlink; // node n 선언 및 headnode가 가리키고 있는 다음 node로 초기화
	listNode *trail = h;	// node trail 선언 및 head로 초기화
	listNode *middle = h;	// node middle 선언 및 head로 초기화

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;

	while (n != NULL && n != h) // n이 존재하지만 head는 아닌 동안 반복
	{
		trail = middle; // 연속으로 이어진 세 node trail, middle, n 모두 한 칸씩 오른쪽으로 이동
		middle = n;
		n = n->rlink;
		middle->rlink = trail; // middle 기준으로 양쪽 node를 반대로 가리키도록 함
		middle->llink = n;
	}

	h->rlink = middle; // 마지막으로 headnode가 middle을 다음 노드로 가리키도록 함

	return 0; // 반환 후 함수 종룐
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode *h, int key)
{

	if (h == NULL) // headnode가 없으면 반환 후 함수 종료
		return -1;

	listNode *node = (listNode *)malloc(sizeof(listNode)); // 새로운 node 선언 및 메모리 동적할당
	node->key = key;									   // 새로운 node에 key값 저장
	node->llink = node->rlink = NULL;					   // 새 node의 왼쪽, 오른쪽 node는 아직 null

	if (h->rlink == h) // headnode가 가리키는 다음 node가 없으면
	{
		insertFirst(h, key); // insertFirst 함수를 이용해 node 삽입 후 반환 후 함수 종료
		return 1;
	}

	listNode *n = h->rlink; // n에 headnode가 가리키는 다음 node 대입

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while (n != NULL && n != h) // n이 존재하지만 head는 아닌 동안 반복
	{
		if (n->key >= key) // key값보다 크거나 같은 key를 가진 n을 찾으면
		{
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if (n == h->rlink) // n이 첫 노드라면 insertFirst함수를 통해 삽읿
			{
				insertFirst(h, key);
			}
			else
			{					 /* 중간이거나 마지막인 경우 */
				node->rlink = n; // n의 이전노드와 n 사이에 새 node를 삽입 후 서로를 옳게 가리키도록 함
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0; // 반환 후 함수 종료
		}

		n = n->rlink; // while문 조건 달성시까지 n을 한칸씩 다음으로 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0; // 반환 후 함수 종료
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode *h, int key)
{

	if (h->rlink == h || h == NULL) // headnode 자기 자신 혹은 다음 node가 없을 경우
	{
		printf("nothing to delete.\n"); // 안내문 출력 후 반환 후 함수 종료
		return 0;
	}

	listNode *n = h->rlink; // 구조체 n 선언 및 head의 다음 node로 초기화

	while (n != NULL && n != h) // n이 존재하지만 head는 아닌 동안 반복
	{
		if (n->key == key) // key값과 같은 key를 가진 n을 찾으면
		{
			if (n == h->rlink)
			{					/* 첫 노드째 노드 인경우 */
				deleteFirst(h); // deleteFirst 이용해 삭제
			}
			else if (n->rlink == h)
			{				   /* 마지막 노드인 경우 */
				deleteLast(h); // deleteLast 이용해 삭제
			}
			else
			{								/* 중간인 경우 */
				n->llink->rlink = n->rlink; // n의 양쪽 node가 서로를 가리키게 함
				n->rlink->llink = n->llink;
				free(n); // n 메모리 해제 후 반환 후 함수 종료
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); // 안내문 출력 후 반환 후 함수 종료
	return 0;
}
