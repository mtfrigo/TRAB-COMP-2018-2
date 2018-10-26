
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

#endif