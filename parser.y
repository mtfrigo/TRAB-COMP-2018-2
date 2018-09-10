%{
	#include <stdio.h>
	#include <stdlib.h>
	int getLineNumber(void);
	int yylex();
	int yyerror();
%}

%union {
	int intValue;
	float floatValue;
	char *stringValue;
	char *identValue;
	char charValue;
	struct hash_node* symbol;
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
%token<identValue> TK_IDENTIFIER
%token<intValue> LIT_INTEGER
%token<floatValue> LIT_FLOAT
%token<charValue> LIT_CHAR
%token<stringValue> LIT_STRING
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
	| KW_THEN cmd
	| KW_ELSE cmd
	| atrib
	| type 'd' param 'b' '{' block
	| KW_WHILE 'd' expr 'b' '{' block ';'
	| KW_WHILE expr '{' block ';'
	| TK_IDENTIFIER '=' expr ';'
	| TK_IDENTIFIER expr '=' expr ';'
	| KW_PRINT print ';'
	| KW_READ TK_IDENTIFIER ';'
	| KW_RETURN expr ';'
	| ';'
	| '{' block
	;


print : LIT_STRING print
	| ',' print
	| TK_IDENTIFIER print
	| expr print
	|
	;

block : cmdlist block
	| '}'
	;

atrib : type '=' expr ';'
	| type 'q' expr 'p' array ';'
	| type '=' "'" LIT_CHAR "'" ';'
	| type '=' LIT_CHAR ';'
	;

array : ':' array
	| expr array
	|
	;

type : KW_INT TK_IDENTIFIER
	| KW_FLOAT TK_IDENTIFIER
	| KW_CHAR TK_IDENTIFIER
	;

param : expr param
	| ',' param
	| type param
	|
	;

expr : LIT_INTEGER
	| LIT_FLOAT
	| LIT_STRING
	| TK_IDENTIFIER
	| expr '.' expr
	| expr '+' expr
	| expr '-' expr
	| expr '=' expr
	| expr '*' expr
	| expr '/' expr
	| expr '<' expr
	| expr '>' expr
	| expr OPERATOR_AND expr
	| expr OPERATOR_GE expr
	| expr OPERATOR_LE expr
	| expr OPERATOR_EQ expr
	| OPERATOR_NOT expr
	| expr OPERATOR_OR expr
	| 'q' expr 'p'
	| 'd' expr 'b'
	| TK_IDENTIFIER 'q' expr 'p'
	| TK_IDENTIFIER 'd' param 'b'
	;

%%

int yyerror(char *msg){

	fprintf(stderr, "Gerofrigolicius Syntax Error at line %d\n", getLineNumber());
	exit(3);

}
