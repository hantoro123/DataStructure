/* postfix.c
 *
 * Data Structures, Homework #5
 * School of Computer Science at Chungbuk National University
 */
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
// 각 operator에 대한 우선순위를 입력
typedef enum{
lparen = 0, /* ( 왼쪽 괄호 */
rparen = 9, /* ) 오른쪽 괄호*/
times = 7, /* * 곱셈 */
divide = 6, /* / 나눗셈 */
plus = 5, /* + 덧셈 */
minus = 4, /* - 뺄셈 */
operand = 1 /* 피연산자 */
} precedence;
char infixExp[MAX_EXPRESSION_SIZE]; /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE]; /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE]; /* postfix로 변환을 위해 필요한 스택*/
int evalStack[MAX_STACK_SIZE]; /* 계산을 위해 필요한 스택 */
int postfixStackTop = -1; /* postfixStack용 top */
int evalStackTop = -1; /* evalStack용 top */
int evalResult = 0; /* 계산 결과를 저장 */

// 각 함수를 선언
void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
    // 동작할 command 변수
    char command;
    // command를 입력하고 q,Q가 입력될때까지 반복
    do{
    printf("----------------------------------------------------------------\n");
    printf(" Infix to Postfix, then Evaluation\n");
    printf("----------------------------------------------------------------\n");
    printf(" Infix=i, Postfix=p, Eval=e, Debug=d,Reset=r, Quit=q \n");
    printf("----------------------------------------------------------------\n");
    printf("Command = ");
    scanf(" %c", &command);
    // 각 command를 입력받아 맞는 case를 진행
    switch(command) {
        case 'i': case 'I':
            getInfix();
            break;
        case 'p': case 'P':
            toPostfix();
            break;
        case 'e': case 'E':
            evaluation();
            break;
        case 'd': case 'D':
            debug();
            break;
        case 'r': case 'R':
            reset();
            break;
        case 'q': case 'Q':
            break;
        // 잘못된 값이 들어오면 출력
        default:
            printf("\n >>>>> Concentration!! <<<<<\n");
            break;
        }
    }while(command != 'q' && command != 'Q');

    printf("[----- [한상준] [2017018024] -----]");
    return 1;
}

// postfix의 operator token을 stack에 넣어두는 함수
void postfixPush(char x)
{
    // 우선순위가 크면 stacktop + 1에 넣는다.
    postfixStack[++postfixStackTop] = x;
}

// postfix의 stack을 pop하는 함수
char postfixPop()
{
    char x;
    // stack의 top이 -1이면 비어있기 때문에 바로 return
    if(postfixStackTop == -1)
        return '\0';
    else {
        // 아니라면 top의 값을 pop하고 topdmf - 1한다.
        x = postfixStack[postfixStackTop--];
    }
    return x;
}

// 값을 evalstack에 넣는 함수
void evalPush(int x)
{
    //현재 top+1 위치에 값을 저장
    evalStack[++evalStackTop] = x;
}

// 값을 evalstack에서 pop하는 함수
int evalPop()
{
    // top이 -1이면 비어있으므로 -1을 바로 리턴
    if(evalStackTop == -1)
        return -1;
    else
        // 안 비어있다면 top값을 return하고 top을 -1
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
// infix로 계산식을 입력받는 함수
void getInfix()
{
    printf("Type the expression >>> ");
    // 문자열로 계산식을 받아 저장
    scanf("%s",infixExp);
}

// precedence의 symbol받아 통해 저장된 우선순위를 보고 operator나 operand를 return받는 함수
precedence getToken(char symbol)
{
    switch(symbol) {
        // 각 symbol에 따라서 operator나 operand를 return한다.
        case '(' : return lparen;
        case ')' : return rparen;
        case '+' : return plus;
        case '-' : return minus;
        case '/' : return divide;
        case '*' : return times;
        default : return operand;
    }
}

// precedence의 x를 받아 값의 우선순위를 확인하기 위한 함수
precedence getPriority(char x)
{
    return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */

// 문자열 C를 postfixExp에 추가하는 함수
void charCat(char* c)
{
    if (postfixExp == '\0')
        // postfix와 c를 하나 복사한다.
        strncpy(postfixExp, c, 1);
    else
        // c를 postfixExp에 하나 붙인다.
        strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */

// infix를 postfix로 바꾸는 함수
void toPostfix()
{
    /* infixExp의 문자 하나씩을 읽기위한 포인터 */
    char *exp = infixExp;
    char x; /* 문자하나를 임시로 저장하기 위한 변수 */
    /* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */

    // infixExp이 끝날때까지 반복한다.
    while(*exp != '\0')
    {
        // exp가 operand라면
        if(getPriority(*exp) == operand)
        {   
            // postfixExp에 붙인다.
            x = *exp;
            charCat(&x);
        }
        // exp가 lparen이면
        else if(getPriority(*exp) == lparen) {
            // postfixstack에 넣는다
            postfixPush(*exp);
        }
        // exp가 rparen이면
        else if(getPriority(*exp) == rparen)
        {
            // postfixstack에 lparen이 나올때까지 pop하면서 postfixExp에 붙인다.
            while((x = postfixPop()) != '(') {
                charCat(&x);
                }
            }
        // 그 외의 operator이면
        else
        {   // postfixstack에 top의 우선순위보다 낮다면
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
                {   
                    // postfixstack의 top을 가져오고
                    x = postfixPop();
                    // postfixExp에 붙인다.
                    charCat(&x);
                }
                // postfixstack에 top의 우선순위보다 높다면 postfixstack에 push
                postfixPush(*exp);
            }
            // 다음 exp로 증가
            exp++;
        }
    
    // postfixstack이 빌때 까지 반복
    while(postfixStackTop != -1)
    {  
        // postfixstack의 top을 가져오고
        x = postfixPop();
        // postfixExp에 붙인다.
        charCat(&x);
    }
}

// 현재 상황을 볼 수 있는 debug 함수
void debug()
{
    // 디버그 infix, postfix, eval, postfixstack을 출력
    printf("\n---DEBUG\n");
    printf("infixExp = %s\n", infixExp);
    printf("postExp = %s\n", postfixExp);
    printf("eval result = %d\n", evalResult);
    printf("postfixStack : ");
    for(int i = 0; i < MAX_STACK_SIZE; i++)
        printf("%c ", postfixStack[i]);
    printf("\n");
}

// infix, postfix, eval, stack을 초기화하는 함수
void reset()
{
    // infix, postfix 식을 0으로 초기화
    infixExp[0] = '\0';
    postfixExp[0] = '\0';
    // postfixStack을 0으로 초기화
    for(int i = 0; i < MAX_STACK_SIZE; i++)
        postfixStack[i] = '\0';

    // 각 stack의 top을 -1로 초기화
    postfixStackTop = -1;
    evalStackTop = -1;
    // 결과값을 초기화
    evalResult = 0;
}

// 결과 값을 구하는 함수
void evaluation()
{
    // operand를 받을 변수와 index 넣을 변수
    int opr1, opr2, i;
    
    // postfixExp의 길이를 length에 넣고
    int length = strlen(postfixExp);
    // 계산식의 한 인덱스씩 넣을 변수
    char symbol;
    // evalStack의 top을 -1로 초기화
    evalStackTop = -1;
    
    // length만큼 반복
    for(i = 0; i < length; i++)
    {
        // postfixExp의 해당 인덱스의 문자
        symbol = postfixExp[i];

        // symbol이 operand라면 evalStack에 바로 push한다.
        if(getToken(symbol) == operand) {
            evalPush(symbol - '0');
        }
        else {
            // operator라면 evalStack에서 pop을해 각 변수에 넣는다.
            opr2 = evalPop();
            opr1 = evalPop();
            // symbol이 각 case에 맞게 해당 연산을 하고 evalStack에 다시 push한다.
            switch(getToken(symbol)) {
                case plus: evalPush(opr1 + opr2); break;
                case minus: evalPush(opr1 - opr2); break;
                case times: evalPush(opr1 * opr2); break;
                case divide: evalPush(opr1 / opr2); break;
                default: break;
            }
        }
    }
    // 최종적으로 결과값을 pop해 저장한다. 
    evalResult = evalPop();
}