
#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"

void setDeclaration(AST *node);
void checkUndeclared();
void checkOperands(AST *node);

#endif