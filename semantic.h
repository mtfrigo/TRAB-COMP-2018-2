
#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"

extern int SemanticErrorFlag;


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