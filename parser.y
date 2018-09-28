%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "ast.h"
	#include "hash.h"
	int getLineNumber(void);
	int yylex();
	int yyerror();
%}

%union {
	struct hash_node* symbol;
	struct ast_node* ast;
}

%type<ast> dec
%type<ast> ldec
%type<ast> program
%type<ast> exp
%type<ast> cmd
%type<ast> lcmd
%type<ast> read
%type<ast> block
%type<ast> reset
%type<ast> l_func_args
%type<ast> lpe
%type<ast> print
%type<ast> reset_func_par
%type<ast> l_func_par
%type<ast> func_header
%type<ast> func_dec
%type<ast> func_args
%type<ast> pe
%type<ast> func_par
%type<ast> lit
%type<ast> vet_dec

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
%token<symbol> TK_IDENTIFIER
%token<symbol> LIT_INTEGER
%token<symbol> LIT_FLOAT
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING
%token TOKEN_ERROR
%token TOKEN_UNKNOWN
%token OPERATOR_ATTRIB


%start program
%right '='
%left OPERATOR_NOT OPERATOR_AND OPERATOR_OR
%left OPERATOR_EQ OPERATOR_GE OPERATOR_LE '>' '<'
%left '+' '-'
%left '*' '/'
%right KW_IF KW_THEN KW_ELSE
%%

program 
	: declaration
	| program declaration
	;

declaration
	: var_global ';'
	| function
	;

var_global
	: type TK_IDENTIFIER 'q' literal 'p'
	| type TK_IDENTIFIER 'q' literal 'p' ':' lit_list
	| type TK_IDENTIFIER '=' expression
	;

type
	: KW_CHAR
	| KW_FLOAT
	| KW_INT
	;

lit_list
	: literal lit_list
	| literal
	;

parameters
	: expression ',' parameters
	| expression
	;

print
	: LIT_STRING ',' print
	| expression ',' print
	| LIT_STRING
	| expression
	;

function
	: type TK_IDENTIFIER 'd' arguments 'b' command
	;

arguments
	: type TK_IDENTIFIER ',' arguments
	| type TK_IDENTIFIER
	|
	;

literal
	: LIT_INTEGER
	| LIT_FLOAT
	| LIT_CHAR
	;

cmd_list
	: command ';' cmd_list 
	|
	;

command
	: TK_IDENTIFIER '=' expression
	| TK_IDENTIFIER 'q' expression 'p' '=' expression

	| KW_READ TK_IDENTIFIER

	| KW_PRINT print 
	
	| KW_RETURN expression

	| KW_IF expression KW_THEN command 
	| KW_IF expression KW_THEN command KW_ELSE command

	| KW_WHILE expression command

	| '{' cmd_list '}'

	|

	;

expression 
	: literal
	| expression OPERATOR_LE expression 
 	| expression OPERATOR_GE expression
 	| expression OPERATOR_EQ expression
 	| expression OPERATOR_OR expression  
	| expression OPERATOR_AND expression 
	| OPERATOR_NOT expression 
	| expression '<' expression
	| expression '>' expression
	| expression '+' expression
	| expression '-' expression
	| expression '*' expression
	| expression '/' expression
	| TK_IDENTIFIER 
	| TK_IDENTIFIER 'q' expression 'p'
	| TK_IDENTIFIER 'd' 'b'
	| TK_IDENTIFIER 'd' parameters 'b'
	| 'd' expression 'b'
	;
%%

int yyerror(char *msg){

	fprintf(stderr, "Gerofrigolicius Syntax Error at line %d\n", getLineNumber());
	exit(3);

}
