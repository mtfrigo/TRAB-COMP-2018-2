

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
        
        if(node->type == AST_FUNC_DEC)
        {
            setDeclaration(node->son[2]);
        }

        if(node->type == AST_COMMAND)
        {
            setDeclaration(node->son[0]);
        }

        if(node->type == AST_COMMAND_LST)
        {
            setDeclaration(node->son[0]);
        }

        if(node->type == AST_FUNCALL)
        {
            setDeclaration(node->son[0]);
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
                    }
                    else if(asc->type == AST_LT || asc->type == AST_GT || asc->type == AST_LE || asc->type == AST_GE
                        || asc->type == AST_EQ || asc->type == AST_OR || asc->type == AST_AND || asc->type == AST_NOT
                        || asc->type == AST_ADD || asc->type == AST_SUB || asc->type == AST_MUL || asc->type == AST_DIV)
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
                            !(terc->son[1]->symbol->datatype == DATATYPE_CHAR || terc->son[1]->symbol->datatype == DATATYPE_INT)){
                                fprintf(stderr, "[SEMANTIC] Argument %s invalid in vector %s declaration; expected a integer;\n", terc->son[1]->symbol->text, dec->symbol->text);
                            } 

                            if(dec->symbol->datatype == DATATYPE_FLOAT &&
                            (terc->son[1]->symbol->datatype == DATATYPE_CHAR || terc->son[1]->symbol->datatype == DATATYPE_INT)){
                                fprintf(stderr, "[SEMANTIC] Argument %s invalid in vector %s declaration; expected a float;\n", terc->son[1]->symbol->text, dec->symbol->text);
                            }

                            terc = terc->son[0];
                        }

                        if(dec->symbol->datatype == DATATYPE_INT &&
                        !(terc->son[0]->symbol->datatype == DATATYPE_CHAR || terc->son[0]->symbol->datatype == DATATYPE_INT)){
                            fprintf(stderr, "[SEMANTIC] Argument %s invalid in vector %s declaration; expected a integer;\n", terc->son[0]->symbol->text, dec->symbol->text);
                        } 

                        if(dec->symbol->datatype == DATATYPE_FLOAT &&
                        (terc->son[0]->symbol->datatype == DATATYPE_CHAR || terc->son[0]->symbol->datatype == DATATYPE_INT)){
                            fprintf(stderr, "[SEMANTIC] Argument %s invalid in vector %s declaration; expected a float;\n", terc->son[0]->symbol->text, dec->symbol->text);
                        }


                    }


                    break;
                case AST_ATTRIB:


                    if(dec->symbol->type == SYMBOL_VECTOR )
                    {
                        fprintf(stderr, "[SEMANTIC] Attributing scalar to a vector (%s) type;\n", dec->symbol->text);
                    }
                    else if(dec->symbol->type == SYMBOL_FUNCTION)
                    {
                        fprintf(stderr, "[SEMANTIC] Attributing scalar to a function (%s) type;\n", dec->symbol->text);
                    }
                    else if(asc->type == AST_SYMBOL)
                    {
                        if(asc->symbol->type == SYMBOL_FUNCTION)
                        {
                            fprintf(stderr, "[SEMANTIC] Cannot use function without parameters (%s);\n", asc->symbol->text);
                        }
                    }
                    else if(asc->type == AST_LT || asc->type == AST_GT || asc->type == AST_LE || asc->type == AST_GE
                        || asc->type == AST_EQ || asc->type == AST_OR || asc->type == AST_AND || asc->type == AST_NOT
                        || asc->type == AST_ADD || asc->type == AST_SUB || asc->type == AST_MUL || asc->type == AST_DIV)
                    {
                        checkOperands(dec->symbol->datatype, asc);
                    }

                    break;

                case AST_ATTRIB_VEC:

                    if(dec->symbol->type == SYMBOL_SCALAR)
                    {
                        fprintf(stderr, "[SEMANTIC] Cannot index a scalar variable (%s) ;\n", dec->symbol->text );
                    }
                    else if(dec->symbol->type == SYMBOL_FUNCTION)
                    {
                        fprintf(stderr, "[SEMANTIC] Attributing vector to a function (%s) type;\n", dec->symbol->text);
                    }
                    else if(node->son[2]->type == AST_SYMBOL)
                    {


                        if(node->son[2]->symbol->type == SYMBOL_FUNCTION)
                        {
                            fprintf(stderr, "[SEMANTIC] Cannot use function without parameters (%s);\n", node->son[2]->symbol->text);
                        }
                    }
                    else if(node->son[2]->type == AST_LT || node->son[2]->type == AST_GT || node->son[2]->type == AST_LE || node->son[2]->type == AST_GE
                        || node->son[2]->type == AST_EQ || node->son[2]->type == AST_OR || node->son[2]->type == AST_AND || node->son[2]->type == AST_NOT
                        || node->son[2]->type == AST_ADD || node->son[2]->type == AST_SUB || node->son[2]->type == AST_MUL || node->son[2]->type == AST_DIV)
                    {
                        checkOperands(dec->symbol->datatype, node->son[2]);
                    }

                    break;



                default: break;

            }
        }
    }


}

void checkDeclaration(AST* dec, AST* asc)
{
    if(dec->symbol->datatype == DATATYPE_INT && !(asc->symbol->datatype == DATATYPE_INT || asc->symbol->datatype == DATATYPE_CHAR))
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


    
    switch(node->type)
    {
        case AST_SYMBOL: 

            if(node->symbol->type != SYMBOL_SCALAR && node->symbol->type != SYMBOL_FUNCTION )
            {
                fprintf(stderr, "[SEMANTIC] Identifier %s must be scalar in arithmetic expression, %d.\n", node->symbol->text, node->symbol->datatype);
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
        case AST_ATTRIB:
            break;
        case AST_LT:
        case AST_GT:
        case AST_LE:
        case AST_GE:
        case AST_EQ:
        case AST_OR:
        case AST_AND:

            if(node->son[0]->datatype != node->son[1]->datatype)
            {
                fprintf(stderr, "[SEMANTIC] Cannot mix different datatypes in boolean expression.\n");
            }

            node->datatype = AST_DATATYPE_BOOL;

            break;
    }
}