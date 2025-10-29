#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char production[MAX][MAX];
char firstResult[20];
char followResult[20];
int n; // number of productions
char start; // global start symbol

void findFirst(char c);
void findFollow(char c);

int visitedFirst[256] = {0}; // prevent infinite recursion
int visitedFollow[256] = {0};

//------------------------------------
// MAIN
//------------------------------------
int main() {
    int i;
    char ch;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter the productions (e.g., E=TR):\n");
    for (i = 0; i < n; i++) {
        scanf("%s", production[i]);
    }

    printf("\nEnter start symbol: ");
    scanf(" %c", &start);

    printf("\n--- FIRST sets ---\n");
    for (i = 0; i < n; i++) {
        ch = production[i][0];
        memset(firstResult, 0, sizeof(firstResult));
        memset(visitedFirst, 0, sizeof(visitedFirst));
        findFirst(ch);
        printf("FIRST(%c) = { ", ch);
        for (int k = 0; k < strlen(firstResult); k++)
            printf("%c ", firstResult[k]);
        printf("}\n");
    }

    printf("\n--- FOLLOW sets ---\n");
    for (i = 0; i < n; i++) {
        ch = production[i][0];
        memset(followResult, 0, sizeof(followResult));
        memset(visitedFollow, 0, sizeof(visitedFollow));
        findFollow(ch);
        printf("FOLLOW(%c) = { ", ch);
        for (int k = 0; k < strlen(followResult); k++)
            printf("%c ", followResult[k]);
        printf("}\n");
    }

    return 0;
}

//------------------------------------
// Function to add unique characters
//------------------------------------
void addToResult(char *res, char c) {
    if (!strchr(res, c)) {
        int len = strlen(res);
        res[len] = c;
        res[len + 1] = '\0';
    }
}

//------------------------------------
// Function to find FIRST
//------------------------------------
void findFirst(char c) {
    if (!isupper(c)) { // terminal
        addToResult(firstResult, c);
        return;
    }

    if (visitedFirst[c]) return; // prevent recursion loop
    visitedFirst[c] = 1;

    for (int i = 0; i < n; i++) {
        if (production[i][0] == c) {
            char next = production[i][2];
            if (next == '#')
                addToResult(firstResult, '#');
            else if (!isupper(next))
                addToResult(firstResult, next);
            else
                findFirst(next);
        }
    }
}

//------------------------------------
// Function to find FOLLOW
//------------------------------------
void findFollow(char c) {
    if (visitedFollow[c]) return;
    visitedFollow[c] = 1;

    if (start == c)
        addToResult(followResult, '$');

    for (int i = 0; i < n; i++) {
        for (int j = 2; j < strlen(production[i]); j++) {
            if (production[i][j] == c) {
                char next = production[i][j + 1];

                if (next != '\0') {
                    if (isupper(next)) {
                        memset(firstResult, 0, sizeof(firstResult));
                        memset(visitedFirst, 0, sizeof(visitedFirst));
                        findFirst(next);
                        for (int k = 0; k < strlen(firstResult); k++) {
                            if (firstResult[k] != '#')
                                addToResult(followResult, firstResult[k]);
                        }
                    } else {
                        addToResult(followResult, next);
                    }
                } else if (production[i][0] != c) {
                    findFollow(production[i][0]);
                    for (int k = 0; k < strlen(followResult); k++)
                        addToResult(followResult, followResult[k]);
                }
            }
        }
    }
}
