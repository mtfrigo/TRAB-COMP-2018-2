

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

        //fprintf(stderr, "[DEBUG] Node type %d; Dec type %d.\n", node->type, dec->type);

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

                    checkReturn(dec->symbol->datatype, node->son[2]->son[0]);

                    checkCmds(node->son[2]);
                    
                    break;

                default: break;

            }
        }


    }
}

void checkReturn(int datatype, AST* node)
{
    if(!node) return;

    AST* son = node->son[0];

    if(son)
    {
        if(son->type != AST_RETURN)
            checkReturn(datatype, node->son[1]);
        else
        {
            if(son->son[0]->type == AST_SYMBOL)
            {
                if(son->son[0]->symbol->datatype != datatype)
                    fprintf(stderr, "[SEMANTIC] Function returning worng datatype.\n");
            }
            else if(son->son[0]->type == AST_ADD || son->son[0]->type == AST_SUB || son->son[0]->type == AST_MUL || son->son[0]->type == AST_DIV)
                    checkOperands(datatype, son->son[0]);
            else if(son->son[0]->type == AST_LT || son->son[0]->type == AST_GT || son->son[0]->type == AST_LE || son->son[0]->type == AST_GE
                    || son->son[0]->type == AST_EQ || son->son[0]->type == AST_OR || son->son[0]->type == AST_AND || son->son[0]->type == AST_NOT)
            {
                fprintf(stderr, "[SEMANTIC] Cannot attribute bool to a variable.\n");
                SemanticErrorFlag = 1;
            }
            else if(son->son[0]->type == AST_FUNCALL)
            {
                if(son->son[0]->son[0]->symbol->datatype != datatype)
                {
                    fprintf(stderr, "[SEMANTIC] Return datatype dont match with function.\n");
                    SemanticErrorFlag = 1;
                }
                checkFuncall(son->son[0]);
            }
            
        }
    }

    

}

void checkCmd(AST* node)
{
    AST* son0;
    AST* son1;
    AST* son2;

    son0 =  node->son[0];
    son1 =  node->son[1];
    son2 =  node->son[2];

    if(son0)
    switch(node->type)
    {
        case AST_ATTRIB: 

            //fprintf(stderr,"[ATRIB] %s (type = %d) = %s (type = %d);\n", son0->symbol->text,son0->symbol->datatype,son1->symbol->text,son1->symbol->datatype);

            if(son0->symbol->type == SYMBOL_VECTOR )
            {
                fprintf(stderr, "[SEMANTIC] Attributing scalar to a vector (%s) type;\n", son0->symbol->text);
                SemanticErrorFlag = 1;
            }
            else if(son1)
            {
                if(son1->type == AST_SYMBOL)
                {
                    if(son1->symbol->type == SYMBOL_FUNCTION)
                    {
                        fprintf(stderr, "[SEMANTIC] Cannot use function without parameters (%s);\n", son1->symbol->text);
                        SemanticErrorFlag = 1;
                    }
                    else if(son1->symbol->type == SYMBOL_SCALAR)
                    {
                        if(son1->symbol->datatype != son0->symbol->datatype)
                        {
                            if(son0->symbol->datatype == 1)
                                fprintf(stderr, "[SEMANTIC] Expecting INTEGER datatype.\n");
                            else if(son0->symbol->datatype == 3)
                                fprintf(stderr, "[SEMANTIC] Expecting FLOAT datatype.\n");
                            
                            SemanticErrorFlag = 1;
                        }
                    }
                }
                else if(son1->type == AST_ADD || son1->type == AST_SUB || son1->type == AST_MUL || son1->type == AST_DIV)
                    checkOperands(son0->symbol->datatype, son1);
                else if(son1->type == AST_LT || son1->type == AST_GT || son1->type == AST_LE || son1->type == AST_GE
                        || son1->type == AST_EQ || son1->type == AST_OR || son1->type == AST_AND || son1->type == AST_NOT)
                    {
                        fprintf(stderr, "[SEMANTIC] Cannot attribute bool to a variable.\n");
                        SemanticErrorFlag = 1;
                    }
                else if(son1->type == AST_FUNCALL)
                {
                    if(son1->son[0]->symbol->datatype != son0->symbol->datatype)
                    {
                        fprintf(stderr, "[SEMANTIC] Datatype dont match for attribution.\n");
                        SemanticErrorFlag = 1;
                    }

                    checkFuncall(son1);
                }
            }
            break;
        
        case AST_ATTRIB_VEC:

            if(son0->symbol->type == SYMBOL_SCALAR || son0->symbol->type == SYMBOL_FUNCTION )
            {
                fprintf(stderr, "[SEMANTIC] Cannot index a scalar variable (%s);\n", son0->symbol->text);
                SemanticErrorFlag = 1;
            }

            if(son1)
            {
                if(son1->type == AST_SYMBOL)
                {
                    if(son1->symbol->datatype != DATATYPE_CHAR && son1->symbol->datatype != DATATYPE_INT)
                    {
                        fprintf(stderr, "[SEMANTIC] Index must be INTEGER.\n");
                        SemanticErrorFlag = 1;
                    }
                }
            }

            if(son2)
            {
                if(son2->type == AST_SYMBOL)
                {
                    if(son2->symbol->type == SYMBOL_FUNCTION)
                    {
                        fprintf(stderr, "[SEMANTIC] Cannot use function without parameters (%s);\n", son2->symbol->text);
                        SemanticErrorFlag = 1;
                    }
                    else if(son2->symbol->type == SYMBOL_SCALAR)
                    {
                        if(son2->symbol->datatype != son0->symbol->datatype)
                        {
                            if(son0->symbol->datatype == DATATYPE_INT)
                                fprintf(stderr, "[SEMANTIC] Expecting INTEGER datatype.\n");
                            else if(son0->symbol->datatype == DATATYPE_FLOAT)
                                fprintf(stderr, "[SEMANTIC] Expecting FLOAT datatype.\n");
                            
                            SemanticErrorFlag = 1;
                        }
                    }
                }
                else if(son2->type == AST_ADD || son2->type == AST_SUB || son2->type == AST_MUL || son2->type == AST_DIV)
                    checkOperands(son0->symbol->datatype, son2);
                else if(son2->type == AST_LT || son2->type == AST_GT || son2->type == AST_LE || son2->type == AST_GE
                        || son2->type == AST_EQ || son2->type == AST_OR || son2->type == AST_AND || son2->type == AST_NOT)
                    {
                        fprintf(stderr, "[SEMANTIC] Cannot attribute bool to a variable.\n");
                        SemanticErrorFlag = 1;
                    }
                else if(son2->type == AST_FUNCALL)
                {
                    if(son2->son[0]->symbol->datatype != son0->symbol->datatype)
                    {
                        fprintf(stderr, "[SEMANTIC] Datatype dont match for attribution.\n");
                        SemanticErrorFlag = 1;
                    }
                    checkFuncall(son2->son[0]);
                }
            }

            break;

        case AST_WHILE:
        case AST_IF_THEN:

            if(son0->type == AST_DB)
                checkOperands(AST_DATATYPE_BOOL, son0->son[0]);
            else
                checkOperands(AST_DATATYPE_BOOL, son0);



            if(son1)
            {
                if(son1->type == AST_COMMAND)
                    checkCmds(son1);
                else
                    checkCmd(son1);
            }
                

            break;

        case AST_IF_THEN_ELSE:

            if(son0->type == AST_DB)
                checkOperands(AST_DATATYPE_BOOL, son0->son[0]);
            else
                checkOperands(AST_DATATYPE_BOOL, son0);

            if(son1)
            {
                if(son1->type == AST_COMMAND)
                    checkCmds(son1);
                else
                    checkCmd(son1);
            }
                

            if(son2)
            {
                if(son2->type == AST_COMMAND)
                    checkCmds(son2);
                else
                    checkCmd(son2);
            }
                
                    
            break;


        case AST_PRINT:
            //precisa???
            break;
        case AST_RETURN:
            break;
    }

}

void checkFuncall(AST* node)
{

    int found = 0;

    AST* fundec;
    AST* _fundec;
    AST* _son1;
    AST* son0 = node->son[0];
    AST* son1 = node->son[1];

    astFindNode(0, getAST(),  &fundec , son0->symbol->text, &found);

    if(found == 1)
    {
        int paramCounter = 0;
        int argumentCounter = 0;

        _fundec = fundec->son[1];
        _son1 = son1;

        for(fundec = fundec->son[1]; fundec; fundec = fundec->son[1])
            paramCounter++;

        for(; son1; son1 = son1->son[1])
            argumentCounter++;

        if(argumentCounter != paramCounter)
        {
            fprintf(stderr, "[SEMANTIC] Number of arguments in function call '%s' invalid.\n", son0->symbol->text);
            SemanticErrorFlag = 1;
        }
        else
        {
            int i = 0, k = 0;

            fundec = _fundec;
            son1 = _son1;

            for(i = 0; i < argumentCounter; son1 = son1->son[1], i++)
            {
                for(k = 0; k < argumentCounter - i - 1; fundec = fundec->son[1], k++);

                if(fundec->son[0]->type == AST_VEC)
                {
                    if(fundec->son[0]->son[0]->symbol->datatype != son1->son[0]->symbol->datatype )
                    {
                        fprintf(stderr, "[SEMANTIC] Argument '%s' dont match with parameter '%s'.\n", fundec->son[0]->son[0]->symbol->text, son1->son[0]->symbol->text);
                        SemanticErrorFlag = 1;
                    }
                }
                else
                {
                    if(fundec->son[0]->symbol->datatype != son1->son[0]->symbol->datatype )
                    {
                        fprintf(stderr, "[SEMANTIC] Argument '%s' dont match with parameter '%s'.\n", fundec->son[0]->symbol->text, son1->son[0]->symbol->text);
                        SemanticErrorFlag = 1;
                    }
                }
                

                fundec = _fundec;
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
            checkCmd(cmd->son[0]) ;       

    }


}

void setArgDeclaration(AST* node)
{
    for(; node; node = node->son[1])
    {
        switch(node->son[0]->type){
            case AST_INT_TYPE:node->son[0]->symbol->datatype = DATATYPE_INT; 
                node->son[0]->symbol->type = SYMBOL_SCALAR; 
            
                break;
            case AST_FLOAT_TYPE:node->son[0]->symbol->datatype = DATATYPE_FLOAT;  
                node->son[0]->symbol->type = SYMBOL_SCALAR; 
            
                break;
            case AST_CHAR_TYPE:node->son[0]->symbol->datatype = DATATYPE_CHAR; 
                node->son[0]->symbol->type = SYMBOL_SCALAR;  
            
                break;
            case AST_VEC: 
                if(node->son[0]->son[0]->type)
                {
                    switch(node->son[0]->son[0]->type){
                        case AST_INT_TYPE:node->son[0]->son[0]->symbol->datatype = DATATYPE_INT;  
                            node->son[0]->son[0]->symbol->type = SYMBOL_VECTOR; 
                        
                            break;
                        case AST_FLOAT_TYPE:node->son[0]->son[0]->symbol->datatype = DATATYPE_FLOAT; 
                            node->son[0]->son[0]->symbol->type = SYMBOL_VECTOR;  
                        
                            break;
                        case AST_CHAR_TYPE:node->son[0]->son[0]->symbol->datatype = DATATYPE_CHAR;  
                            node->son[0]->son[0]->symbol->type = SYMBOL_VECTOR; 
                        
                            break;
                    }
                
                }
                break;
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

            if(node->symbol->type != SYMBOL_SCALAR && node->symbol->type != SYMBOL_FUNCTION)
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
            node->datatype = node->son[0]->datatype;

            if(node->son[0]->symbol)
            {
                if(node->son[0]->symbol->datatype == DATATYPE_INT || node->son[0]->symbol->datatype == DATATYPE_CHAR)
                    node->datatype = AST_DATATYPE_INT;
                else
                    node->datatype = AST_DATATYPE_FLOAT;
            }
            
            break;
        case AST_FUNCALL:
            node->datatype = node->son[0]->datatype;
            checkFuncall(node);

            if(node->son[0]->symbol->datatype == DATATYPE_INT || node->son[0]->symbol->datatype == DATATYPE_CHAR)
                node->datatype = AST_DATATYPE_INT;
            else
                node->datatype = AST_DATATYPE_FLOAT;
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
                fprintf(stderr, "[SEMANTIC] Only boolean allowed with NOT.\n");
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
            if(node->son[0]->datatype != node->son[1]->datatype)
            {
                fprintf(stderr, "[SEMANTIC] Cannot mix different datatypes in boolean expression.\n");
                SemanticErrorFlag = 1;
            }

            node->datatype = AST_DATATYPE_BOOL;

            break;
    }
}