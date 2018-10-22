#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int yyparse(void);
int yylex(void);
void hashPrint(void);
void printToken(int);
int isRunning(void);
void initMe(void);
void checkUndeclared();
void setDeclaration(AST* node);
int getLineNumber(void);
void astToFile(AST* node, FILE *fileTree);
void astPrint(int level, AST* node);
AST* getAST(void);

extern char *yytext;
extern FILE *yyin;
extern int running;
extern int lineNumber;

int main(int argc, char** argv)
{
	FILE *outputFile;
	int result;

	if(argc < 3)
	{
		printf("Call: ./%s <input> <output>\n", argv[0]);

		exit(1);
	}

	if ((yyin = fopen(argv[1], "r")) == 0)
	{
		fprintf(stderr, "Cannot open file %s\n", argv[1]);

		exit(2);
	}

	if ((outputFile = fopen(argv[2], "w")) == 0)
	{
		fprintf(stderr, "Cannot open file %s\n", argv[1]);

		exit(2);
	}

	initMe();

	result = yyparse();

	if( result == 0 )
	{
		fprintf(stderr, "Hash table of the input file: \n");
		hashPrint();
		fprintf(stderr, "\nSyntactical tree for the input file: \n");
		astPrint(0, getAST());
		astToFile(getAST(), outputFile);

		fprintf(stderr, "\nSource code OK!\n");

		checkUndeclared();
		setDeclaration(getAST());
		//fprintf(stderr, "\nSource code generated in '%s' file.\n", argv[2]);

		exit(0);
	}
	else
	{
		fprintf(stderr, "ERROR parsing the source code at line %d\n", getLineNumber());

		exit(3);
	}
}

