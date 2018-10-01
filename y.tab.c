#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130304

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
	#include "ast.h"
	#include "hash.h"
	int getLineNumber(void);
	int yylex();
	int yyerror();
	AST_NODE* getAST();
	AST_NODE* root = NULL;
#line 11 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	struct hash_node* symbol;
	struct ast_node* ast;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 39 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define KW_CHAR 257
#define KW_INT 258
#define KW_FLOAT 259
#define KW_IF 260
#define KW_THEN 261
#define KW_ELSE 262
#define KW_WHILE 263
#define KW_READ 264
#define KW_RETURN 265
#define KW_PRINT 266
#define OPERATOR_LE 267
#define OPERATOR_GE 268
#define OPERATOR_EQ 269
#define OPERATOR_OR 270
#define OPERATOR_AND 271
#define OPERATOR_NOT 272
#define TK_IDENTIFIER 273
#define LIT_INTEGER 274
#define LIT_FLOAT 275
#define LIT_CHAR 276
#define LIT_STRING 277
#define TOKEN_ERROR 278
#define TOKEN_UNKNOWN 279
#define OPERATOR_ATTRIB 280
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    1,    1,    2,    2,    2,    3,    3,    3,
    4,    4,    5,    5,    5,    6,    6,    6,    6,    7,
    8,    8,    8,    9,    9,    9,   10,   10,   11,   11,
   11,   11,   11,   11,   11,   11,   11,   11,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,
};
static const short yylen[] = {                            2,
    1,    2,    2,    1,    5,    7,    4,    1,    1,    1,
    2,    1,    3,    1,    0,    3,    3,    1,    1,    6,
    4,    2,    0,    1,    1,    1,    3,    0,    3,    6,
    2,    2,    2,    4,    6,    3,    3,    0,    1,    3,
    3,    3,    3,    3,    2,    3,    3,    3,    3,    3,
    3,    1,    4,    3,    4,    3,
};
static const short yydefred[] = {                         0,
    8,   10,    9,    0,    1,    0,    0,    4,    2,    3,
    0,    0,    0,    0,    0,    0,   24,   25,   26,    0,
   39,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   54,    0,    0,   56,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   50,   51,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   20,   53,
   55,    0,    6,    0,   21,    0,    0,   31,    0,    0,
   32,    0,    0,    0,    0,    0,   13,   11,    0,   36,
    0,    0,    0,    0,   37,    0,    0,   16,   17,    0,
   27,    0,    0,   35,    0,
};
static const short yydgoto[] = {                          4,
    5,    6,    7,   73,   46,   81,    8,   25,   21,   85,
   86,   82,
};
static const short yysindex[] = {                      -170,
    0,    0,    0, -170,    0,  -49, -270,    0,    0,    0,
  -61,  -50, -181, -170,  -50,  -80,    0,    0,    0,  -50,
    0,  459, -100, -244,  -63,   65,  -50,  -70,  -36,  -50,
  -50,  -50,  -50,  -50,  -50,  -50,  -50,  -50,  -50,  -50,
  -21,    5,  267,  -20,    0,  -42,  -28,    0,   28,   28,
   28,   65,   65,   28,   28,  -11,  -11,    0,    0, -181,
 -170,  -50,  -50, -206,  -50,  289,  -56,  267,    0,    0,
    0,  -50,    0, -181,    0,  412,  424,    0,  459,   30,
    0,  434,  -50,  -50,  -46,   17,    0,    0,  267,    0,
  289,  289,  459,  445,    0,  267, -180,    0,    0,   29,
    0,  267,  -50,    0,  459,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   -7,    0,    1,    0,    0,    0,    0,
    0,   37,    0,    0,    0,  370,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   45,   -1,   38,    0,    0,    0,    7,    0,   58,   78,
   98,  387,  405,  115,  350,   21,   41,    0,    0,    0,
   -7,    0,    0,    0,    0,    0,    0,  -57,    0,    0,
    0,    8,    0,   50,    0,    0,  134,    0,  141,  149,
    0,  161,    0,    0,    0,    0,    0,    0,  134,    0,
    0,    0,  178,    0,    0,  -57,   18,    0,    0,    0,
    0,  134,    0,    0,  185,
};
static const short yygindex[] = {                         0,
  107,    0,  -10,   40,   44,  -38,    0,   60,   -5,   27,
  -30,  705,
};
#define YYTABLESIZE 808
static const short yytable[] = {                         12,
   52,   38,   11,   24,   83,   39,   37,   23,   38,   10,
   40,   41,   69,   39,   37,   72,   38,   34,   40,   28,
   48,   39,   37,   36,   38,   35,   40,   45,   42,   20,
   39,   36,   27,   35,   43,   40,   60,   38,   14,   36,
   49,   35,   52,   52,   52,   52,   90,   52,   61,   20,
   24,   13,   98,   99,   74,   71,   84,   40,   97,   52,
   52,   48,   52,   48,   48,   48,   78,   28,   74,   39,
   37,  104,   38,   91,   40,   96,   34,   41,   95,   48,
   48,  102,   48,   49,   49,   49,    1,    2,    3,  103,
   23,   70,   17,   18,   19,    7,   22,   42,   52,   49,
   49,   40,   49,    5,   14,   15,   39,   37,   12,   38,
    9,   40,   52,   88,   47,   87,   40,   40,   48,   40,
   75,   41,  101,   52,   36,    0,   35,    0,    0,    0,
    0,    0,   48,   38,    0,    0,   41,   41,   49,   41,
   33,   42,    0,   48,    0,    0,    0,    0,   18,    0,
    0,    0,   49,    0,    0,   40,   42,   42,   47,   42,
   19,    0,    0,   49,    0,    0,    0,    0,    0,   40,
    0,    0,    0,   47,   47,   41,   47,   29,    0,    0,
   40,    0,    0,    0,   30,    0,    0,    0,    0,   41,
    0,    0,   38,    0,    0,   42,    0,    0,    0,   33,
   41,   15,   16,   17,   18,   19,    0,   18,    0,   42,
    0,    0,   47,    0,    0,    0,    0,    0,    0,   19,
   42,   15,   16,   17,   18,   19,   47,    0,    0,    0,
   30,   31,   32,   33,   34,    0,   29,   47,   30,   31,
   32,   33,   34,   30,    0,    0,   30,   31,   32,   33,
   34,    0,    0,    0,    0,    0,    0,   52,   52,   52,
   52,   52,   52,   52,   52,   52,   52,   52,   52,   52,
   52,   52,    0,   52,   34,   34,   34,   48,   48,   48,
   48,   48,   48,   48,   48,   48,   48,   48,   48,   48,
   48,   48,    0,   48,   38,   38,   38,   49,   49,   49,
   49,   49,   49,   49,   49,   49,   49,   49,   49,   49,
   49,   49,    0,   49,   40,   40,   40,   40,   40,   40,
   40,   40,   40,   40,   40,   40,   40,   40,   40,    0,
   40,   30,   31,   32,   41,   41,   41,   41,   41,   41,
   41,   41,   41,   41,   41,   41,   41,   41,   41,   46,
   41,    0,    0,    0,   42,   42,   42,   42,   42,   42,
   42,   42,   42,   42,   42,   42,   42,   42,   42,   45,
   42,   47,   47,   47,   47,   47,   47,   47,   47,   47,
   47,   47,   47,   47,   47,   47,   43,   47,   20,   68,
   38,   38,   38,   46,    0,   38,    0,   33,   33,   33,
    0,    0,   33,    0,   44,   18,   18,   18,   46,   46,
   18,   46,    0,   45,    0,    0,    0,   19,   19,   19,
    0,    0,   19,    0,    0,    0,    0,    0,   45,    0,
   43,    0,    0,    0,   29,   29,   29,    0,    0,   29,
    0,   30,   30,   30,    0,   43,   30,   46,   44,    0,
    0,    0,    0,   39,   37,    0,   38,    0,   40,    0,
    0,   46,    0,   44,    0,   39,   37,   45,   38,    0,
   40,   36,   46,   35,    0,   39,   37,   92,   38,    0,
   40,   45,    0,   36,   43,   35,   39,   37,    0,   38,
    0,   40,   45,   36,    0,   35,    0,    0,   43,    0,
   39,   37,   44,   38,   36,   40,   35,    0,    0,   43,
    0,    0,    0,    0,    0,    0,   44,    0,   36,    0,
   35,    0,    0,    0,    0,    0,   62,   44,    0,   63,
   64,   65,   66,    0,    0,    0,    0,    0,    0,   67,
    0,    0,    0,    0,    0,    0,   68,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  100,    0,    0,    0,
   15,   16,   17,   18,   19,   80,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   46,   46,   46,   46,
   46,   46,   46,   46,   46,   46,   46,   46,   46,   46,
   46,    0,   46,    0,    0,    0,   45,   45,   45,   45,
   45,   45,   45,   45,   45,   45,    0,    0,    0,   45,
   45,    0,   45,   43,   43,   43,   43,   43,   43,   43,
   43,   43,   43,    0,    0,    0,   43,   43,    0,   43,
    0,   44,   44,   44,   44,   44,   44,   44,   44,   44,
   44,    0,   89,    0,   44,   44,    0,   44,   30,   31,
   32,   33,   34,   62,    0,    0,   63,   64,   65,   66,
   30,   31,   32,   33,   34,    0,   67,    0,    0,    0,
   30,   31,   32,   33,   34,    0,    0,    0,    0,    0,
    0,   30,   31,   32,   33,   34,   22,    0,    0,   26,
    0,    0,    0,    0,   29,   30,   31,   32,   33,   34,
    0,   44,   47,    0,   49,   50,   51,   52,   53,   54,
   55,   56,   57,   58,   59,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   76,   77,    0,   79,
    0,    0,    0,    0,    0,    0,   47,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   93,   94,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  105,
};
static const short yycheck[] = {                         61,
    0,   59,  273,   14,   61,   42,   43,   13,   45,   59,
   47,  112,   43,   42,   43,   44,   45,    0,   47,  100,
    0,   42,   43,   60,   45,   62,   47,   98,  273,  100,
   42,   60,  113,   62,   98,   47,   58,    0,  100,   60,
    0,   62,   42,   43,   44,   45,   77,   47,   44,  100,
   61,  113,   91,   92,   60,   98,  113,    0,   89,   59,
   60,   98,   62,   43,   44,   45,  273,  125,   74,   42,
   43,  102,   45,   44,   47,   59,   59,    0,  125,   59,
   60,  262,   62,   43,   44,   45,  257,  258,  259,   61,
   98,  112,  274,  275,  276,   59,   98,    0,   98,   59,
   60,   44,   62,   59,   98,   98,   42,   43,   59,   45,
    4,   47,  112,   74,    0,   72,   59,   60,   98,   62,
   61,   44,   96,  123,   60,   -1,   62,   -1,   -1,   -1,
   -1,   -1,  112,    0,   -1,   -1,   59,   60,   98,   62,
    0,   44,   -1,  123,   -1,   -1,   -1,   -1,    0,   -1,
   -1,   -1,  112,   -1,   -1,   98,   59,   60,   44,   62,
    0,   -1,   -1,  123,   -1,   -1,   -1,   -1,   -1,  112,
   -1,   -1,   -1,   59,   60,   98,   62,    0,   -1,   -1,
  123,   -1,   -1,   -1,    0,   -1,   -1,   -1,   -1,  112,
   -1,   -1,   59,   -1,   -1,   98,   -1,   -1,   -1,   59,
  123,  272,  273,  274,  275,  276,   -1,   59,   -1,  112,
   -1,   -1,   98,   -1,   -1,   -1,   -1,   -1,   -1,   59,
  123,  272,  273,  274,  275,  276,  112,   -1,   -1,   -1,
  267,  268,  269,  270,  271,   -1,   59,  123,  267,  268,
  269,  270,  271,   59,   -1,   -1,  267,  268,  269,  270,
  271,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,
  260,  261,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,   -1,  273,  257,  258,  259,  257,  258,  259,
  260,  261,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,   -1,  273,  257,  258,  259,  257,  258,  259,
  260,  261,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,   -1,  273,  257,  258,  259,  260,  261,  262,
  263,  264,  265,  266,  267,  268,  269,  270,  271,   -1,
  273,  267,  268,  269,  257,  258,  259,  260,  261,  262,
  263,  264,  265,  266,  267,  268,  269,  270,  271,    0,
  273,   -1,   -1,   -1,  257,  258,  259,  260,  261,  262,
  263,  264,  265,  266,  267,  268,  269,  270,  271,    0,
  273,  257,  258,  259,  260,  261,  262,  263,  264,  265,
  266,  267,  268,  269,  270,  271,    0,  273,  100,  123,
  257,  258,  259,   44,   -1,  262,   -1,  257,  258,  259,
   -1,   -1,  262,   -1,    0,  257,  258,  259,   59,   60,
  262,   62,   -1,   44,   -1,   -1,   -1,  257,  258,  259,
   -1,   -1,  262,   -1,   -1,   -1,   -1,   -1,   59,   -1,
   44,   -1,   -1,   -1,  257,  258,  259,   -1,   -1,  262,
   -1,  257,  258,  259,   -1,   59,  262,   98,   44,   -1,
   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,   -1,
   -1,  112,   -1,   59,   -1,   42,   43,   98,   45,   -1,
   47,   60,  123,   62,   -1,   42,   43,   44,   45,   -1,
   47,  112,   -1,   60,   98,   62,   42,   43,   -1,   45,
   -1,   47,  123,   60,   -1,   62,   -1,   -1,  112,   -1,
   42,   43,   98,   45,   60,   47,   62,   -1,   -1,  123,
   -1,   -1,   -1,   -1,   -1,   -1,  112,   -1,   60,   -1,
   62,   -1,   -1,   -1,   -1,   -1,  260,  123,   -1,  263,
  264,  265,  266,   -1,   -1,   -1,   -1,   -1,   -1,  273,
   -1,   -1,   -1,   -1,   -1,   -1,  123,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  112,   -1,   -1,   -1,
  272,  273,  274,  275,  276,  277,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,  260,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,   -1,  273,   -1,   -1,   -1,  257,  258,  259,  260,
  261,  262,  263,  264,  265,  266,   -1,   -1,   -1,  270,
  271,   -1,  273,  257,  258,  259,  260,  261,  262,  263,
  264,  265,  266,   -1,   -1,   -1,  270,  271,   -1,  273,
   -1,  257,  258,  259,  260,  261,  262,  263,  264,  265,
  266,   -1,  261,   -1,  270,  271,   -1,  273,  267,  268,
  269,  270,  271,  260,   -1,   -1,  263,  264,  265,  266,
  267,  268,  269,  270,  271,   -1,  273,   -1,   -1,   -1,
  267,  268,  269,  270,  271,   -1,   -1,   -1,   -1,   -1,
   -1,  267,  268,  269,  270,  271,   12,   -1,   -1,   15,
   -1,   -1,   -1,   -1,   20,  267,  268,  269,  270,  271,
   -1,   27,   28,   -1,   30,   31,   32,   33,   34,   35,
   36,   37,   38,   39,   40,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   62,   63,   -1,   65,
   -1,   -1,   -1,   -1,   -1,   -1,   72,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   83,   84,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  103,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 280
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,"'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,"':'","';'",
"'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,"'b'",0,"'d'",0,0,0,0,0,0,0,0,0,0,0,"'p'","'q'",0,0,0,0,0,0,0,0,0,"'{'",
0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"KW_CHAR","KW_INT","KW_FLOAT","KW_IF","KW_THEN",
"KW_ELSE","KW_WHILE","KW_READ","KW_RETURN","KW_PRINT","OPERATOR_LE",
"OPERATOR_GE","OPERATOR_EQ","OPERATOR_OR","OPERATOR_AND","OPERATOR_NOT",
"TK_IDENTIFIER","LIT_INTEGER","LIT_FLOAT","LIT_CHAR","LIT_STRING","TOKEN_ERROR",
"TOKEN_UNKNOWN","OPERATOR_ATTRIB",
};
static const char *yyrule[] = {
"$accept : program",
"program : declaration",
"program : program declaration",
"declaration : var_global ';'",
"declaration : function",
"var_global : type TK_IDENTIFIER 'q' literal 'p'",
"var_global : type TK_IDENTIFIER 'q' literal 'p' ':' lit_list",
"var_global : type TK_IDENTIFIER '=' expression",
"type : KW_CHAR",
"type : KW_FLOAT",
"type : KW_INT",
"lit_list : literal lit_list",
"lit_list : literal",
"parameters : expression ',' parameters",
"parameters : expression",
"parameters :",
"print : LIT_STRING ',' print",
"print : expression ',' print",
"print : LIT_STRING",
"print : expression",
"function : type TK_IDENTIFIER 'd' arguments 'b' command",
"arguments : type TK_IDENTIFIER ',' arguments",
"arguments : type TK_IDENTIFIER",
"arguments :",
"literal : LIT_INTEGER",
"literal : LIT_FLOAT",
"literal : LIT_CHAR",
"cmd_list : command ';' cmd_list",
"cmd_list :",
"command : TK_IDENTIFIER '=' expression",
"command : TK_IDENTIFIER 'q' expression 'p' '=' expression",
"command : KW_READ TK_IDENTIFIER",
"command : KW_PRINT print",
"command : KW_RETURN expression",
"command : KW_IF expression KW_THEN command",
"command : KW_IF expression KW_THEN command KW_ELSE command",
"command : KW_WHILE expression command",
"command : '{' cmd_list '}'",
"command :",
"expression : literal",
"expression : expression OPERATOR_LE expression",
"expression : expression OPERATOR_GE expression",
"expression : expression OPERATOR_EQ expression",
"expression : expression OPERATOR_OR expression",
"expression : expression OPERATOR_AND expression",
"expression : OPERATOR_NOT expression",
"expression : expression '<' expression",
"expression : expression '>' expression",
"expression : expression '+' expression",
"expression : expression '-' expression",
"expression : expression '*' expression",
"expression : expression '/' expression",
"expression : TK_IDENTIFIER",
"expression : TK_IDENTIFIER 'q' expression 'p'",
"expression : TK_IDENTIFIER 'd' 'b'",
"expression : TK_IDENTIFIER 'd' parameters 'b'",
"expression : 'd' expression 'b'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 168 "parser.y"

int yyerror(char *msg){

	fprintf(stderr, "Gerofrigolicius Syntax Error at line %d\n", getLineNumber());
	exit(3);

}

AST_NODE* getAST(){

	return root;
}
#line 456 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 2:
#line 67 "parser.y"
	{ root = yyval.ast = astCreate(AST_DEC, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 5:
#line 76 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[-3].symbol, 0, 0, 0, 0); yyval.ast = astCreate(AST_VEC_DECLARATION, 0, 0, yystack.l_mark[-1].ast, 0, 0); }
break;
case 6:
#line 77 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[-5].symbol, 0, 0, 0, 0); yyval.ast = astCreate(AST_VEC_DECLARATION, 0, 0, yystack.l_mark[-3].ast, yystack.l_mark[0].ast, 0); }
break;
case 7:
#line 78 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[-2].symbol, 0, 0, 0, 0); yyval.ast = astCreate(AST_VAR_DECLARATION, 0, 0, yystack.l_mark[0].ast, 0, 0); }
break;
case 11:
#line 88 "parser.y"
	{ yyval.ast = astCreate(AST_LIT_LIST, 0, yystack.l_mark[0].ast, yystack.l_mark[-1].ast, 0, 0); }
break;
case 12:
#line 89 "parser.y"
	{ yyval.ast = astCreate(AST_LIT_LIST, 0, yystack.l_mark[0].ast, 0, 0, 0); }
break;
case 13:
#line 93 "parser.y"
	{ yyval.ast = astCreate(AST_PARAM_LST, 0, yystack.l_mark[0].ast, yystack.l_mark[-2].ast, 0, 0); }
break;
case 14:
#line 94 "parser.y"
	{ yyval.ast = astCreate(AST_PARAM_LST, 0, yystack.l_mark[0].ast, 0, 0, 0); }
break;
case 15:
#line 95 "parser.y"
	{ yyval.ast = 0; }
break;
case 16:
#line 99 "parser.y"
	{ yyval.ast = astCreate(AST_PARAM_LIST, yystack.l_mark[-2].symbol, 0, 0, 0, 0); yyval.ast = astCreate(AST_PARAM_LIST, 0, yystack.l_mark[0].ast, 0, 0, 0); }
break;
case 17:
#line 100 "parser.y"
	{ yyval.ast = astCreate(AST_PARAM_LIST, 0, yystack.l_mark[0].ast, yystack.l_mark[-2].ast, 0, 0); }
break;
case 18:
#line 101 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 20:
#line 106 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[-4].symbol, 0, 0, 0, 0); yyval.ast = astCreate(AST_FUNC_DEC, 0, yystack.l_mark[-5].ast, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0); }
break;
case 21:
#line 110 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[-2].symbol, 0, 0, 0, 0); yyval.ast = astCreate(AST_ARG_LIST, 0, yystack.l_mark[0].ast, yystack.l_mark[-3].ast, 0, 0); }
break;
case 22:
#line 111 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); yyval.ast = astCreate(AST_ARG_LIST, 0, yystack.l_mark[-1].ast, 0, 0, 0); }
break;
case 23:
#line 112 "parser.y"
	{ yyval.ast = 0; }
break;
case 24:
#line 116 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 25:
#line 117 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 26:
#line 118 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 27:
#line 122 "parser.y"
	{ yyval.ast = astCreate(AST_COMMAND_LST, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 28:
#line 123 "parser.y"
	{ yyval.ast = 0; }
break;
case 29:
#line 127 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[-2].symbol, 0, 0, 0, 0); yyval.ast = astCreate(AST_ATTRIB, 0, 0, yystack.l_mark[0].ast, 0, 0); }
break;
case 30:
#line 128 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[-5].symbol, 0, 0, 0, 0); yyval.ast = astCreate(AST_ATTRIB_VEC, 0, 0, yystack.l_mark[-3].ast, yystack.l_mark[0].ast, 0); }
break;
case 31:
#line 130 "parser.y"
	{ yyval.ast = astCreate(AST_READ, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 32:
#line 132 "parser.y"
	{ yyval.ast = astCreate(AST_PRINT, 0, yystack.l_mark[0].ast, 0, 0, 0); }
break;
case 33:
#line 134 "parser.y"
	{ yyval.ast = astCreate(AST_RETURN, 0, yystack.l_mark[0].ast, 0, 0, 0); }
break;
case 34:
#line 136 "parser.y"
	{ yyval.ast = astCreate(AST_IF_THEN, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 35:
#line 137 "parser.y"
	{ yyval.ast = astCreate(AST_IF_THEN_ELSE, 0, yystack.l_mark[-4].ast, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0); }
break;
case 36:
#line 139 "parser.y"
	{ yyval.ast = astCreate(AST_WHILE, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 37:
#line 141 "parser.y"
	{ yyval.ast = astCreate(AST_COMMAND, 0, yystack.l_mark[-1].ast, 0, 0, 0); }
break;
case 38:
#line 143 "parser.y"
	{ yyval.ast = 0; }
break;
case 40:
#line 149 "parser.y"
	{ yyval.ast = astCreate(AST_LE, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 41:
#line 150 "parser.y"
	{ yyval.ast = astCreate(AST_GE, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 42:
#line 151 "parser.y"
	{ yyval.ast = astCreate(AST_EQ, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 43:
#line 152 "parser.y"
	{ yyval.ast = astCreate(AST_OR, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 44:
#line 153 "parser.y"
	{ yyval.ast = astCreate(AST_AND, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 45:
#line 154 "parser.y"
	{ yyval.ast = astCreate(AST_NOT, 0, yystack.l_mark[0].ast, 0, 0, 0); }
break;
case 46:
#line 155 "parser.y"
	{ yyval.ast = astCreate(AST_LT, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 47:
#line 156 "parser.y"
	{ yyval.ast = astCreate(AST_GT, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 48:
#line 157 "parser.y"
	{ yyval.ast = astCreate(AST_ADD, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 49:
#line 158 "parser.y"
	{ yyval.ast = astCreate(AST_SUB, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 50:
#line 159 "parser.y"
	{ yyval.ast = astCreate(AST_MUL, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 51:
#line 160 "parser.y"
	{ yyval.ast = astCreate(AST_DIV, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 52:
#line 161 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 53:
#line 162 "parser.y"
	{ yyval.ast = astCreate(AST_VEC, 0, 0, yystack.l_mark[-1].ast, 0, 0); }
break;
case 55:
#line 164 "parser.y"
	{ yyval.ast = astCreate(AST_FUNCALL, 0, 0, yystack.l_mark[-1].ast, 0, 0); }
break;
case 56:
#line 165 "parser.y"
	{ yyval.ast = astCreate(AST_DB, 0, yystack.l_mark[-1].ast, 0, 0, 0); }
break;
#line 850 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
