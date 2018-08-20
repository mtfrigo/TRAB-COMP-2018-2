#include <stdio.h>
#include <stdlib.h>
#include "token.h"

int yylex(void);
int isRunning(void);
void initMe(void);

extern char *yytext;
extern FILE *yyin;

int main(int argc, char** argv)
{
    FILE *output = 0;

    int tok = 0;
    int answer = 0;
    int nota = 0;
    int i = 0;

    if(argc < 3)
    {
        printf("Call: %s input.txt output.txt \n", argv[0]);
        exit(1);
    }

    if((yyin = fopen(argv[1], "r")) == 0)
    {
        printf("Error: Cannot open file %s... \n", argv[1]);
        exit(2);
    }

    if((output = fopen(argv[2],"r")) == 0)
    {
        printf("Error: Cannot open file %s... \n", argv[2]);
        exit(2);
    }

    initMe();

    while(isRunning())
    {
        tok = yylex();

        if(!isRunning())
        {
            break;
        }

        fscanf(output,"%d",&answer);

        if(tok == answer)
        {
            fprintf(stderr, "%d = OK (%s)\n", i, yytext);
            ++nota;
        }
        else
        {
            fprintf(stderr, "\n%d = ERROR (%s, %d, %d)\n ", i, yytext, tok, answer);
        }

        ++i;
    }

    fprintf(stderr, "\nGRADE %d, %.2f%% of right results\n", nota, ((float)nota/i) * 100);

    return 0;
}