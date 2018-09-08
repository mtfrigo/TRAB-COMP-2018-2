#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

int yylex(void);
void hashPrint(void);
int isRunning(void);
void initMe(void);

extern char *yytext;
extern FILE *yyin;
extern int running;
extern int lineNumber;

int main (int argc, char **argv)
{
	int tok;

	if (argc < 2) 
	{
		fprintf(stderr, "Call: a.out file_name\n");
		exit(1);
	}

	if ((yyin = fopen(argv[1], "r")) == 0)
	{
		fprintf(stderr, "Cannot open file \%s\"\n", argv[1]);
		exit(2);
	}

	initMe();

	while(isRunning())
	{
		tok = yylex();

		if(!isRunning())
			break;

		fprintf(stderr, "[%d, ", lineNumber);
		if (tok < 256)
			fprintf(stderr, "%c, %d]\n", tok, tok);
		else
			switch(tok)
			{
				case KW_CHAR: fprintf(stderr,"KW_CHAR, %d]\n", KW_CHAR); break;
				case KW_INT: fprintf(stderr,"KW_INT, %d]\n", KW_INT); break;
                case KW_FLOAT: fprintf(stderr,"KW_FLOAT, %d]\n", KW_FLOAT); break;
                case KW_IF: fprintf(stderr,"KW_IF, %d]\n", KW_IF); break;
                case KW_THEN: fprintf(stderr,"KW_THEN, %d]\n", KW_THEN); break;
                case KW_ELSE: fprintf(stderr,"KW_ELSE, %d]\n", KW_ELSE); break;
                case KW_WHILE: fprintf(stderr,"KW_WHILE, %d]\n", KW_WHILE); break;
                case KW_READ: fprintf(stderr,"KW_READ, %d]\n", KW_READ); break;
                case KW_RETURN: fprintf(stderr,"KW_RETURN, %d]\n", KW_RETURN); break;
                case KW_PRINT: fprintf(stderr,"KW_PRINT, %d]\n", KW_PRINT); break;
                case OPERATOR_LE: fprintf(stderr,"OPERATOR_LE, %d]\n", OPERATOR_LE); break;
                case OPERATOR_GE: fprintf(stderr,"OPERATOR_GE, %d]\n", OPERATOR_GE); break;
                case OPERATOR_EQ: fprintf(stderr,"OPERATOR_EQ, %d]\n", OPERATOR_EQ); break;
                case OPERATOR_OR: fprintf(stderr,"OPERATOR_OR, %d]\n", OPERATOR_OR); break;
                case OPERATOR_AND: fprintf(stderr,"OPERATOR_AND, %d]\n", OPERATOR_AND); break;
                case OPERATOR_NOT: fprintf(stderr,"OPERATOR_NOT, %d]\n", OPERATOR_NOT); break;
				case LIT_INTEGER: fprintf(stderr,"LIT_INTEGER, %d]\n", LIT_INTEGER); break;
                case LIT_FLOAT: fprintf(stderr,"LIT_FLOAT, %d]\n", LIT_FLOAT); break;
                case LIT_CHAR: fprintf(stderr,"LIT_CHAR, %d]\n", LIT_CHAR); break;
                case LIT_STRING: fprintf(stderr,"LIT_STRING, %d]\n", LIT_STRING); break;
                case TK_IDENTIFIER: fprintf(stderr,"TK_IDENTIFIER, %d]\n", TK_IDENTIFIER); break;
				case TOKEN_ERROR: fprintf(stderr,"TOKEN_ERROR, %d]\n", TOKEN_ERROR); break;
				default: fprintf(stderr,"ERROR: UNKNOWN LOKO]\n"); break;
			}
	}	

	hashPrint();

	exit(0);

}