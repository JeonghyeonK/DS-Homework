/**
 * postfix.c
 *
 * School of Computer Science,
 * Chungbuk National University
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_STACK_SIZE 10      // 최대 stack 크기
#define MAX_EXPRESSION_SIZE 20 // 최대 infix expression 크기

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum
{
    lparen = 0, /* ( 왼쪽 괄호 */
    rparen = 9, /* ) 오른쪽 괄호*/
    times = 7,  /* * 곱셈 */
    divide = 6, /* / 나눗셈 */
    plus = 5,   /* + 덧셈 */
    minus = 4,  /* - 뺄셈 */
    operand = 1 /* 피연산자 */
} precedence;   // 열거형 변수를 이용해 연산자와 숫자를 매치해줌

char infixExp[MAX_EXPRESSION_SIZE];   // infix expression 입력받기 위한 문자열 변수
char postfixExp[MAX_EXPRESSION_SIZE]; // 변환된 후위표기식을 저장
char postfixStack[MAX_STACK_SIZE];    // 후위표기식을 만드는 데 사용할 stack
int evalStack[MAX_STACK_SIZE];        // 후위표기식을 계산하는 데 사용할 stack
int postfixStackTop = -1;             // 후위표기식을 만드는 데 사용할 stack에서 원소의 위치를 표시하는 변수
int evalStackTop = -1;                // 후위표기식을 계산하는 데 사용할 stack에서 원소의 위치를 표시하는 변수
int evalResult = 0;                   // 후위표기식을 계산한 결과를 저장할 변수
void postfixPush(char x);             // postfixStack에 문자를 push하는 함수
char postfixPop();                    // postfixStack에서 문자를 pop하고 반환받는 함수
void evalPush(int x);                 // 후위표기식을 계산하는 데 사용할 stack에 문자를 push하는 함수
int evalPop();                        // 후위표기식을 계산하는 데 사용할 stack에서 문자를 pop하는 함수
void getInfix();                      // 사용자에게 수식 입력받는 함수
precedence getToken(char symbol);     // 연산자를 입력받아 precedence 형태로 반환하는 함수
precedence getPriority(char x);       // 연산자를 입력받아 getToken() 함수를 이용해 precedence 자료형으로 우선순위 반환
void charCat(char *c);                // postfixExp 뒤에 문자 하나를 이어붙이는 함수
void toPostfix();                     // infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경
void debug();                         // 입력받거나 계산, 변환한 결과를 출력하는 함수
void reset();                         // 입력받거나 계산, 변환한 내용을 초기화하는 함수
void evaluation();                    // 완성된 후위표기식을 계산하는 함수
int main()
{
    printf("[----- [Jeonghyeon Kim] [2018038075] -----]\n");

    char command; // 명령을 입력받을 변수
    do            // 안내문을 출력하고 명령을 입력받아 실행
    {
        printf("----------------------------------------------------------------\n");
        printf(" Infix to Postfix, then Evaluation \n");
        printf("----------------------------------------------------------------\n");
        printf(" Infix=i, Postfix=p, Eval=e, Debug=d, Reset=r, Quit=q \n");
        printf("----------------------------------------------------------------\n");
        printf("Command = ");
        scanf(" %c", &command); // 명령 입력
        switch (command)        // 명령에 따라 switch문 실행
        {
        case 'i':
        case 'I':
            getInfix(); // 'i'를 입력받을 경우 getInfix() 함수 실행해서 수식 입력받음
            break;
        case 'p':
        case 'P':
            toPostfix(); // 'p'를 입력받을 경우 toPostFix() 함수 실행해서 후위표기식으로 변환
            break;
        case 'e':
        case 'E':
            evaluation(); // 'e'를 입력받을 경우 evaluation() 함수를 실행해서 후위표기식 계산
            break;
        case 'd':
        case 'D':
            debug(); // 'd'를 입력받을 경우 debug() 함수를 실행해서 현재까지 변환 혹은 계산된 내용 출력
            break;
        case 'r':
        case 'R':
            reset(); // 'r'을 입력받을 경우 reset() 함수를 실행해서 입력, 변환, 계산된 값 모두 추기화
            break;
        case 'q':  
        case 'Q':
            break; // 'q'를 입력받을 경우 switch문 실행을 종료하고 do-while문 실행 종료
        default:
            printf("\n >>>>> Concentration!! <<<<< \n"); // 그 외의 문자 입력받을 경우 재입력받음
            break;
        }
    } while (command != 'q' && command != 'Q'); // 명령으로 'q'를 입력받기 전까지 실행
    return 1;                                   // 반환 후 프로그램 종료
}
void postfixPush(char x) // postfixStack에 문자를 push해주는 함수
{
    postfixStack[++postfixStackTop] = x; // postfixStackTop의 값을 1 증가시키고 스택 내 해당 위치에 x 대입
}
char postfixPop() // postfixStack에서 문자를 pop해주는 함수
{
    char x;                    //
    if (postfixStackTop == -1) // Stack에 문자가 존재하지 않을 경우
        return '\0';           // '\0' 반환
    else                       // Stack에 문자가 존재할 경우
    {
        x = postfixStack[postfixStackTop--]; // 마지막 문자 한 개를 삭제하고 Top의 위치를 조절하고 삭제한 문자를 x로 반환받음
    }
    return x; // 삭제한 문자 반환
}
void evalPush(int x) // 변수를 받아서 evalStack에 push해주는 함수
{
    evalStack[++evalStackTop] = x; // 입력받은 변수를 evalStack에 추가하고 Top 위치 수정
}
int evalPop() // evalStack에서 pop해주는 함수
{
    if (evalStackTop == -1) // pop할 문자가 없으면 -1 리턴
        return -1;
    else
        return evalStack[evalStackTop--]; // pop할 문자가 있으면 pop하고 top의 위치 수정
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> "); // expression 입력받기 위해 안내문 출력
    scanf("%s", infixExp);              // expression 입력받음
}
precedence getToken(char symbol) // 연산자를 입력받아 precedence 형태로 반환하는 함수
{
    switch (symbol) // 연산자 문자를 입력받아 연산자에 따라 precedence 자료형으로 반환
    {
    case '(':
        return lparen;
    case ')':
        return rparen;
    case '+':
        return plus;
    case '-':
        return minus;
    case '/':
        return divide;
    case '*':
        return times;
    default:
        return operand;
    }
}
precedence getPriority(char x) // 연산자를 입력받아 getToken() 함수를 이용해 precedence 자료형으로 우선순위 반환
{
    return getToken(x);
}
/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char *c) //
{
    if (postfixExp == '\0')        // postfixExp에 들어있는 문자가 없을 경우
        strncpy(postfixExp, c, 1); // c에 들어있는 문자를 postfixExp에 대입
    else                           // postfixExp에 들어있는 문자가 있을 경우
        strncat(postfixExp, c, 1); // c에 들어있는 문자를 postfixExp 뒤에 붙임
}
/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
    /* infixExp의 문자 하나씩을 읽기위한 포인터 */
    char *exp = infixExp;
    char x; /* 문자하나를 임시로 저장하기 위한 변수 */
    /* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
    while (*exp != '\0') // 더이상 문자가 없을 때 까지 반복
    {
        if (getPriority(*exp) == operand) // 받은 문자가 피연산자일 경우
        {
            x = *exp;    // 피연산자를 변수 x에 대입
            charCat(&x); // postfixExp 문자열에 x를 이어붙임
        }
        else if (getPriority(*exp) == lparen) // 받은 문자가 왼쪽 괄호일 경우
        {
            postfixPush(*exp); // postfixStack에 문자를 push
        }
        else if (getPriority(*exp) == rparen) // 받은 문자가 오른쪽 괄호일 경우
        {
            while ((x = postfixPop()) != '(') // 왼쪽 괄호 문자가 나올 때 까지 pop
            {
                charCat(&x);
            }
        }
        else // 받은 문자가 +, -, *, -일 경우
        {
            while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) // 우선순위가 postfixStack에 있는 문자가 exp 문자보다 높을 경우
            {
                x = postfixPop(); // postfixStack에서 문자를 pop하고
                charCat(&x);      // postfixExp에 문자를 이어붙임
            }
            postfixPush(*exp); // postfixStack에 exp 문자(+, -, * , /) push
        }
        exp++; // 다음 문자로 이동
    }
    while (postfixStackTop != -1) // postfixStack에 문자가 남지 않을 때 까지
    {
        x = postfixPop(); // postfixStack에서 문자를 pop 하고
        charCat(&x);      // pop한 문자를 postfixExp에 이어붙임
    }
}
void debug()
{
    printf("\n---DEBUG\n");                   // 안내문 출력
    printf("infixExp = %s\n", infixExp);      // 사용자가 입력한 수식 출력
    printf("postExp = %s\n", postfixExp);     // 후위표기로 변환한 수식 출력
    printf("eval result = %d\n", evalResult); // 후위표기식을 계산한 값 출력
    printf("postfixStack : ");                // postfixStack 출력
    for (int i = 0; i < MAX_STACK_SIZE; i++)
        printf("%c ", postfixStack[i]); // stack에서 문자 하나씩 모두 출력
    printf("\n");
}
void reset()
{
    infixExp[0] = '\0';                      // 사용자에게 입력받을 infix 수식 초기화
    postfixExp[0] = '\0';                    // 후위표기식 계산을 위해 사용할 postfixExp 초기화
    for (int i = 0; i < MAX_STACK_SIZE; i++) // postfix Stack도 초기화
        postfixStack[i] = '\0';

    postfixStackTop = -1; // 스택별 Top의 위치도 초기화
    evalStackTop = -1;
    evalResult = 0; // 후위표기식 계산 결과도 초기화
}
void evaluation() // 완성된 후위표기식을 계산하는 함수
{
    int opr1, opr2, i;               // 연산자 두개와 반복문에 사용할 변수 i 선언
    int length = strlen(postfixExp); // postfixExp의 길이를 저장할 변수 length
    char symbol;                     // 단일 문자로 이용할 변수 symbol
    evalStackTop = -1;               // evalStack에서 위치를 표기할 변수
    for (i = 0; i < length; i++)     // postfixExp의 길이만큼 반복
    {
        symbol = postfixExp[i];          // symbol에 postfixExp의 문자를 대입
        if (getToken(symbol) == operand) // 문자가 피연산자일 경우
        {
            evalPush(symbol - '0'); // 피연산자를 정수형으로 바꿔서 evalStack에 push
        }
        else // 문자가 피연산자가 아닐 경우 (연산자인 경우)
        {
            opr2 = evalPop();         // 두번째 숫자를 먼저 pop하고
            opr1 = evalPop();         // 첫번째 숫자를 이어서 pop하고
            switch (getToken(symbol)) // 연산자의 종류에 따라
            {
            case plus:
                evalPush(opr1 + opr2); // + 연산자면 두 수를 더해서 evalStack에 push
                break;
            case minus:
                evalPush(opr1 - opr2); // - 연산자면 두 수의 차를 evalStack에 push
                break;
            case times:
                evalPush(opr1 * opr2); // * 연산자면 두 수의 곱을 evalStack에 push
                break;
            case divide:
                evalPush(opr1 / opr2); // / 연산자면 첫 번째 수를 두 번째 수로 나눠서 evalStack에 push
                break;
            default:
                break;
            }
        }
    }
    evalResult = evalPop(); // 결과로 나온 값을 result로 저장
}