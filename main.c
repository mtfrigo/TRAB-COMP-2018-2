#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "semantic.h"
#include "tacs.h"
#include "frigenco.h"

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
	FILE *outputFile, *output2;
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

	if ((outputFile = fopen(argv[2], "w+")) == 0)
	{
		fprintf(stderr, "Cannot open file %s\n", argv[2]);

		exit(2);
	}
	//output2 = stdout;

	initMe();

	result = yyparse();

	if(result == 0)
	{
		fprintf(stderr, "Hash table of the input file: \n");
		hashPrint();
		fprintf(stderr, "\nSyntactical tree for the input file: \n");
		astPrint(0, getAST());
		//astToFile(getAST(), output2);

		fprintf(stderr, "\nSource code OK!\n");

		checkUndeclared();
		fprintf(stderr, "OK UNDECLARED\n");
		setDeclaration(getAST());

		if(SemanticErrorFlag == 1)
		{
			fprintf(stderr, "At least one semantic error!\n");
			exit(4);
		}

		fprintf(stderr, "\nNo semantic errors!\n");

		TAC *tac_reverse = tacReverse(tacGenerate(getAST()));
		tacPrintForward(tac_reverse);

		fprintf(stderr, "\nGerando assembly...\n");
		gen_assembly(tac_reverse, outputFile, getAST());


		exit(0);
	}
	else
	{
		fprintf(stderr, "ERROR parsing the source code at line %d\n", getLineNumber());

		exit(3);
	}
	
}

