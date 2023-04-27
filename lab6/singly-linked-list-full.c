/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science
 *  at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node
{
    int key;
    struct Node *link;
} listNode;

typedef struct Head
{
    struct Node *first;
} headNode;

/* 함수 리스트 */
headNode *initialize(headNode *h);
int freeList(headNode *h);

int insertFirst(headNode *h, int key);
int insertNode(headNode *h, int key);
int insertLast(headNode *h, int key);

int deleteFirst(headNode *h);
int deleteNode(headNode *h, int key);
int deleteLast(headNode *h);
int invertList(headNode *h);

void printList(headNode *h);

int main()
{
    char command;              // 명령을 입력받는 변수
    int key;                   // 노드별로 key값 입력받는 변수
    headNode *headnode = NULL; // headnode 선언

    do
    {                                                                                 // 안내문 출력하고 명령 입력받아 실행하는 것을 반복
        printf("----------------------------------------------------------------\n"); // 안내문 출력
        printf("                     Singly Linked List                         \n");
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
        case 'Z':                            // initialize 명령 입력받으면
            headnode = initialize(headnode); // headnode 초기화 함수 실행 후 종료
            break;
        case 'p':
        case 'P':                // print 명령 입력받으면
            printList(headnode); // headnode를 인자로 받아 printList 함수를 통해 출력 후 종료
            break;
        case 'i':
        case 'I':
            printf("Your Key = ");     // insert 명령 입력받으면
            scanf("%d", &key);         // key값 입력받고
            insertNode(headnode, key); // insertNode 함수를 통해 연결리스트에 삽입
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

    } while (command != 'q' && command != 'Q'); // q 명령을 입력받으면 반복 종료

    return 1;
}

headNode *initialize(headNode *h)
{ // headnode 초기화하는 함수

    if (h != NULL)   // headnode가 NULL이 아니라면
        freeList(h); // freeList 함수를 이용해 메모리 해제

    headNode *temp = (headNode *)malloc(sizeof(headNode)); // headnode에 메모리 동적 할당
    temp->first = NULL;                                    // first link 부분은 NULL로 함
    return temp;                                           // headnode 반환
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
        p = p->link; // p가 앞에서 두번째에 있는 node로 변경됨
        free(prev);  // 가장 앞에 있는 node 메모리 해제
    }
    free(h); // 마지막으로 headnode 메모리 해제 후 반환
    return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode *h, int key)
{

    listNode *node = (listNode *)malloc(sizeof(listNode)); // 새로운 node 선언 및 메모리 동적할당
    node->key = key; // 
    node->link = NULL;

    if (h->first == NULL)
    {
        h->first = node;
        return 0;
    }

    listNode *n = h->first;
    listNode *trail = h->first;

    /* key를 기준으로 삽입할 위치를 찾는다 */
    while (n != NULL)
    {
        if (n->key >= key)
        {
            /* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
            if (n == h->first)
            {
                h->first = node;
                node->link = n;
            }
            else
            { /* 중간이거나 마지막인 경우 */
                node->link = n;
                trail->link = node;
            }
            return 0;
        }

        trail = n;
        n = n->link;
    }

    /* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
    trail->link = node;
    return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode *h, int key)
{

    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;
    node->link = NULL;

    if (h->first == NULL)
    {
        h->first = node;
        return 0;
    }

    listNode *n = h->first;
    while (n->link != NULL)
    {
        n = n->link;
    }
    n->link = node;
    return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode *h, int key)
{

    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;

    node->link = h->first;
    h->first = node;

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
        return 0;
    }

    listNode *n = h->first;
    listNode *trail = NULL;

    /* key를 기준으로 삽입할 위치를 찾는다 */
    while (n != NULL)
    {
        if (n->key == key)
        {
            /* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
            if (n == h->first)
            {
                h->first = n->link;
            }
            else
            { /* 중간인 경우거나 마지막인 경우 */
                trail->link = n->link;
            }
            free(n);
            return 0;
        }

        trail = n;
        n = n->link;
    }

    /* 찾지 못 한경우 */
    printf("cannot find the node for key = %d\n", key);
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
    if (n->link == NULL)
    {
        h->first = NULL;
        free(n);
        return 0;
    }

    /* 마지막 노드까지 이동 */
    while (n->link != NULL)
    {
        trail = n;
        n = n->link;
    }

    /* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
    trail->link = NULL;
    free(n);

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

    h->first = n->link;
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
        n = n->link;
        middle->link = trail;
    }

    h->first = middle;

    return 0;
}

void printList(headNode *h)
{                // 연결리스트 출력하는 함수
    int i = 0;   // node 개수 저장하는 변수
    listNode *p; // node 구조체

    printf("\n---PRINT\n"); // 안내문 출력

    if (h == NULL) // headnode가 NULL이면
    {
        printf("Nothing to print....\n"); // 안내문 출력 후 반환
        return;
    }

    p = h->first; // headnode가 NULL이 아니면 node구조체에 headnode가 가리키는 첫번째 node를 대입

    while (p != NULL) // p가 NULL일 때 까지
    {
        printf("[ [%d]=%d ] ", i, p->key); // i번째 node의 key를 출력
        p = p->link;                       // 출력한 node의 다음 node로 link 변경
        i++;                               // node 개수 증가
    }

    printf("  items = %d\n", i); // 출력한 node의 개수 출력
}
