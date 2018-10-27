void setDeclarations(AST *root)
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


        fprintf(stderr, "[DEBUG] Node type: [%d]    ; Dec type: [%d].\n", node->type, dec->type);

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

                    if(asc)
                    {
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

                    AST* decAux = dec;

                    dec->symbol->type = SYMBOL_FUNCTION;

                    if(dec->type == AST_INT_TYPE || dec->type == AST_CHAR_TYPE)
                    {
                        dec->symbol->datatype = DATATYPE_INT;
                    }
                    else
                    {
                        dec->symbol->datatype = DATATYPE_FLOAT;
                    }

                    if(asc)
                    {
                        for(asc; asc; asc = asc->son[1])
                        {
                            dec = asc->son[0];
                            
                            switch(dec->type){
                                case AST_INT_TYPE:dec->symbol->datatype = DATATYPE_INT; break;
                                case AST_FLOAT_TYPE:dec->symbol->datatype = DATATYPE_FLOAT; break;
                                case AST_CHAR_TYPE:dec->symbol->datatype = DATATYPE_CHAR; break;
                            }
                        }

                        if(node->son[2])
                        {
                            terc = node->son[2];

                            while(terc->type != AST_RETURN)
                            {
                                if(terc->son[1])
                                {
                                    terc = terc->son[1];
                                }
                                else
                                {
                                    terc = terc->son[0];
                                }
                            }

                            if(terc->type == AST_RETURN)
                            {
                                if(terc->son[0]->type == AST_SYMBOL)
                                {
                                    if(dec->symbol->datatype != terc->son[0]->symbol->datatype)
                                    {
                                        if(((decAux->symbol->type == DATATYPE_CHAR || decAux->symbol->type == DATATYPE_INT) && (terc->son[0]->symbol->datatype == DATATYPE_CHAR || terc->son[0]->symbol->datatype == DATATYPE_INT)) ||
                                            (decAux->symbol->type == DATATYPE_FLOAT  &&  terc->son[0]->symbol->datatype == DATATYPE_FLOAT))
                                        fprintf(stderr, "[SEMANTIC] Function %s with type = %d and return type = %d\n", decAux->symbol->text, decAux->symbol->type, terc->son[0]->symbol->datatype);
                                        SemanticErrorFlag = 1;
                                    }
                                }
                            }

                        }
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
                        SemanticErrorFlag = 1;
                    }
                    else if(dec->symbol->type == SYMBOL_FUNCTION)
                    {
                        fprintf(stderr, "[SEMANTIC] Attributing scalar to a function (%s) type;\n", dec->symbol->text);
                        SemanticErrorFlag = 1;
                    }
                    else if(asc){
                        if(asc->type == AST_SYMBOL)
                        {
                            if(asc->symbol->type == SYMBOL_FUNCTION)
                            {
                                fprintf(stderr, "[SEMANTIC] Cannot use function without parameters (%s);\n", asc->symbol->text);
                                SemanticErrorFlag = 1;
                            }
                        }
                        else if(asc->type == AST_LT || asc->type == AST_GT || asc->type == AST_LE || asc->type == AST_GE
                            || asc->type == AST_EQ || asc->type == AST_OR || asc->type == AST_AND || asc->type == AST_NOT
                            || asc->type == AST_ADD || asc->type == AST_SUB || asc->type == AST_MUL || asc->type == AST_DIV)
                        {
                            checkOperands(dec->symbol->datatype, asc);
                        }
                    }

                    break;

                case AST_ATTRIB_VEC:

                    if(dec->symbol->type == SYMBOL_SCALAR)
                    {
                        fprintf(stderr, "[SEMANTIC] Cannot index a scalar variable (%s) ;\n", dec->symbol->text );
                        SemanticErrorFlag = 1;
                    }
                    else if(dec->symbol->type == SYMBOL_FUNCTION)
                    {
                        fprintf(stderr, "[SEMANTIC] Attributing vector to a function (%s) type;\n", dec->symbol->text);
                        SemanticErrorFlag = 1;
                    }
                    else if(node->son[2]->type == AST_SYMBOL)
                    {


                        if(node->son[2]->symbol->type == SYMBOL_FUNCTION)
                        {
                            fprintf(stderr, "[SEMANTIC] Cannot use function without parameters (%s);\n", node->son[2]->symbol->text);
                            SemanticErrorFlag = 1;
                        }
                    }
                    else if(node->son[2]->type == AST_LT || node->son[2]->type == AST_GT || node->son[2]->type == AST_LE || node->son[2]->type == AST_GE
                        || node->son[2]->type == AST_EQ || node->son[2]->type == AST_OR || node->son[2]->type == AST_AND || node->son[2]->type == AST_NOT
                        || node->son[2]->type == AST_ADD || node->son[2]->type == AST_SUB || node->son[2]->type == AST_MUL || node->son[2]->type == AST_DIV)
                    {
                        checkOperands(dec->symbol->datatype, node->son[2]);
                    }

                    break;


                    if(dec->symbol->type == SYMBOL_VECTOR )
                    {
                        fprintf(stderr, "[SEMANTIC] Attributing scalar to a vector (%s) type;\n", dec->symbol->text);
                        SemanticErrorFlag = 1;
                    }
                    else if(dec->symbol->type == SYMBOL_FUNCTION)
                    {
                        fprintf(stderr, "[SEMANTIC] Attributing scalar to a function (%s) type;\n", dec->symbol->text);
                        SemanticErrorFlag = 1;
                    }
                    else if(asc)
                    {
                        if(asc->type == AST_SYMBOL)
                        {
                            if(asc->symbol->type == SYMBOL_FUNCTION)
                            {
                                fprintf(stderr, "[SEMANTIC] Cannot use function without parameters (%s);\n", asc->symbol->text);
                                SemanticErrorFlag = 1;
                            }
                        }
                        else if(asc->type == AST_LT || asc->type == AST_GT || asc->type == AST_LE || asc->type == AST_GE
                            || asc->type == AST_EQ || asc->type == AST_OR || asc->type == AST_AND || asc->type == AST_NOT
                            || asc->type == AST_ADD || asc->type == AST_SUB || asc->type == AST_MUL || asc->type == AST_DIV)
                        {
                            checkOperands(dec->symbol->datatype, asc);
                        }
                    }

                    break;

                case AST_FUNCALL:
                {
                    int found = 0;

                    AST* terc;
                    AST* tercAux;
                    AST* ascAux;

                    astFindNode(0, getAST(),  &terc , dec->symbol->text, &found);

                    int paramCounter = 0;
                    int argumentCounter = 0;

                    if(found == 1)
                    {
                        if(terc->type == AST_FUNC_DEC)
                        {
                            tercAux = terc->son[1];

                            for(terc = tercAux; terc; terc = terc->son[1])
                            {
                                paramCounter++;
                                //fprintf(stderr, "[FUNCALL] (%s) PARAM: ;\n", terc->son[0]->symbol->text );
                            }
                        }
                    }
                    else
                    {
                        fprintf(stderr, "[SEMANTIC] Call invalid function '%s'", dec->symbol->text);
                        SemanticErrorFlag = 1;
                    }

                    if(asc)
                    {
                        ascAux = asc;

                        for(asc; asc; asc = asc->son[1])
                        {
                            argumentCounter++;
                        }
                    }

                    asc = ascAux;
                    terc = tercAux;

                    if(argumentCounter != paramCounter)
                    {
                        fprintf(stderr, "[SEMANTIC] Number of arguments in function call '%s' invalid.\n", dec->symbol->text);
                        SemanticErrorFlag = 1;
                    }
                    else{

                        int i = 0, k = 0;

                        for(i = 0; i < argumentCounter; asc = asc->son[1], i++)
                        {
                            for(k = 0; k < argumentCounter - i - 1; terc = terc->son[1], k++);

                            //fprintf(stderr, "[FUNCALL] (%s) ARG, type = %d .\n", terc->son[0]->symbol->text, terc->son[0]->symbol->datatype);
                            //fprintf(stderr, "[FUNCALL] (%s) PARAM, type = %d.\n", asc->son[0]->symbol->text, asc->son[0]->symbol->datatype);

                            if(terc->son[0]->symbol->datatype != asc->son[0]->symbol->datatype )
                            {
                                if(!((terc->son[0]->symbol->datatype == DATATYPE_CHAR || terc->son[0]->symbol->datatype == DATATYPE_INT) &&
                                 (asc->son[0]->symbol->datatype == DATATYPE_CHAR || asc->son[0]->symbol->datatype == DATATYPE_INT)))
                                 {
                                    fprintf(stderr, "[SEMANTIC] Argument '%s' dont match with parameter '%s'.\n", terc->son[0]->symbol->text, asc->son[0]->symbol->text);
                                    SemanticErrorFlag = 1;
                                 }
                                
                            }

                            terc = tercAux;
                        }
                    }

                    break;

                }
                default: break;

            }
        }
    }

    



}
