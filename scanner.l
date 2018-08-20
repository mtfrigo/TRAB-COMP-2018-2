%{

#include "token.h"
#include "hash.h"

int running = 1;
int lineNumber = 1;

%}

%%

"char"							{ return KW_CHAR; }
"int"							{ return KW_INT; }
"float"							{ return KW_FLOAT; }
"if"							{ return KW_IF; }
"then"							{ return KW_THEN; }
"else"							{ return KW_ELSE; }
"while"							{ return KW_WHILE; }
"read"							{ return KW_READ; }
"return"						{ return KW_RETURN; }
"print"							{ return KW_PRINT; }
"<="							{ return OPERATOR_LE; }
">="							{ return OPERATOR_GE; }
"=="							{ return OPERATOR_EQ; }
"or"							{ return OPERATOR_OR; }
"and"							{ return OPERATOR_AND; }
"not"							{ return OPERATOR_NOT; }
[-,;:dbqp+*\{\}/<>=!&$#]		{ return yytext[0]; }
[0-9].[0-9]						{ hashInsert(0, yytext); return LIT_FLOAT; }
[ACE-OR-Zace-or-z]?				{ hashInsert(0, yytext); return LIT_CHAR; }
\"[-ACE-OR-Zace-or-z_0-9]*\"						{ hashInsert(0, yytext); return LIT_STRING; }
[-ACE-OR-Zace-or-z_][-ACE-OR-Zace-or-z_0-9]*	{ return TK_IDENTIFIER; }
[0-9]+							{ hashInsert(0, yytext); return LIT_INTEGER; }

"//".*	
[ \t]
\n								{  ++lineNumber; }
.								{ return TOKEN_ERROR; }

%%

int yywrap()
{
	running = 0;
	return 1;
}
