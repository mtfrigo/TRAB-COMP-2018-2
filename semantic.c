

#include "semantic.h"

#include "y.tab.h"

int SemanticErrorFlag = 0;

AST* getAST();

void setDeclaration(AST *root)
{
    AST *node;
    AST *dec;

    if(!root) return;

    for(node = root; node; node = node->son[1])
    {

        dec = node->son[0];

        if(dec){

        fprintf(stderr, "[DEBUG] Node type %d; Dec type %d.\n", node->type, dec->type);

            switch(node->type)
            {

                case AST_DEC:
                    setDeclaration(dec);
                    break;

                case AST_VAR_DECLARATION:
                    checkAlreadDeclared(dec, SYMBOL_SCALAR);

                    if(node->son[1])
                    {
                        if(node->son[1]->type == AST_SYMBOL)
                            checkValidDeclaration(node);
                        else if(node->son[1]->type == AST_ADD || node->son[1]->type == AST_SUB || node->son[1]->type == AST_MUL || node->son[1]->type == AST_DIV
                                || node->son[1]->type == AST_LT || node->son[1]->type == AST_GT || node->son[1]->type == AST_LE || node->son[1]->type == AST_GE
                                || node->son[1]->type == AST_EQ || node->son[1]->type == AST_OR || node->son[1]->type == AST_AND || node->son[1]->type == AST_NOT)
                            checkOperands(dec->symbol->datatype, node->son[1]);
                    }
                    break;

                case AST_VEC_DECLARATION:
                    checkAlreadDeclared(dec, SYMBOL_VECTOR);

                    if(node->son[1])
                        if(node->son[1]->type == AST_SYMBOL)
                            if(node->son[1]->symbol->datatype != DATATYPE_CHAR && node->son[1]->symbol->datatype != DATATYPE_INT)
                            {
                                fprintf(stderr, "[SEMANTIC] Index must be INTEGER.\n");
                                SemanticErrorFlag = 1;
                            }

                    if(node->son[2])
                        checkVecDeclaration(dec->symbol->datatype, node->son[2]);

                    break;

                case AST_FUNC_DEC:
                    checkAlreadDeclared(dec, SYMBOL_FUNCTION);

                    setArgDeclaration(node->son[1]);

                    checkCmds(node->son[2]);
                    
                    break;

                default: break;

            }
        }


    }
}

void checkCmds(AST* node)
{
    if(!node) return;

    AST* cmd;

    for(cmd = node->son[0]; cmd; cmd = cmd->son[1])
    {
        if(cmd->son[0])
        {
            switch(cmd->son[0]->type)
            {
                case AST_ATTRIB: 

                    break;

                case AST_RETURN:

                    break;
            }

        }

    }


}

void setArgDeclaration(AST* node)
{
    for(node; node; node = node->son[1])
    {
        switch(node->son[0]->type){
            case AST_INT_TYPE:node->son[0]->symbol->datatype = DATATYPE_INT; break;
            case AST_FLOAT_TYPE:node->son[0]->symbol->datatype = DATATYPE_FLOAT; break;
            case AST_CHAR_TYPE:node->son[0]->symbol->datatype = DATATYPE_CHAR; break;
        }
    }
}

void checkVecDeclaration(int datatype, AST* node)
{

    int i;

    if(!node) return;

    for(i = 0; i < 2; i++)
        checkVecDeclaration(datatype, node->son[i]);

    if(node->type == AST_SYMBOL)
        if(node->symbol->datatype != datatype)
            fprintf(stderr, "[SEMANTIC] Wrong datatype in value (%s) for vector declaration [%d].\n", node->symbol->text, node->symbol->datatype);


}

void checkAlreadDeclared(AST* dec, int SYMBOL_NUMBER)
{
    if(dec->symbol)
    {
        if(dec->symbol->type != SYMBOL_IDENTIFIER)
        {
            fprintf(stderr, "[SEMANTIC] Symbol %s redeclared.\n", dec->symbol->text);
            SemanticErrorFlag = 1;
        }
    }

    //SETTING TYPE AND DATATYPE
    dec->symbol->type = SYMBOL_NUMBER;

    if(dec->type == AST_INT_TYPE || dec->type == AST_CHAR_TYPE)
        dec->symbol->datatype = DATATYPE_INT;
    else
        dec->symbol->datatype = DATATYPE_FLOAT;
}

void checkValidDeclaration(AST* node)
{

    AST* dec = node->son[0];
    AST* value = node->son[1];

    if(dec->symbol->datatype == DATATYPE_INT && !(value->symbol->datatype == DATATYPE_INT || value->symbol->datatype == DATATYPE_CHAR))
    {
        fprintf(stderr, "[SEMANTIC] Symbol %s must be integer.\n", dec->symbol->text);
        SemanticErrorFlag = 1;
    }
    else if(dec->symbol->datatype == DATATYPE_FLOAT && value->symbol->datatype != DATATYPE_FLOAT)
    {
        fprintf(stderr, "[SEMANTIC] Symbol %s must be float.\n", dec->symbol->text);
        SemanticErrorFlag = 1;
    }
}

void checkUndeclared()
{
    hashCheckUndeclared();
}

void checkOperands(int datatype, AST *node)
{
    int i;

    if(!node) return;

    for(i = 0; i < MAX_SONS; i++)
        checkOperands(datatype, node->son[i]);
        
    switch(node->type)
    {
        case AST_SYMBOL: 

            if(node->symbol->type != SYMBOL_SCALAR)
            {
                fprintf(stderr, "[SEMANTIC] Identifier %s must be scalar in arithmetic expression, %d.\n", node->symbol->text, node->symbol->datatype);
                SemanticErrorFlag = 1;
            }


            if(node->symbol->datatype == DATATYPE_INT || node->symbol->datatype == DATATYPE_CHAR)
                node->datatype = AST_DATATYPE_INT;
            else
                node->datatype = AST_DATATYPE_FLOAT;
            break;

        case AST_DB:
        case AST_FUNCALL:
            node->datatype = node->son[0]->datatype;
            break;
        
        case AST_ADD:
        case AST_MUL:
        case AST_DIV:
        case AST_SUB:

            if(node->son[0]->datatype == AST_DATATYPE_BOOL || node->son[1]->datatype == AST_DATATYPE_BOOL )
            {
                fprintf(stderr, "[SEMANTIC] Cannot use boolean in arithmetic expression.\n");
                SemanticErrorFlag = 1;
            }
            else if(node->son[0]->datatype != node->son[1]->datatype)
            {
                fprintf(stderr, "[SEMANTIC] Arithmetic operation cannot mix float and int data.\n");
                SemanticErrorFlag = 1;
            }
            else
            {
                node->datatype = node->son[0]->datatype;
            }

            break;
        case AST_NOT:
            if(node->son[0]->datatype != AST_DATATYPE_BOOL)
            {
                fprintf(stderr, "[SEMANTIC] Only boolean allowed with NOT.\n", node->symbol->text, node->symbol->datatype);
                SemanticErrorFlag = 1;
            }

            node->datatype = AST_DATATYPE_BOOL;
            break;
        case AST_ATTRIB:
            break;
        case AST_LT:
        case AST_GT:
        case AST_LE:
        case AST_GE:
        case AST_EQ:
        case AST_OR:
        case AST_AND:
            fprintf(stderr, "[adsasdasdasd]\n");

            if(node->son[0]->datatype != node->son[1]->datatype)
            {
                fprintf(stderr, "[SEMANTIC] Cannot mix different datatypes in boolean expression.\n");
                SemanticErrorFlag = 1;
            }

            node->datatype = AST_DATATYPE_BOOL;

            break;
    }
}