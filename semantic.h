
#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"

typedef struct list_func_declaration
{
	AST* ast_node;
 	struct list_func_declaration* next;
} LIST_FUNC_DECL;

LIST_FUNC_DECL* listFuncDecl;

extern int SemanticErrorFlag;

void listFuncDeclInsert(LIST_FUNC_DECL** listFuncDecl, AST* node);
void setDeclaration(AST *node);
void checkUndeclared();
void checkDeclaration(AST* dec, AST* asc);
void checkOperands(int datatype, AST *node);
void checkAlreadDeclared(AST* dec, int SYMBOL_NUMBER);
void checkVecDeclaration(int datatype, AST* node);
void checkValidDeclaration(AST* node);
void setArgDeclaration(AST* node);
void checkCmds(AST* node);
void checkReturn(int datatype, AST* node);
void checkFuncall(AST* node);

#endif
