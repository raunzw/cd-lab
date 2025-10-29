#include <stdio.h>
#include <ctype.h>
#include <string.h>

char input[100];
int i = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();
void match(char expected);
void error();

void match(char expected) {
    if (input[i] == expected) {
        i++;
    } else {
        error();
    }
}

void error() {
    printf("❌ Syntax Error at position %d near '%c'\n", i, input[i]);
}

void E() {
    T();
    Eprime();
}

void Eprime() {
    if (input[i] == '+') {
        match('+');
        T();
        Eprime();
    }
 
}

void T() {
    F();
    Tprime();
}

void Tprime() {
    if (input[i] == '*') {
        match('*');
        F();
        Tprime();
    }
   
}

void F() {
    if (input[i] == '(') {
        match('(');
        E();
        match(')');
    } else if (isalpha(input[i])) {
        match(input[i]); 
    } else {
        error();
    }
}

int main() {
    printf("Enter an expression: ");
    scanf("%s", input);

    E(); 

 
    if (input[i] == '\0')
        printf(" Parsing successful! The expression is valid.\n");
    else
        printf(" Parsing failed! Extra characters after parsing.\n");

    return 0;
}
