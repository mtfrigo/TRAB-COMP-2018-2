%{
	#include "ast.h"
	#include "hash.h"
	int getLineNumber(void);
	int yylex();
	int yyerror();
	AST_NODE* getAST();
	AST_NODE* root = NULL;
%}

%union {
	struct hash_node* symbol;
	struct ast_node* ast;
}

%type<ast> program
%type<ast> declaration
%type<ast> var_global
%type<ast> type
%type<ast> lit_list
%type<ast> parameters
%type<ast> print
%type<ast> function
%type<ast> arguments
%type<ast> literal
%type<ast> cmd_list
%type<ast> command
%type<ast> expression

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
	| program declaration 					{ root = $$ = astCreate(AST_DEC, 0, $1, $2, 0, 0); }
	;

declaration
	: var_global ';'
	| function
	;

var_global
	: type TK_IDENTIFIER 'q' literal 'p' 			{ $$ = astCreate(AST_SYMBOL, $2, 0, 0, 0, 0); $$ = astCreate(AST_VEC_DECLARATION, 0, 0, $4, 0, 0); }
	| type TK_IDENTIFIER 'q' literal 'p' ':' lit_list 	{ $$ = astCreate(AST_SYMBOL, $2, 0, 0, 0, 0); $$ = astCreate(AST_VEC_DECLARATION, 0, 0, $4, $7, 0); }
	| type TK_IDENTIFIER '=' expression 			{ $$ = astCreate(AST_SYMBOL, $2, 0, 0, 0, 0); $$ = astCreate(AST_VAR_DECLARATION, 0, 0, $4, 0, 0); }
	;

type
	: KW_CHAR						
	| KW_FLOAT						
	| KW_INT						
	;

lit_list
	: literal lit_list					{ $$ = astCreate(AST_LIT_LIST, 0, $2, $1, 0, 0); }
	| literal						{ $$ = astCreate(AST_LIT_LIST, 0, $1, 0, 0, 0); }
	;

parameters
	: expression ',' parameters				{ $$ = astCreate(AST_PARAM_LST, 0, $3, $1, 0, 0); }
	| expression						{ $$ = astCreate(AST_PARAM_LST, 0, $1, 0, 0, 0); }
	| { $$ = 0; }
	;

print
	: LIT_STRING ',' print					{ $$ = astCreate(AST_PARAM_LIST, $1, 0, 0, 0, 0); $$ = astCreate(AST_PARAM_LIST, 0, $3, 0, 0, 0); }
	| expression ',' print					{ $$ = astCreate(AST_PARAM_LIST, 0, $3, $1, 0, 0); }
	| LIT_STRING						{ $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }	
	| expression						
	;

function
	: type TK_IDENTIFIER 'd' arguments 'b' command			{ $$ = astCreate(AST_SYMBOL, $2, 0, 0, 0, 0); $$ = astCreate(AST_FUNC_DEC, 0, $1, $4, $6, 0); }
	;

arguments
	: type TK_IDENTIFIER ',' arguments				{ $$ = astCreate(AST_SYMBOL, $2, 0, 0, 0, 0); $$ = astCreate(AST_ARG_LIST, 0, $4, $1, 0, 0); }
	| type TK_IDENTIFIER						{ $$ = astCreate(AST_SYMBOL, $2, 0, 0, 0, 0); $$ = astCreate(AST_ARG_LIST, 0, $1, 0, 0, 0); }
	| { $$ = 0; }
	;

literal
	: LIT_INTEGER 							{ $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
	| LIT_FLOAT							{ $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
	| LIT_CHAR							{ $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
	;

cmd_list
	: command ';' cmd_list						{ $$ = astCreate(AST_COMMAND_LST, 0, $1, $3, 0, 0); }	
	| { $$ = 0; }
	;

command
	: TK_IDENTIFIER '=' expression					{ $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); $$ = astCreate(AST_ATTRIB, 0, 0, $3, 0, 0); }
	| TK_IDENTIFIER 'q' expression 'p' '=' expression		{ $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); $$ = astCreate(AST_ATTRIB_VEC, 0, 0, $3, $6, 0); }

	| KW_READ TK_IDENTIFIER						{ $$ = astCreate(AST_READ, $2, 0, 0, 0, 0); }

	| KW_PRINT print						{ $$ = astCreate(AST_PRINT, 0, $2, 0, 0, 0); } 
	
	| KW_RETURN expression						{ $$ = astCreate(AST_RETURN, 0, $2, 0, 0, 0); }

	| KW_IF expression KW_THEN command				{ $$ = astCreate(AST_IF_THEN, 0, $2, $4, 0, 0); } 
	| KW_IF expression KW_THEN command KW_ELSE command		{ $$ = astCreate(AST_IF_THEN_ELSE, 0, $2, $4, $6, 0); }

	| KW_WHILE expression command					{ $$ = astCreate(AST_WHILE, 0, $2, $3, 0, 0); }

	| '{' cmd_list '}'						{ $$ = astCreate(AST_COMMAND, 0, $2, 0, 0, 0); }

	| { $$ = 0; }

	;

expression 
	: literal
	| expression OPERATOR_LE expression				{ $$ = astCreate(AST_LE, 0, $1, $3, 0, 0); } 
 	| expression OPERATOR_GE expression				{ $$ = astCreate(AST_GE, 0, $1, $3, 0, 0); }
 	| expression OPERATOR_EQ expression				{ $$ = astCreate(AST_EQ, 0, $1, $3, 0, 0); }
 	| expression OPERATOR_OR expression  				{ $$ = astCreate(AST_OR, 0, $1, $3, 0, 0); }
	| expression OPERATOR_AND expression 				{ $$ = astCreate(AST_AND, 0, $1, $3, 0, 0); }
	| OPERATOR_NOT expression 					{ $$ = astCreate(AST_NOT, 0, $2, 0, 0, 0); }
	| expression '<' expression					{ $$ = astCreate(AST_LT, 0, $1, $3, 0, 0); }
	| expression '>' expression					{ $$ = astCreate(AST_GT, 0, $1, $3, 0, 0); }
	| expression '+' expression					{ $$ = astCreate(AST_ADD, 0, $1, $3, 0, 0); }
	| expression '-' expression					{ $$ = astCreate(AST_SUB, 0, $1, $3, 0, 0); }
	| expression '*' expression					{ $$ = astCreate(AST_MUL, 0, $1, $3, 0, 0); }
	| expression '/' expression					{ $$ = astCreate(AST_DIV, 0, $1, $3, 0, 0); }
	| TK_IDENTIFIER							{ $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); } 
	| TK_IDENTIFIER 'q' expression 'p'				{ $$ = astCreate(AST_VEC, 0, 0, $3, 0, 0); }
	| TK_IDENTIFIER 'd' 'b'
	| TK_IDENTIFIER 'd' parameters 'b'				{ $$ = astCreate(AST_FUNCALL, 0, 0, $3, 0, 0); }
	| 'd' expression 'b'						{ $$ = astCreate(AST_DB, 0, $2, 0, 0, 0); }
	;
%%

int yyerror(char *msg){

	fprintf(stderr, "Gerofrigolicius Syntax Error at line %d\n", getLineNumber());
	exit(3);

}

AST_NODE* getAST(){

	return root;
}
