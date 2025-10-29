#include <stdio.h>
#include <string.h>
#include <ctype.h>

char expr[100];
int tempCount = 1;

// Function declarations
void generate(char op, char arg1, char arg2);
int precedence(char op);
void infixToPostfix(char infix[], char postfix[]);
void generateThreeAddress(char postfix[]);

//-----------------------
// Generate TAC instruction
//-----------------------
void generate(char op, char arg1, char arg2) {
    printf("t%d = %c %c %c\n", tempCount, arg1, op, arg2);
    tempCount++;
}

//-----------------------
// Operator precedence
//-----------------------
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

//-----------------------
// Infix → Postfix conversion
//-----------------------
void infixToPostfix(char infix[], char postfix[]) {
    char stack[100];
    int top = -1, k = 0;

    for (int i = 0; i < strlen(infix); i++) {
        char c = infix[i];

        if (isalnum(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = stack[top--];
            }
            top--; // pop '('
        } else {
            while (top != -1 && precedence(stack[top]) >= precedence(c)) {
                postfix[k++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    while (top != -1) {
        postfix[k++] = stack[top--];
    }
    postfix[k] = '\0';
}

//-----------------------
// Generate 3-address code from postfix
//-----------------------
void generateThreeAddress(char postfix[]) {
    char stack[100][10];
    int top = -1;

    for (int i = 0; i < strlen(postfix); i++) {
        char c = postfix[i];

        if (isalnum(c)) {
            char temp[2];
            temp[0] = c;
            temp[1] = '\0';
            strcpy(stack[++top], temp);
        } else {
            char op2[10], op1[10], result[10];
            strcpy(op2, stack[top--]);
            strcpy(op1, stack[top--]);
            sprintf(result, "t%d", tempCount++);
            printf("%s = %s %c %s\n", result, op1, c, op2);
            strcpy(stack[++top], result);
        }
    }
}

int main() {
    char postfix[100];

    printf("Enter an arithmetic expression: ");
    scanf("%s", expr);

    infixToPostfix(expr, postfix);

    printf("\nPostfix Expression: %s\n", postfix);
    printf("\nThree Address Code:\n");
    generateThreeAddress(postfix);

    return 0;
}
