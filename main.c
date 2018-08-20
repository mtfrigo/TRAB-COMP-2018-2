#include <stdio.h>
#include <stdlib.h>
#include "token.h"

int yylex(void);
void hashInit(void);
void hashPrint(void);
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

	hashInit();
	while(running)
	{

		tok = yylex();

		if(!running)
			break;

		fprintf(stderr, "[%d, ", lineNumber);
		if (tok < 256)
			fprintf(stderr, "%c]\n", tok);
		else
			switch(tok)
			{
				case KW_CHAR: fprintf(stderr,"KW_CHAR]\n"); break;
				case KW_INT: fprintf(stderr,"KW_INT]\n"); break;
                case KW_FLOAT: fprintf(stderr,"KW_FLOAT]\n"); break;
                case KW_IF: fprintf(stderr,"KW_IF]\n"); break;
                case KW_THEN: fprintf(stderr,"KW_THEN]\n"); break;
                case KW_ELSE: fprintf(stderr,"KW_ELSE]\n"); break;
                case KW_WHILE: fprintf(stderr,"KW_WHILE]\n"); break;
                case KW_READ: fprintf(stderr,"KW_READ]\n"); break;
                case KW_RETURN: fprintf(stderr,"KW_RETURN]\n"); break;
                case KW_PRINT: fprintf(stderr,"KW_PRINT]\n"); break;
                case OPERATOR_LE: fprintf(stderr,"OPERATOR_LE]\n"); break;
                case OPERATOR_GE: fprintf(stderr,"OPERATOR_GE]\n"); break;
                case OPERATOR_EQ: fprintf(stderr,"OPERATOR_EQ]\n"); break;
                case OPERATOR_OR: fprintf(stderr,"OPERATOR_OR]\n"); break;
                case OPERATOR_AND: fprintf(stderr,"OPERATOR_AND]\n"); break;
                case OPERATOR_NOT: fprintf(stderr,"OPERATOR_NOT]\n"); break;
				case LIT_INTEGER: fprintf(stderr,"LIT_INTEGER]\n"); break;
                case LIT_FLOAT: fprintf(stderr,"LIT_FLOAT]\n"); break;
                case LIT_CHAR: fprintf(stderr,"LIT_CHAR]\n"); break;
                case LIT_STRING: fprintf(stderr,"LIT_STRING]\n"); break;
                case TK_IDENTIFIER: fprintf(stderr,"IDENTIFIER]\n"); break;
				case TOKEN_ERROR: fprintf(stderr,"ERROR: UNKNOWN]\n"); break;
				default: fprintf(stderr,"ERROR: UNKNOWN LOKO]\n"); break;
			}
	}	

	hashPrint();

	exit(0);

}