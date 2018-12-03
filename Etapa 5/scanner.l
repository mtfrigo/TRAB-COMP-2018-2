
%{

#include "y.tab.h"
#include "hash.h"
#include "ast.h"

char *s;
char buffer[STRING_SIZE];

int running;
int lineNumber;

%}

%x COMMENT
%x STRING

%%

"<-"							{ return OPERATOR_ATTRIB; }
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
[0-9]*							{ yylval.symbol = hashInsert(LIT_INTEGER, yytext); 
								   return LIT_INTEGER; }
[-,;:dbqp+*\{\}/<>=!&$#]		{ return yytext[0]; }

\"								{ BEGIN(STRING); s = buffer;	}
<STRING>\\n						{ *s++ = '\n';   	}
<STRING>\\\"					{ *s++ = '\"';   	}
<STRING>\"						{	*s = 0;
									BEGIN 0;
								//printf("found ");
								//puts(buffer);
									yytext = buffer;
									yylval.symbol = hashInsert(LIT_STRING, yytext);
									return LIT_STRING;
								}
<STRING>\[-ACE-OR-Zace-or-z_0-9]*	{ *s++ = yytext[0];  }

<STRING>.	{ *s++ = *yytext;   	}


[-ACE-OR-Zace-or-z_0-9]*		{ yylval.symbol = hashInsert(TK_IDENTIFIER, yytext); 
								   return TK_IDENTIFIER; }
\'[-ACE-OR-Zace-or-z]?\'		{ yylval.symbol = hashInsert(LIT_CHAR, yytext);
								   return LIT_CHAR; }
[0-9]*\.[0-9]*					{ yylval.symbol = hashInsert(LIT_FLOAT, yytext); 
								   return LIT_FLOAT; }



"//".*

"/*" 							{ BEGIN(COMMENT); }
<COMMENT>"*/" 					{ BEGIN(INITIAL); }
<COMMENT>"\n" 					{ ++lineNumber;   }
<COMMENT>.
	
[ \t]
"\n" 							{  ++lineNumber; }
.								{ return TOKEN_ERROR; }

%%

int isRunning(void){
	return running;
}

int getLineNumber(void){
	return lineNumber;
}

int yywrap()
{
	running = 0;
	return 1;
}

void initMe(void){
	running = 1;
	lineNumber = 1;
	hashInit();
}
