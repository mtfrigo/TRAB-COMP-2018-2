%{
	#include <stdio.h>
	#include <stdlib.h>
%}

%union {
	int value;
}

%token KW_CHAR
%token KW_INT
%token KW_FLOAT
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_READ
%token KW_RETURN
%token KW_PRINT
%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_OR
%token OPERATOR_AND
%token OPERATOR_NOT
%token TK_IDENTIFIER
%token<value>  LIT_INTEGER
%token LIT_FLOAT
%token LIT_CHAR
%token LIT_STRING
%token TOKEN_ERROR
%token TOKEN_UNKNOWN
%token OPERATOR_ATTRIB

%%

program : cmdlist
	;

cmdlist : cmd cmdlist
	|
	;

cmd	: KW_IF expr cmd
	| TK_IDENTIFIER OPERATOR_ATTRIB expr ';'
	;

expr	: LIT_INTEGER	{ fprintf(stderr, "Achei LIT_INT", $1); }
	| TK_IDENTIFIER
	| expr '+' expr
	| expr '-' expr
	| expr '=' expr
	| expr '*' expr
	| TK_IDENTIFIER '(' expr ')'
	| '(' expr ')'
	;

%%

int yyerror(char *msg){

	fprintf(stderr, "Gerofrigolicius Syntax Error at line %d\n", getLineNumber());
	exit(3);

}
