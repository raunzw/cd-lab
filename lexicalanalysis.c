#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *input;
    int line=1,tno=1;
    char str[50];
    int i=0;
    int flag=0;
    input =fopen("input.txt","r");
    if(!input)
    {
        printf("error in opening the file");
    }
    printf("line\ttoken no\ttoken type\tlexeme\t\n");
    char keywords[15][15]={"while","do","for","return","if","else","include","float","int"};
    char ch;
    while((ch=fgetc(input))!=EOF)
    {
        if(ch==' '||ch=='\t')
        continue;
        if(ch=='\n')
        {
            line++;
            continue;
        }
        if(ch=='/')
        {
            char next=fgetc(input);
            if(next=='/')
            {
                while((ch=fgetc(input))!=EOF&&ch!='\n');
                    line++;
                continue;
            }
            else
            {
                ungetc(next,input);
                printf("%d\t%d\toperator\t%d",line,tno++,ch);
                continue;
            }
        }
        if (ch == '+' || ch == '-' || ch == '*' || ch == '=' ||
            ch == '<' || ch == '>' || ch == '%') {
            printf( "%7d\t%7d\tOperator\t\t%c\n", line, tno++, ch);
            continue;
        }
        if (ch == ';' || ch == '{' || ch == '}' || ch == '(' || ch == ')' ||
            ch == ',' || ch == '[' || ch == ']') {
            printf( "%7d\t%7d\tPunctuation\t\t%c\n", line, tno++, ch);
            continue;
        }
         if (isdigit(ch)) {
            printf("%7d\t%7d\tLiteral\t\t\t%c\n", line, tno++, ch);
            continue;
        }
        if(isalpha(ch)||ch=='_')
        {
            i=0;
            str[i++]=ch;
            while((ch=fgetc(input))!=EOF&&(isalnum(ch)||ch=='_'))
            {
                str[i++]=ch;
            }
            str[i]='\0';
            flag=0;
            for(int j=0;j<=15;j++)
            {
                if(strcmp(str,keywords[j])==0)
                {
                    flag=1;
                    break;
                }
            }
            if (flag == 1)
                printf( "%7d\t%7d\tKeyword\t\t\t%s\n", line, tno++, str);
            else
                printf( "%7d\t%7d\tIdentifier\t\t%s\n", line, tno++, str);

            continue;
        
        }
    }
    fclose(input);
    printf("Lexical analysis complete! Check output.txt\n");
    return 0;
 }
