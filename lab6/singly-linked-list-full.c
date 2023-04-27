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
            printf("Your Key = ");     // delete node 명령 입력받으면
            scanf("%d", &key);         // key값 입력받고
            deleteNode(headnode, key); // deleteNode 함수를 통해 해당 key값 가진 node 삭제
            break;
        case 'n':
        case 'N':
            printf("Your Key = ");     // insert last 명령 입력받으면
            scanf("%d", &key);         // key값 입력받고
            insertLast(headnode, key); // insertLast 함수를 통해 해당 key값 가진 node 마지막에 삽입
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
    node->key = key;                                       // 새로운 node에 key값 저장
    node->link = NULL;                                     // 새 node의 다음 node는 아직 null

    if (h->first == NULL) // headnode가 가리키는 node가 없으면
    {
        h->first = node; // 새로운 node가 headnode가 가리키는 node가 되고 반환 후 함수 종료
        return 0;
    }

    listNode *n = h->first;     // n에 headnode가 가리키는 node 대입
    listNode *trail = h->first; // trail에도 같은 node 대입

    /* key를 기준으로 삽입할 위치를 찾는다 */
    while (n != NULL)
    {
        if (n->key >= key)
        {
            /* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
            if (n == h->first) // 첫 노드 앞에 삽입해야 한다면
            {
                h->first = node; // 첫 노드를 변경하고
                node->link = n;  // 기존 첫 노드는 새로운 첫 노드의 다음 노드가 됨
            }
            else
            {                       /* 중간이거나 마지막인 경우 */
                node->link = n;     // node는 n의 전 위치, 그리고
                trail->link = node; // trail의 다음 위치에 놓임
            }
            return 0; // 반환 후 함수종료
        }

        trail = n;   // trail은 기존 n node가 되고
        n = n->link; // n node는 다음 node가 됨
    }

    /* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
    trail->link = node;
    return 0; // 반환 후 함수 종료
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode *h, int key)
{

    listNode *node = (listNode *)malloc(sizeof(listNode)); // 새로운 node 선언 및 메모리 동적할당
    node->key = key;                                       // key값 저장
    node->link = NULL;                                     // 다음 node의 link는 null

    if (h->first == NULL) // headnode가 가리키는 node가 null이라면
    {
        h->first = node; // 새로운 node를 headnode가 가리키게 하고 반환 후 함수 종료
        return 0;
    }

    listNode *n = h->first; // headnode가 가리키는 node가 null이 아니면 node n을 선언하고 headnode가 가리키는 node를 대입
    while (n->link != NULL) // headnode가 가리키는 node의 다음 node가 존재하는 동안 반복
    {
        n = n->link; // n node의 위치를 다음 node로 변경, 마지막 node까지 반복하게 됨
    }
    n->link = node; // 마지막 node의 다음 node로 새로 입력받은 node의 포인터 대입하고 반환 후 함수 종료
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

    if (h->first == NULL) // headnode가 가리키는 node가 없을 경우
    {
        printf("nothing to delete.\n"); // 안내문 출력하고 함수 종료
        return 0;
    }

    listNode *n = h->first; // node n 선언 후 headnode가 가리키는 node로 초기화
    listNode *trail = NULL; // node trail 선언 후 NULL로 초기화

    /* key를 기준으로 삽입할 위치를 찾는다 */
    while (n != NULL) // n이 null일 때 까지 n과 trail의 위치를 한칸씩 다음으로 이동하면서 반복
    {
        if (n->key == key) // n이 key값이 일치하는 node일 경우
        {
            /* 첫 노드를 삭제해야 하는 경우 인지 검사 */
            if (n == h->first) // n이 headnode가 가리키고 있는 node일 경우
            {
                h->first = n->link; // headnode가 자신이 가리키고 있는 node의 다음 node를 가리키도록 함
            }
            else
            {                          /* 중간인 경우거나 마지막인 경우 */
                trail->link = n->link; // n의 이전 node가 다음 node를 가리키게 함
            }
            free(n);  // n은 메모리 해제
            return 0; // 반환 후 함수 종료
        }

        trail = n; // trail과 n의 위치를 한칸씩 다음으로 이동
        n = n->link;
    }

    /* 찾지 못 한경우 */
    printf("cannot find the node for key = %d\n", key); // 안내문 출력 후 함수 종료
    return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode *h)
{

    if (h->first == NULL) // headnode가 가리키는 node가 없을 경우
    {
        printf("nothing to delete.\n"); // 안내문 출력하고 반환 후 함수 종료
        return 0;
    }

    listNode *n = h->first; // node n 선언 및 headnode가 가리키는 node로 초기화
    listNode *trail = NULL; // node trail 선언 및 null로 초기화

    /* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
    if (n->link == NULL)
    {
        h->first = NULL; // headnode가 가리키는 node가 없도록 하고
        free(n);         // 원래 가리키던 node는 메모리 해제
        return 0;        // 반환 후 함수 종료
    }

    /* 마지막 노드까지 이동 */
    while (n->link != NULL)
    {
        trail = n; // trail과 n의 위치를 한 칸 씩 다음으로 옮김, n이 마지막 노드가 될 때 까지
        n = n->link;
    }

    /* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
    trail->link = NULL; // n이 마지막 node, trail이 마지막 직전 node라는 것을 확인했으므로 trail의 다음 node를 null로 하고
    free(n);            // 원래 마지막 node였던 n을 메모리 해제

    return 0; // 반환 후 함수 종료
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
