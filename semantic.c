

#include "semantic.h"

int SemanticErrorFlag = 0;

void setDeclaration(AST *root)
{
    AST *node;
    AST *dec;

    for(node = root; node; node = node->son[1])
    {
        dec = node->son[0];
        if(dec)
        {
            switch(dec->type)
            {
                case AST_VAR_DECLARATION:
                    if(dec->symbol)
                    if(dec->symbol->type != SYMBOL_IDENTIFIER)
                    {
                        fprintf(stderr, "Symbol %s redeclared.\n", dec->symbol->text);
                        SemanticErrorFlag = 1;
                    }
                    dec->symbol->type = SYMBOL_SCALAR;
                    if(dec->son[0]->type == AST_INT_TYPE ||
                        dec->son[0]->type == AST_CHAR_TYPE)
                        {
                            dec->symbol->datatype = DATATYPE_INT;
                        }
                        else
                        {
                            dec->symbol->datatype = DATATYPE_FLOAT;
                        }
                    break;

                case AST_FUNC_DEC: break;

                default: break;

            }
        }
    }


}

void checkUndeclared()
{
    hashCheckUndeclared();
}

void checkOperands(AST *node)
{
    int i;

    if(node == 0) return;

    for(i = 0; i < MAX_SONS; i++)
    {
        checkOperands(node->son[i]);
    }

    switch(node->type)
    {
        case AST_SYMBOL: 

            if(node->symbol->type != SYMBOL_SCALAR &&
                node->symbol->type != SYMBOL_LITINT)
                {
                    fprintf(stderr, "Identifier %s must be scalar in arithmetic expression.\n", node->symbol->text);
                    SemanticErrorFlag = 1;
                }

            if(node->symbol->datatype == DATATYPE_INT ||
               node->symbol->datatype == DATATYPE_CHAR)
               {
                    node->datatype = AST_DATATYPE_INT;
               }
               else
               {
                    node->datatype = AST_DATATYPE_FLOAT;
               }
               break;
        case AST_ADD:
        case AST_MUL:
        case AST_DIV:
        case AST_SUB:
            if(node->son[0]->type == AST_LT ||
                node->son[0]->type == AST_GT ||
                node->son[0]->type == AST_GE ||
                node->son[0]->type == AST_LE ||
                node->son[0]->type == AST_EQ ||
                node->son[0]->type == AST_OR ||
                node->son[0]->type == AST_AND || 
                node->son[1]->type == AST_LT ||
                node->son[1]->type == AST_GT ||
                node->son[1]->type == AST_GE ||
                node->son[1]->type == AST_LE ||
                node->son[1]->type == AST_EQ ||
                node->son[1]->type == AST_OR ||
                node->son[1]->type == AST_AND )
                {
                    fprintf(stderr, "Invalid operand in arithmetic expression.\n");
                    SemanticErrorFlag = 1;
                }
                
                if(node->son[0]->datatype != node->son[1]->datatype)
                {
                    fprintf(stderr, "Arithmetic operation cannot mix float and int data.\n");
                    SemanticErrorFlag = 1;
                }
                else
                {
                    node->datatype = node->son[0]->datatype;
                }
            break;
        case AST_ATTRIB:
            break;
    }
}