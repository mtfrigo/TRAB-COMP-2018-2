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


cmd	: 
	  KW_INT TK_IDENTIFIER  '=' expr ';'
	| KW_INT TK_IDENTIFIER 'q' TK_IDENTIFIER 'p' array ';'
	| KW_INT TK_IDENTIFIER 'q' LIT_INTEGER 'p' array ';'

	| KW_FLOAT TK_IDENTIFIER '=' expr ';'
	| KW_FLOAT TK_IDENTIFIER 'q' TK_IDENTIFIER 'p' array ';'
	| KW_FLOAT TK_IDENTIFIER 'q' LIT_INTEGER 'p' array ';'

	| KW_CHAR TK_IDENTIFIER '=' expr ';'
	| KW_CHAR TK_IDENTIFIER 'q' TK_IDENTIFIER 'p' array ';'
	| KW_CHAR TK_IDENTIFIER 'q' LIT_INTEGER 'p' array ';'

	| TK_IDENTIFIER 'q' TK_IDENTIFIER 'p' '=' expr ';'
	| TK_IDENTIFIER '=' expr ';'

	| KW_INT TK_IDENTIFIER 'd' param 'b' '{' cmdlist '}'

	| KW_PRINT TK_IDENTIFIER 'q' TK_IDENTIFIER 'p' ';'
	| KW_PRINT TK_IDENTIFIER 'q' LIT_INTEGER 'p' ';'
	| KW_PRINT param ';'

	| KW_READ TK_IDENTIFIER ';'
	| KW_RETURN expr ';'

	| KW_WHILE 'd' expr 'b' '{' cmdlist '}' ';'
	| KW_WHILE expr '{' cmdlist '}' ';'
	
	| TK_IDENTIFIER '=' TK_IDENTIFIER 'd' param 'b' ';'

	| KW_IF expr KW_THEN cmd 
	| KW_IF expr KW_THEN '{' cmdlist '}'  

	| KW_IF 'd' expr 'b' KW_THEN cmd 
	| KW_IF 'd' expr 'b' KW_THEN '{' cmdlist '}' 

	| KW_IF expr KW_THEN cmd KW_ELSE 
	| KW_IF expr KW_THEN cmd KW_ELSE '{' cmdlist '}' 
	| KW_IF expr KW_THEN '{' cmdlist '}' KW_ELSE
	| KW_IF expr KW_THEN '{' cmdlist '}' KW_ELSE '{' cmdlist '}'

	| KW_IF 'd' expr 'b' KW_THEN cmd KW_ELSE 
	| KW_IF 'd' expr 'b' KW_THEN cmd KW_ELSE '{' cmdlist '}' 
	| KW_IF 'd' expr 'b' KW_THEN '{' cmdlist '}' KW_ELSE
	| KW_IF 'd' expr 'b' KW_THEN '{' cmdlist '}' KW_ELSE '{' cmdlist '}'

	| ';'

	| '{' cmdlist '}' ';'

	
	;



array : ':' array
	| expr array
	|
	;

param : KW_INT TK_IDENTIFIER param
	| KW_FLOAT TK_IDENTIFIER param
	| KW_CHAR TK_IDENTIFIER param

	| KW_INT TK_IDENTIFIER 'q' LIT_INTEGER 'p' param
	| KW_FLOAT TK_IDENTIFIER 'q' LIT_INTEGER 'p' param
	| KW_CHAR TK_IDENTIFIER 'q' LIT_INTEGER 'p' param

	| KW_INT TK_IDENTIFIER 'q' TK_IDENTIFIER 'p' param
	| KW_FLOAT TK_IDENTIFIER 'q' TK_IDENTIFIER 'p' param
	| KW_CHAR TK_IDENTIFIER 'q' TK_IDENTIFIER 'p' param
	
	| expr param

	| ',' param
	|
	;

expr : LIT_INTEGER
	| LIT_FLOAT
	| LIT_STRING
	| LIT_CHAR
	| TK_IDENTIFIER
	| expr '+' expr
	| expr '-' expr
	| expr '*' expr
	| expr '/' expr
	| expr '<' expr
	| expr '>' expr
	| expr OPERATOR_EQ expr
	| expr OPERATOR_OR expr
	| expr OPERATOR_AND expr
	| expr OPERATOR_GE expr
	| expr OPERATOR_LE expr
	| OPERATOR_NOT expr
	| 'd' expr 'b'
	;
	


%%

int yyerror(char *msg){

	fprintf(stderr, "Gerofrigolicius Syntax Error at line %d\n", getLineNumber());
	exit(3);

}
