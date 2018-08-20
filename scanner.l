%{

#include "token.h"
#include "hash.h"

<<<<<<< HEAD
int running;
int lineNumber;
=======
char *s;
char buffer[STRING_SIZE];
int running = 1;
int lineNumber = 1;
>>>>>>> 49d79d64dc1e036990279122051a561790e67eb2

%}


%x COMMENT
%x STRING

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
[0-9]*							{ hashInsert(3, yytext); return LIT_INTEGER; }
[-,;:dbqp+*\{\}/<>=!&$#]				{ return yytext[0]; }

\"		{ BEGIN(STRING); s = buffer;	}
<STRING>\\n	{ *s++ = '\n';   	}
<STRING>\\\"	{ *s++ = '\"';   	}
<STRING>\"	{	*s = 0;
		 	BEGIN 0;
		  //printf("found ");
		  //puts(buffer);
		  	yytext = buffer;
		  	hashInsert(2, yytext);
		  	return LIT_STRING;
		}
<STRING>\[-ACE-OR-Zace-or-z_0-9]*	{ *s++ = yytext[0];  }

<STRING>.	{ *s++ = *yytext;   	}


[-ACE-OR-Zace-or-z_0-9]*		{ hashInsert(4, yytext); return TK_IDENTIFIER; }
\'[-ACE-OR-Zace-or-z]?\'		{ hashInsert(1, yytext); return LIT_CHAR; }
[0-9]*\.[0-9]*				{ hashInsert(0, yytext); return LIT_FLOAT; }



"//".*

"/*" 		{ BEGIN(COMMENT); }
<COMMENT>"*/" 	{ BEGIN(INITIAL); }
<COMMENT>"\n" 	{ ++lineNumber;   }
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
<<<<<<< HEAD

void initMe(void){
	running = 1;
	lineNumber = 1;
	hashInit();
}
=======
>>>>>>> 49d79d64dc1e036990279122051a561790e67eb2
