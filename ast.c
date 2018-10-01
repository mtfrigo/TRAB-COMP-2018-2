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

	if(node == 0)
		return;
	  
	switch(node->type){

		case AST_SYMBOL:{
			

			break;
		}
		case AST_DEC: {
			
			for(i = 0; i < MAX_SONS; i++)
				astToFile(node->son[i], f);

			break;
		}
		case AST_VEC_DECLARATION: {
			

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
			

			break;
		}
		case AST_FLOAT_TYPE: {
			

			break;
		}
		case AST_INT_TYPE: {
			

			break;
		}
		case AST_LIT_LIST: {
			

			break;
		}
		case AST_PARAM_LST: {
			

			break;
		}
		case AST_FUNC_DEC: {
			

			break;
		}
		case AST_ARG_LIST: {
			

			break;
		}
		case AST_COMMAND_LST: {
			

			break;
		}
		case AST_ATTRIB: {
			

			break;
		}
		case AST_ATTRIB_VEC: {
			

			break;
		}
		case AST_PRINT: {
			

			break;
		}
		case AST_RETURN: {
			

			break;
		}
		case AST_READ: {
			

			break;
		}
		case AST_IF_THEN: {
			

			break;
		}
		case AST_IF_THEN_ELSE: {
			

			break;
		}
		case AST_WHILE: {
			

			break;
		}
		case AST_COMMAND: {
			

			break;
		}
		case AST_LT: {
			

			break;
		}
		case AST_GT: {
			

			break;
		}
		case AST_LE: {
			

			break;
		}
		case AST_GE: {
			

			break;
		}
		case AST_EQ: {
			

			break;
		}
		case AST_OR: {
			

			break;
		}
		case AST_AND: {
			

			break;
		}
		case AST_NOT: {
			

			break;
		}
		case AST_ADD: {
			

			break;
		}
		case AST_SUB: {
			

			break;
		}
		case AST_DIV: {
			

			break;
		}
		case AST_MUL: {
			

			break;
		}
		case AST_VEC: {
			

			break;
		}
		case AST_FUNCALL: {
			

			break;
		}
		case AST_DB: {
			

			break;
		}
		default: {
			

			break;
		}

	}
	
}