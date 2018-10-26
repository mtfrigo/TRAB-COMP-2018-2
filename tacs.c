#include "tacs.h"

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2)
{
    TAC* newtac;

    newtac = (TAC*) calloc(1, sizeof(TAC));
    newtac->type = type;
    newtac->res = res;
    newtac->op1 = op1;
    newtac->op2 = op2;
    newtac->prev = 0;
    newtac->next = 0;
    return newtac;
}
void tacPrintSingle(TAC* tac)
{
    if(!tac) return;

    switch(tac->type)
    {
        case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); 
            break;

        case TAC_ADD: fprintf(stderr, "TAC_ADD"); 
            break;

        case TAC_SUB: fprintf(stderr, "TAC_SUB"); 
            break;

        case TAC_DIV: fprintf(stderr, "TAC_DIV"); 
            break;

        case TAC_MUL: fprintf(stderr, "TAC_MUL"); 
            break;

        default: fprintf(stderr, "TAC_UNKNOWN"); 
            break;
    }

    if(tac->res) fprintf(stderr, ", %s", tac->res->text);
        else fprintf(stderr, ", 0");

    if(tac->op1) fprintf(stderr, ", %s", tac->op1->text);
        else fprintf(stderr, ", 0");

    if(tac->op2) fprintf(stderr, ", %s", tac->op2->text);
        else fprintf(stderr, ", 0");

    fprintf(stderr, ")\n");
}
void tacPrintBackwards(TAC* tac)
{
    if(!tac) return;

    tacPrintSingle(tac);
    tacPrintBackwards(tac->prev);
}

// CODE GENERATION

TAC* tacGenerate(AST* node)
{
    int i;
    TAC* result[MAX_SONS];

    if(!node) return 0;

    for(i = 0; i < MAX_SONS; i++)
        result[i] = tacGenerate(node->son[i]);

    switch(node->type)
    {
        case AST_SYMBOL:
            return tacCreate(TAC_SYMBOL, node->symbol, 0,0);
            break;

        case AST_ADD: 
            return tacJoin(tacJoin(result[0], result[1]), tacCreate(TAC_ADD, makeTemp(), result[0]?result[0]->res:0, result[1]?result[1]->res:0));
            break;

        default: 
            return tacJoin(tacJoin(tacJoin(result[0], result[1]), result[2]), result[3]);
            break;
    }

    return 0;
}
TAC* tacJoin(TAC* l1, TAC* l2)
{
    TAC* aux;

    if(!l1) return l2;

    if(!l2) return l1;

    for(aux = l2; aux->prev; aux = aux->prev);

    aux->prev = l1;

    return l2;
}