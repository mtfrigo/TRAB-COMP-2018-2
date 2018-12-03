#if !defined(GENCO_H)
#define GENCO_H

#include <stdio.h>
#include <stdlib.h>
#include "tacs.h"
#include "hash.h"
#include "ast.h"

void gen_assembly(TAC*node, FILE* output);

#endif
