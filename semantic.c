

#include "semantic.h"

#include "y.tab.h"

int SemanticErrorFlag = 0;

void setDeclaration(AST *root)
{
    AST *node;
    AST *dec;
    AST *asc;
    AST *terc;

    for(node = root; node; node = node->son[1])
    {

        if(node->type == AST_DEC)
        {
            setDeclaration(node->son[0]);
            node = node->son[1];
        }

        dec = node->son[0];
        asc = node->son[1];
        
        if(dec)
        {

            switch(node->type)
            {
                case AST_VAR_DECLARATION:

                    if(dec->symbol){
                        if(dec->symbol->type != SYMBOL_IDENTIFIER)
                        {
                            fprintf(stderr, "[SEMANTIC] Symbol %s redeclared.\n", dec->symbol->text);
                            SemanticErrorFlag = 1;
                        }
                    }
                    
                    dec->symbol->type = SYMBOL_SCALAR;

                    fprintf(stderr, "[DEBUG] dec->symbol->type = %d.\n", dec->symbol->type);

                    if(dec->type == AST_INT_TYPE || dec->type == AST_CHAR_TYPE)
                    {
                        dec->symbol->datatype = DATATYPE_INT;
                    }
                    else
                    {
                        dec->symbol->datatype = DATATYPE_FLOAT;
                    }

                    if(asc->type == AST_SYMBOL)
                    {
                        checkDeclaration(dec, asc);

                        fprintf(stderr, "entrou;  %s.\n", dec->symbol->text);
                    }
                    else
                    {
                        checkOperands(dec->symbol->datatype, asc);
                    }



                    break;

                case AST_FUNC_DEC: 
                    
                    if(dec->symbol)
                    {
                        if(dec->symbol->type != SYMBOL_IDENTIFIER)
                        {
                            fprintf(stderr, "[SEMANTIC] Symbol %s redeclared.\n", dec->symbol->text);
                            SemanticErrorFlag = 1;
                        }
                    }

                    dec->symbol->type = SYMBOL_FUNCTION;

                    if(dec->type == AST_INT_TYPE || dec->type == AST_CHAR_TYPE)
                    {
                        dec->symbol->datatype = DATATYPE_INT;
                    }
                    else
                    {
                        dec->symbol->datatype = DATATYPE_FLOAT;
                    }


                 break;

                case AST_VEC_DECLARATION:

                    if(dec->symbol)
                    {
                        if(dec->symbol->type != SYMBOL_IDENTIFIER)
                        {
                            fprintf(stderr, "[SEMANTIC] Symbol %s redeclared.\n", dec->symbol->text);
                            SemanticErrorFlag = 1;
                        }
                    }

                    dec->symbol->type = SYMBOL_VECTOR;
                    
                    if(dec->type == AST_INT_TYPE || dec->type == AST_CHAR_TYPE)
                    {
                        dec->symbol->datatype = DATATYPE_INT;
                    }
                    else
                    {
                        dec->symbol->datatype = DATATYPE_FLOAT;
                    }

                    if(node->son[2])
                    {
                        terc = node->son[2];

                        while(terc->type == terc->son[0]->type)
                        {
                            if(dec->symbol->datatype == DATATYPE_INT &&
                            !(terc->son[1]->symbol->type == LIT_CHAR || terc->son[1]->symbol->type == LIT_INTEGER)){
                                fprintf(stderr, "[SEMANTIC] Argument %s invalid in vector %s declaration; expected a integer;\n", terc->son[1]->symbol->text, dec->symbol->text);
                            } 

                            if(dec->symbol->datatype == DATATYPE_FLOAT &&
                            (terc->son[1]->symbol->type == LIT_CHAR || terc->son[1]->symbol->type == LIT_INTEGER)){
                                fprintf(stderr, "[SEMANTIC] Argument %s invalid in vector %s declaration; expected a float;\n", terc->son[1]->symbol->text, dec->symbol->text);
                            }

                            terc = terc->son[0];
                        }

                        if(dec->symbol->datatype == DATATYPE_INT &&
                        !(terc->son[0]->symbol->type == LIT_CHAR || terc->son[0]->symbol->type == LIT_INTEGER)){
                            fprintf(stderr, "[SEMANTIC] Argument %s invalid in vector %s declaration; expected a integer;\n", terc->son[0]->symbol->text, dec->symbol->text);
                        } 

                        if(dec->symbol->datatype == DATATYPE_FLOAT &&
                        (terc->son[0]->symbol->type == LIT_CHAR || terc->son[0]->symbol->type == LIT_INTEGER)){
                            fprintf(stderr, "[SEMANTIC] Argument %s invalid in vector %s declaration; expected a float;\n", terc->son[0]->symbol->text, dec->symbol->text);
                        }


                    }


                    break; 

                default: break;

            }
        }
    }


}

void checkDeclaration(AST* dec, AST* asc)
{
    if(dec->symbol->datatype == DATATYPE_INT && !(asc->symbol->datatype == DATATYPE_INT || asc->symbol->datatype == DATATYPE_INT))
    {
        fprintf(stderr, "[SEMANTIC] Symbol %s must be integer.\n", dec->symbol->text);

    }
    else if(dec->symbol->datatype == DATATYPE_FLOAT && asc->symbol->datatype != DATATYPE_FLOAT)
    {
        fprintf(stderr, "[SEMANTIC] Symbol %s must be float.\n", dec->symbol->text);
    }
}

void checkUndeclared()
{
    hashCheckUndeclared();
}

void checkOperands(int datatype, AST *node)
{
    int i;

    if(node == 0) return;

    for(i = 0; i < MAX_SONS; i++)
    {
        checkOperands(datatype, node->son[i]);
    }


    fprintf(stderr, "node type  %d\n", node->type);
    switch(node->type)
    {
        case AST_SYMBOL: 

            if(node->symbol->type != SYMBOL_SCALAR)
            {
                fprintf(stderr, "Identifier %s must be scalar in arithmetic expression.\n", node->symbol->text);
                SemanticErrorFlag = 1;
            }


            if(node->symbol->datatype == DATATYPE_INT || node->symbol->datatype == DATATYPE_CHAR)
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
        case AST_DB:

             fprintf(stderr, "Datatype %d. Node datatype %d\n", node->symbol->datatype, node->datatype);
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