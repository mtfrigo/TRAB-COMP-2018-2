#include "ast.h"


AST* astCreate(int type, HASH_NODE *symbol, AST *son0, AST *son1, AST *son2, AST *son3){


	AST* newnode;
	newnode = (AST*) calloc(1,sizeof(AST));
	newnode->type = type;
	newnode->symbol = symbol;
	newnode->son[FILHOZERO] = son0;
	newnode->son[FILHOUM]   = son1;
	newnode->son[FILHODOIS] = son2;
	newnode->son[FILHOTRES] = son3;
	return newnode;
}

void astPrint(int level, AST *node){
	int i = 0;

	if(node == 0)
		return;
	  
  	for(i=0; i<level; i++)
   		fprintf(stderr, "   ");

	switch(node->type){

		case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL, "); 			break;
		case AST_DEC: fprintf(stderr, "AST_DEC, "); 				break;
		case AST_VEC_DECLARATION: fprintf(stderr, "AST_VEC_DECLARATION, "); 	break;
		case AST_VAR_DECLARATION: fprintf(stderr, "AST_VAR_DECLARATION, "); 	break;
		case AST_CHAR_TYPE: fprintf(stderr, "AST_CHAR_TYPE, "); 		break;
		case AST_FLOAT_TYPE: fprintf(stderr, "AST_FLOAT_TYPE, "); 		break;
		case AST_INT_TYPE: fprintf(stderr, "AST_INT_TYPE, "); 			break;
		case AST_LIT_LIST: fprintf(stderr, "AST_LIT_LIST, "); 			break;
		case AST_PARAM_LST: fprintf(stderr, "AST_PARAM_LST, "); 		break;
		case AST_FUNC_DEC: fprintf(stderr, "AST_FUNC_DEC, "); 			break;
		case AST_ARG_LIST: fprintf(stderr, "AST_ARG_LIST, "); 			break;
		case AST_COMMAND_LST: fprintf(stderr, "AST_COMMAND_LST, "); 		break;
		case AST_ATTRIB: fprintf(stderr, "AST_ATTRIB, "); 			break;
		case AST_ATTRIB_VEC: fprintf(stderr, "AST_ATTRIB_VEC, "); 		break;
		case AST_PRINT: fprintf(stderr, "AST_PRINT, "); 			break;
		case AST_RETURN: fprintf(stderr, "AST_RETURN, "); 			break;
		case AST_READ: fprintf(stderr, "AST_READ, "); 				break;
		case AST_IF_THEN: fprintf(stderr, "AST_IF_THEN, "); 			break;
		case AST_IF_THEN_ELSE: fprintf(stderr, "AST_IF_THEN_ELSE, "); 		break;
		case AST_WHILE: fprintf(stderr, "AST_WHILE, "); 			break;
		case AST_COMMAND: fprintf(stderr, "AST_COMMAND, "); 			break;
		case AST_LT: fprintf(stderr, "AST_LT, ");				break;
		case AST_GT: fprintf(stderr, "AST_GT, "); 				break;
		case AST_LE: fprintf(stderr, "AST_LE, "); 				break;
		case AST_GE: fprintf(stderr, "AST_GE, "); 				break;
		case AST_EQ: fprintf(stderr, "AST_EQ, "); 				break;
		case AST_OR: fprintf(stderr, "AST_OR, "); 				break;
		case AST_AND: fprintf(stderr, "AST_AND, "); 				break;
		case AST_NOT: fprintf(stderr, "AST_NOT, "); 				break;
		case AST_ADD: fprintf(stderr, "AST_ADD, "); 				break;
		case AST_SUB: fprintf(stderr, "AST_SUB, "); 				break;
		case AST_DIV: fprintf(stderr, "AST_DIV, "); 				break;
		case AST_MUL: fprintf(stderr, "AST_MUL, "); 				break;
		case AST_VEC: fprintf(stderr, "AST_VEC, ");				break;
		case AST_FUNCALL: fprintf(stderr, "AST_FUNCALL," );			break;
		case AST_DB: fprintf(stderr, "AST_DB, ");				break;
		case AST_STRING: fprintf(stderr, "AST_STRING, ");				break;
		default: fprintf(stderr,"AST_UNKNOWN, ");				break;

	}
	
	if(node->symbol != 0)
		fprintf(stderr, "%s, \n", node->symbol->text);
	else
		fprintf(stderr, "<no symbol>, \n");

	for (i=0; i<MAX_SONS; i++)
		astPrint(level+1, node->son[i]);
			
}

void astToFile(AST *node, FILE *f){
	
	int i = 0;
	int level = 0;

	if(node == 0)
		return;
	  
	switch(node->type){

		case AST_SYMBOL: {
		
			fprintf(f, "%s", node->symbol->text);
			break;
		}
		case AST_DEC: {
			
			for(i = 0; i < MAX_SONS; i++)
				astToFile(node->son[i], f);

			break;
		}
		case AST_VEC_DECLARATION: {
			
			astToFile(node->son[0], f);

		    	fprintf(f, " q%sp", node->son[1]->symbol->text);

		    	if(node->son[2] != 0)
		    	{
		        	fprintf(f, ": ");
		        	astToFile(node->son[2], f);
		    	}
		    	fprintf(f, ";\n");
			break;
		}
		case AST_VAR_DECLARATION: {
			
			astToFile(node->son[0], f);
			fprintf(f, " = ");

			astToFile(node->son[1], f);
			fprintf(f, ";\n");

			break;
		}
		case AST_CHAR_TYPE: {

			fprintf(f, "char %s", node->symbol->text);
			
			break;
		}
		case AST_STRING: {

			fprintf(f, "\"");
			fprintf(f, "%s", node->symbol->text);
			fprintf(f, "\"");
			
			break;
		}
		case AST_FLOAT_TYPE: {
			
			fprintf(f, "float %s", node->symbol->text);

			break;
		}
		case AST_INT_TYPE: {
			
			fprintf(f, "int %s", node->symbol->text);

			break;
		}
		case AST_LIT_LIST: {
		
			if(node->son[1] != 0)
            		{
                		astToFile(node->son[1], f);
                		fprintf(f, " ");
           		 }
            		astToFile(node->son[0], f);

			break;
		}
		case AST_PARAM_LST: {

			if(node->son[1] != 0)
		    	{
				if(node->son[1]->type == AST_PARAM_LST)
				{
			    		astToFile(node->son[1], f);
			 	   	fprintf(f, ", ");
				}
		    	}
            		astToFile(node->son[0], f);

			break;
		}
		case AST_FUNC_DEC: {

			astToFile(node->son[0], f);
            		fprintf(f, " d");
            		astToFile(node->son[1], f);
            		fprintf(f, "b");
            		astToFile(node->son[2], f);

			break;
		}
		case AST_ARG_LIST: {
			
			if(node->son[1] != 0)
		    	{
				if(node->son[1]->type == AST_ARG_LIST)
				{
			    		astToFile(node->son[1], f);
			 	   	fprintf(f, ", ");
				}
		    	}
            		astToFile(node->son[0], f);

			break;
		}
		case AST_COMMAND_LST: {
			
			astToFile(node->son[0], f);
            		fprintf(f, ";\n");
			astToFile(node->son[1], f);

			break;
		}
		case AST_ATTRIB: {

			for (i = 0; i < level; i++) 
				fprintf(f, "    ");

			astToFile(node->son[0], f);
			fprintf(f, " = ");
			astToFile(node->son[1], f);

			break;
		}
		case AST_ATTRIB_VEC: {

			for (i = 0; i < level; i++) 
				fprintf(f, "    ");
            		astToFile(node->son[0], f);
            		fprintf(f, " q");
            		astToFile(node->son[1], f);
            		fprintf(f, "p = ");
			astToFile(node->son[2], f);

			break;
		}
		case AST_PRINT: {
			
			for (i = 0; i < level; i++) 
				fprintf(f, "    ");


			fprintf(f, "print ");

			astToFile(node->son[0], f);


			break;
		}
		case AST_RETURN: {
			
			for (i = 0; i < level; i++) 
				fprintf(f, "    ");
			fprintf(f, "return ");
			astToFile(node->son[0], f);

			break;
		}
		case AST_READ: {

			for (i = 0; i < level; i++) 
				fprintf(f, "    ");
            		fprintf(f, "read ");
            		astToFile(node->son[0], f);

			break;
		}
		case AST_IF_THEN: {

			for (i = 0; i < level; i++) fprintf
				(f, "    ");
		    	fprintf(f, "if ");
		    	astToFile(node->son[0], f);
		    	fprintf(f, " then\n");
		    	for (i = 0; i < level; i++) 
				fprintf(f, "    ");
		    	astToFile(node->son[1], f);
			
			break;
		}
		case AST_IF_THEN_ELSE: {
			for (i = 0; i < level; i++) 
				fprintf(f, "    ");
            		fprintf(f, "if ");
            		astToFile(node->son[0], f);
            		fprintf(f, " then\n");
            		for (i = 0; i < level; i++)
				fprintf(f, "    ");
            		astToFile(node->son[1], f);
            		fprintf(f, "\n");
            		for (i = 0; i < level; i++) 
				fprintf(f, "    ");
            		fprintf(f, "else\n");
            		for (i = 0; i < level; i++) 
				fprintf(f, "    ");
            		astToFile(node->son[2], f);

			break;
		}
		case AST_WHILE: {
			
			for (i = 0; i < level; i++) 
				fprintf(f, "    ");
            		fprintf(f, "while ");
            		astToFile(node->son[0], f);
            		fprintf(f, "\n");
            		for (i = 0; i < level; i++) 
				fprintf(f, "    ");
            		astToFile(node->son[1], f);

			break;
		}
		case AST_COMMAND: {
			
			fprintf(f, "{\n");
            		level++;
            		astToFile(node->son[0], f);
            		level--;
            		for (i = 0; i < level; i++) 
				fprintf(f, "    ");
			fprintf(f, "}");

			break;
		}
		case AST_LT: {

			astToFile(node->son[0], f);
            		fprintf(f, " < ");
			astToFile(node->son[1], f);

			break;
		}
		case AST_GT: {
				
			astToFile(node->son[0], f);
            		fprintf(f, " > ");
			astToFile(node->son[1], f);			

			break;
		}
		case AST_LE: {
			
			astToFile(node->son[0], f);
            		fprintf(f, " <= ");
			astToFile(node->son[1], f);

			break;
		}
		case AST_GE: {
			
			astToFile(node->son[0], f);
            		fprintf(f, " >= ");
			astToFile(node->son[1], f);

			break;
		}
		case AST_EQ: {
			
			astToFile(node->son[0], f);
            		fprintf(f, " == ");
			astToFile(node->son[1], f);

			break;
		}
		case AST_OR: {
			
			astToFile(node->son[0], f);
            		fprintf(f, " or ");
			astToFile(node->son[1], f);			

			break;
		}
		case AST_AND: {
			
			astToFile(node->son[0], f);
            		fprintf(f, " and ");
			astToFile(node->son[1], f);

			break;
		}
		case AST_NOT: {
			
            		fprintf(f, "not ");
			astToFile(node->son[0], f);

			break;
		}
		case AST_ADD: {

			astToFile(node->son[0], f);
            		fprintf(f, " + ");
			astToFile(node->son[1], f);
			
			break;
		}
		case AST_SUB: {
			
			astToFile(node->son[0], f);
            		fprintf(f, " - ");
			astToFile(node->son[1], f);

			break;
		}
		case AST_DIV: {

			astToFile(node->son[0], f);
            		fprintf(f, " / ");
			astToFile(node->son[1], f);
			
			break;
		}
		case AST_MUL: {

			astToFile(node->son[0], f);
            		fprintf(f, " * ");
			astToFile(node->son[1], f);

			break;
		}
		case AST_VEC: {

			astToFile(node->son[0], f);
            		fprintf(f, " q");
            		astToFile(node->son[1], f);
			fprintf(f, "p");
			
			break;
		}
		case AST_FUNCALL: {
			
			astToFile(node->son[0], f);
            		fprintf(f, "d ");
            		astToFile(node->son[1], f);
			fprintf(f, " b\n");


			break;
		}
		case AST_DB: {

			fprintf(f, "d ");
            		astToFile(node->son[0], f);
			fprintf(f, " b");
		
			break;
		}
		default: {
			
			fprintf(f, "GEROFRIGOLICIOUS VOS SAUDA");	

			break;
		}

	}
	
}

void astFind(int level, AST *node, char* text)
{
	int i = 0;

	if(node == 0)
		return;

	  
	if(node->type == AST_VAR_DECLARATION){
		if((strcmp(node->son[0]->symbol->text, text) == 0 && node->son[0]->symbol->type == 274))
		{
			hashSetType(text, SYMBOL_IDENTIFIER);
		}
	}

	if(node->type == AST_FUNC_DEC || node->type == AST_VEC_DECLARATION || node->type == AST_ARG_LIST){
		hashSetType(node->son[0]->symbol->text, SYMBOL_IDENTIFIER);
	}


	for (i=0; i<MAX_SONS; i++){
		astFind(level+1, node->son[i], text);
	}
}

AST* astFindNode(int level, AST *node, AST **terc, char* text, int *found)
{
	int i = 0;


	if(node->type == AST_FUNC_DEC && strcmp(node->son[0]->symbol->text, text) == 0){
		*terc = node;
		*found = 1;
	}

	if(*found == 1){
		return NULL;
	}


	for (i=0; i<MAX_SONS; i++){
		if(node->son[i])
			astFindNode(level+1, node->son[i], terc, text, found);
	}	
}
