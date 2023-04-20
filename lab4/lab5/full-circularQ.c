/**
 * circularQ.c
 *
 * School of Computer Science,
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct
{
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType; // 사이즈 4짜리 배열과 front, rear 변수를 가지는 큐 구조체 선언

QueueType *createQueue();                   // 큐를 생성하는 함수
int freeQueue(QueueType *cQ);               // 큐에 할당된 메모리를 해제하는 함수
int isEmpty(QueueType *cQ);                 // 큐가 비었는지 확인하는 함수
int isFull(QueueType *cQ);                  // 큐가 꽉 찼는지 확인하는 함수
void enQueue(QueueType *cQ, element item);  // 큐에 삽입하는 함수
void deQueue(QueueType *cQ, element *item); // 큐에서 삭제하는 함수
void printQ(QueueType *cQ);                 // 큐 내용 출력하는 함수
void debugQ(QueueType *cQ);                 // 큐 내용과 front, rear의 위치 등 출력
element getElement();                       // item 내용 입력받는 함수

int main(void)
{
    printf("[----- [Jeonghyeon Kim] [2018038075] -----]\n");

    QueueType *cQ = createQueue(); // 원형 큐 생성
    element data;                  // 입력받을 용으로 선언

    char command; // 명령 입력받을 변수 선언

    do // command 입력받고 함수 실행
    {
        printf("\n-----------------------------------------------------\n"); // 안내문 출력
        printf("                     Circular Q                   \n");
        printf("------------------------------------------------------\n");
        printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
        printf("------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); // 명령 입력받음

        switch (command) // 명령에 따라 switch문 실행
        {
        case 'i':
        case 'I':
            data = getElement(); // 명령이 i면 getElement()함수를 실행해 data를 입력받음
            enQueue(cQ, data);   // 큐에 data 추가
            break;
        case 'd':
        case 'D':
            deQueue(cQ, &data); // 명령이 d면 큐에서 data 삭제하고 해당 데이터는 data 변수에 저장
            break;
        case 'p':
        case 'P':
            printQ(cQ); // 명령이 p면 큐 내용 출력
            break;
        case 'b':
        case 'B':
            debugQ(cQ); // 명령이 b면 큐 내용과 front, rear의 위치 등 출력
            break;
        case 'q':
        case 'Q':
            break; // 명령이 q면 while문을 통해 프로그램 종료
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 지정 문자 외 다른 게 입력되면 안내문 출력 후 다시 입력받음
            break;
        }

    } while (command != 'q' && command != 'Q'); // command로 q가 입력될 때 까지 실행

    return 1; // 반환 후 프로그램 종료
}

QueueType *createQueue() // 큐를 생성하는 함수
{
    QueueType *cQ;                               // QueueType 구조체를 포인터로 선언
    cQ = (QueueType *)malloc(sizeof(QueueType)); // 포인터에 동적할당
    cQ->front = 0;                               // 프론트의 위치를 0으로 초기화
    cQ->rear = 0;                                // rear의 위치를 0으로 초기화
    return cQ;                                   // 초기화한 큐 반환
}

int freeQueue(QueueType *cQ) // 큐에 할당된 메모리를 해제하는 함수
{
    if (cQ == NULL) // 인자가 NULL이면
        return 1;   // 그냥 반환
    free(cQ);       // free로 메모리 해제
    return 1;       // 반환
}

element getElement() // item 내용 입력받는 함수
{
    element item;               // element형 item 선언
    printf("Input element = "); // 안내문 출력
    scanf(" %c", &item);        // item에 입력 받음
    return item;                // 반환
}

int isEmpty(QueueType *cQ) // 큐가 비었는지 확인하는 함수
{
    if (cQ->front == cQ->rear) // front와 rear의 위치가 같으면
    {
        printf("Circular Queue is empty!"); // 큐가 비었다고 안내문 출력
        return 1;                           // 비었다는 뜻으로 1 반환
    }
    else
        return 0; // 비지 않았으면 0 반환
}

int isFull(QueueType *cQ) // 큐가 꽉 찼는지 확인하는 함수
{
    if (((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front) // rear 다음 칸이 front라면
    {
        printf(" Circular Queue is full!"); // 큐가 꽉 찼다고 안내문 출력
        return 1;                           // 꽉 찼다는 뜻으로 1 반환
    }
    else
        return 0; // 꽉 차지 않았으면 0 반환
}

void enQueue(QueueType *cQ, element item) // 큐에 삽입하는 함수
{
    if (isFull(cQ)) // 큐가 꽉 찼으면 그냥 반환
        return;
    else
    {
        cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // rear의 위치를 한 칸 뒤로 미룸
        cQ->queue[cQ->rear] = item;                 // rear 위치에 새 item 저장
    }
}

void deQueue(QueueType *cQ, element *item) // 큐에서 삭제하는 함수
{
    if (isEmpty(cQ)) // 큐가 비었으면 그냥 반환
        return;
    else
    {

        cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; // front의 위치를 한 칸 뒤로 미룸
        *item = cQ->queue[cQ->front];                 // 꺼낸 item을 원래 변수에 다시 저장

        element item = "";               // 새 빈 아이템 선언
        cQ->queue[cQ->front - 1] = item; // 원래 자리에 빈 아이템 저장

        return; // 반환
    }
}

void printQ(QueueType *cQ) // 큐 내용 출력하는 함수
{
    int i, first, last; // while문용 변수 i와 시작, 끝을 표시하는 변수 두 개 선언

    first = (cQ->front + 1) % MAX_QUEUE_SIZE; // first 변수에 front 다음 위치(첫 아이템의 위치) 저장
    last = (cQ->rear + 1) % MAX_QUEUE_SIZE;   // last 변수에 rear 다음 위치(마지막 아이템의 다음 위치) 저장

    printf("Circular Queue : ["); // 큐 시작 부분 직전까지 안내문 출력

    i = first;        // 맨 첫 아이템부터 시작
    while (i != last) // 마지막 아이템까지 반복
    {
        printf("%3c", cQ->queue[i]);  // 아이템 출력
        i = (i + 1) % MAX_QUEUE_SIZE; // 다음 원소로 이동
    }
    printf(" ]\n"); // 출력 마무리
}

void debugQ(QueueType *cQ)
{

    printf("\n---DEBUG\n");                  // 안내문 출력
    for (int i = 0; i < MAX_QUEUE_SIZE; i++) // 큐 사이즈 만큼 반복
    {
        if (i == cQ->front) // i값이 front의 위치와 같으면
        {
            printf("  [%d] = front\n", i); // 그 위치는 front로 출력
            continue;
        }
        printf("  [%d] = %c\n", i, cQ->queue[i]); // 그 외에는 큐에 들어있는 값으로 출력
    }
    // printQ(cQ);
    printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // front와 rear의 위치 출력
}
