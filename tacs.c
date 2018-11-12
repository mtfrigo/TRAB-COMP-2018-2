#include "tacs.h"

TAC* makeBinOp(int type, TAC* result0, TAC* result1);
TAC* makeMove(int type, TAC* result0, TAC* result1);
TAC* makeIfThen(TAC* result0, TAC* result1);
TAC* makeWhile(TAC* result0, TAC* result1);
TAC* makeFuncall(TAC* result0, TAC* result1);
TAC* makePrint(TAC* result0, TAC* result1);
TAC* makeFundec(TAC* result0, TAC* result1, TAC* result2);
TAC* makeIfThenElse(TAC* result0, TAC* result1, TAC* result2);

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

    if(tac->type == TAC_SYMBOL) return;

    fprintf(stderr, "TAC ("); 
    switch(tac->type)
    {
        case TAC_ADD: fprintf(stderr, "TAC_ADD"); 
            break;

        case TAC_SUB: fprintf(stderr, "TAC_SUB"); 
            break;

        case TAC_DIV: fprintf(stderr, "TAC_DIV"); 
            break;

        case TAC_MUL: fprintf(stderr, "TAC_MUL"); 
            break;

        case TAC_LT: fprintf(stderr, "TAC_LT"); 
            break;

        case TAC_GT: fprintf(stderr, "TAC_GT"); 
            break;

        case TAC_LE: fprintf(stderr, "TAC_LE"); 
            break;

        case TAC_GE: fprintf(stderr, "TAC_GE"); 
            break;

        case TAC_EQ: fprintf(stderr, "TAC_EQ"); 
            break;

        case TAC_OR: fprintf(stderr, "TAC_OR"); 
            break;

        case TAC_AND: fprintf(stderr, "TAC_AND"); 
            break;

        case TAC_BEGINFUN: fprintf(stderr, "TAC_BEGINFUN"); 
            break;

        case TAC_ENDFUN: fprintf(stderr, "TAC_ENDFUN"); 
            break;

        case TAC_RETURN: fprintf(stderr, "TAC_RET"); 
            break;

        case TAC_IFZ: fprintf(stderr, "TAC_IFZ"); 
            break;

        case TAC_JUMP: fprintf(stderr, "TAC_JUMP"); 
            break;

        case TAC_CALL: fprintf(stderr, "TAC_CALL"); 
            break;

        case TAC_ARG: fprintf(stderr, "TAC_ARG"); 
            break;

        case TAC_PRINT: fprintf(stderr, "TAC_PRINT"); 
            break;

        case TAC_READ: fprintf(stderr, "TAC_READ"); 
            break;

        case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); 
            break;

        case TAC_MOVE: fprintf(stderr, "TAC_MOVE"); 
            break;

        case TAC_WHILE: fprintf(stderr, "TAC_WHILE"); 
            break;

        case TAC_VEC_WR: fprintf(stderr, "TAC_VEC_WR"); 
            break;

        case TAC_VEC_RD: fprintf(stderr, "TAC_VEC_RD"); 
            break;

        case TAC_FUNCALL: fprintf(stderr, "TAC_FUNCALL"); 
            break;

        case TAC_BUFFER: fprintf(stderr, "TAC_BUFFER"); 
            break;

        case TAC_ARG_LIST: fprintf(stderr, "TAC_ARG_LIST"); 
            break;

        case TAC_PARAM_LIST: fprintf(stderr, "TAC_PARAM_LIST"); 
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
            return makeBinOp(TAC_ADD, result[0], result[1]);
            break;

        case AST_SUB: 
            return makeBinOp(TAC_SUB, result[0], result[1]);
            break;

        case AST_MUL: 
            return makeBinOp(TAC_MUL, result[0], result[1]);
            break;

        case AST_DIV: 
            return makeBinOp(TAC_DIV, result[0], result[1]);
            break;

        case AST_LT: 
            return makeBinOp(TAC_LT, result[0], result[1]);
            break;

        case AST_GT: 
            return makeBinOp(TAC_GT, result[0], result[1]);
            break;

        case AST_LE: 
            return makeBinOp(TAC_LE, result[0], result[1]);
            break;

        case AST_GE: 
            return makeBinOp(TAC_GE, result[0], result[1]);
            break;

        case AST_EQ: 
            return makeBinOp(TAC_EQ, result[0], result[1]);
            break;

        case AST_OR: 
            return makeBinOp(TAC_OR, result[0], result[1]);
            break;

        case AST_RETURN: 
            return makeBinOp(TAC_RETURN, result[0], result[1]);
            break;

        case AST_READ: 
            return tacCreate(TAC_READ, result[0]->res, 0, 0);
            break;

        case AST_AND: 
            return makeBinOp(TAC_AND, result[0], result[1]);
            break;

        case AST_ATTRIB:
            return makeMove(TAC_MOVE, result[0], result[1]);
            break;

        case AST_ATTRIB_VEC:
            return makeMove(TAC_VEC_WR, result[0], result[1]);
            break;

        case AST_VEC:
            return tacCreate(TAC_VEC_RD, makeTemp(), result[0]->res, result[1]->res);
            break;

        case AST_IF_THEN: 
            return makeIfThen(result[0], result[1]);
            break;

        case AST_IF_THEN_ELSE: 
            return makeIfThenElse(result[0], result[1], result[2]);
            break;

        case AST_WHILE: 
            return makeWhile(result[0], result[1]);
            break;

        case AST_FUNCALL: 
            return makeFuncall(result[0], result[1]);
            break;

        case AST_PRINT: 
            return makePrint(result[0], result[1]);
            break;

        case AST_PARAM_LST: 
            return tacJoin(tacCreate(TAC_PARAM_LIST, result[0]?result[0]->res:0, 0, 0),result[1]);
            break; 

        case AST_ARG_LIST: 
            return tacJoin(tacCreate(TAC_ARG_LIST, result[0]?result[0]->res:0, 0, 0),result[1]);
            break; 

        case AST_FUNC_DEC: 
            return makeFundec(result[0], result[1], result[2]);
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

TAC* tacReverse(TAC* tac)
{
    if(!tac) return 0;

    for(; tac->prev; tac = tac->prev)
        tac->prev->next = tac;

    return tac;
}

void tacPrintForward(TAC* tac)
{
    if(!tac) return;

    tacPrintSingle(tac);
    tacPrintForward(tac->next);
}

TAC* makeBinOp(int type, TAC* result0, TAC* result1)
{
    return tacJoin(tacJoin(result0, result1), tacCreate(type, makeTemp(), result0?result0->res:0, result1?result1->res:0));
}

TAC* makeMove(int type, TAC* result0, TAC* result1)
{
    return tacJoin(tacJoin(result0, result1), tacCreate(type, result0?result0->res:0, result0?result0->res:0, result1?result1->res:0));
}

TAC* makeIfThen(TAC* result0, TAC* result1)
{
    TAC* newIfTac = 0;
    TAC* newLabelTac = 0;
    HASH_NODE* newLabel = 0;

    newLabel = makeLabel();
    newIfTac = tacCreate(TAC_IFZ, newLabel, result0?result0->res:0, 0);
    newLabelTac = tacCreate(TAC_LABEL, newLabel, 0, 0);

    return tacJoin(tacJoin(tacJoin(result0, newIfTac), result1), newLabelTac);
}

TAC* makeIfThenElse(TAC* result0, TAC* result1, TAC* result2)
{
    TAC* skipTac = 0;
    TAC* elseLabelTac = 0;
    
    TAC* ifTac = 0;
    TAC* ifLabelTac = 0;
    
    HASH_NODE* ifLabel = makeLabel();
    HASH_NODE* elseLabel = makeLabel();

    skipTac = tacCreate(TAC_JUMP, elseLabel, 0, 0);
    elseLabelTac = tacCreate(TAC_LABEL, elseLabel, 0, 0);

    ifTac = tacCreate(TAC_IFZ, ifLabel, result0?result0->res:0, 0);
    elseLabelTac = tacCreate(TAC_LABEL, ifLabel, 0, 0);

    return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(result0, ifTac), result1), skipTac), ifLabelTac), result2), elseLabelTac);
}

TAC* makeWhile(TAC* result0, TAC* result1)
{
    TAC* whileTac = 0;
    TAC* labelWhileTac = 0;

    TAC* jumpLabelTac = 0;
    TAC* jumpTac = 0;

    HASH_NODE* whileLabel = 0;
    HASH_NODE* jumpLabel = 0;

    whileLabel = makeLabel();
    jumpLabel = makeLabel();

    jumpTac = tacCreate(TAC_JUMP, whileLabel, 0, 0);
    whileTac = tacCreate(TAC_IFZ, jumpLabel, result0?result0->res:0, 0);

    labelWhileTac = tacCreate(TAC_LABEL, whileLabel, 0, 0);
    jumpLabelTac = tacCreate(TAC_LABEL, jumpLabel, 0, 0);

    return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(labelWhileTac, result0), whileTac), result1), jumpTac), jumpLabelTac);
}

TAC* makeFuncall(TAC* result0, TAC* result1)
{
    TAC* bufferTac = 0;
    TAC* funcallTac = 0;

    bufferTac = tacCreate(TAC_BUFFER, result0, 0, 0);
    bufferTac->res = makeTemp();

    funcallTac = tacCreate(TAC_FUNCALL, bufferTac->res, result0->res, 0);

    return tacJoin(tacJoin(tacJoin(result0, funcallTac), result1), bufferTac);
}

TAC* makePrint(TAC* result0, TAC* result1)
{
    TAC* bufferTac = 0;
    TAC* printTac = 0;

    bufferTac = tacCreate(TAC_BUFFER, result0, 0, 0);
    bufferTac->res = makeTemp();

    printTac = tacCreate(TAC_PRINT, bufferTac->res, 0, 0);

    return tacJoin(tacJoin(tacJoin(result0, printTac), result1), bufferTac);
}

TAC* makeFundec(TAC* result0, TAC* result1, TAC* result2)
{
    TAC* beginTac = 0;
    TAC* endTac = 0;

    beginTac = tacCreate(TAC_BEGINFUN, result0, 0, 0);
    endTac = tacCreate(TAC_ENDFUN, result0, 0, 0);

    return tacJoin(tacJoin(tacJoin(beginTac, result1), result2 ), endTac);
    
    return tacJoin(tacJoin(beginTac, result1), endTac);
}

