#ifndef AST_HEADER
#define AST_HEADER

#include "hash.h"

#define FILHOZERO 0
#define FILHOUM 1
#define FILHODOIS 2
#define FILHOTRES 3

//Número máximo de folhas
#define MAX_SONS 4

#define AST_SYMBOL 		1
#define AST_DEC 		2
#define AST_VEC_DECLARATION 	3
#define AST_VAR_DECLARATION 	4
#define AST_CHAR_TYPE 		5
#define AST_FLOAT_TYPE 		6	
#define AST_INT_TYPE 		7
#define AST_LIT_LIST 		8
#define AST_PARAM_LST 		9 
#define AST_FUNC_DEC 		10
#define AST_ARG_LIST 		11
#define AST_COMMAND_LST 	12
#define AST_ATTRIB 		13
#define AST_ATTRIB_VEC 		14
#define AST_PRINT 		15
#define AST_RETURN 		16
#define AST_READ 		17
#define AST_IF_THEN 		18
#define AST_IF_THEN_ELSE 	19
#define AST_WHILE 		20
#define AST_COMMAND 		21
#define AST_LT 			22				
#define AST_GT 			23
#define AST_LE 			24			
#define AST_GE 			25
#define AST_EQ 			26
#define AST_OR 			27
#define AST_AND 		28
#define AST_NOT 		29
#define AST_ADD 		30
#define AST_SUB 		31
#define AST_DIV 		32
#define AST_MUL 		33
#define AST_VEC 		34
#define AST_FUNCALL 		35
#define AST_DB 			36			

typedef struct ast_node{
    int type;
    HASH_NODE *symbol;
    struct ast_node *son[MAX_SONS];
} AST;

AST* astCreate(int type, HASH_NODE *symbol, AST *son0, AST *son1, AST *son2, AST *son3);
void astToFile(AST* node, FILE *fileTree);
void astPrint(int level, AST* node);

#endif
