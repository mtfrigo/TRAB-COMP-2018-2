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

void astToFile(int level, AST *node, FILE* fileTree){
	int i = 0;

  	for(i=0; i<level; i++)
   		fprintf(stderr, "  ");
  	if(!node){
    		return;
  	}else{
    		switch(node->type){

        		case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL,\n"); 			break;
			case AST_DEC: fprintf(stderr, "AST_DEC,\n"); 				break;
			case AST_VEC_DECLARATION: fprintf(stderr, "AST_VEC_DECLARATION,\n"); 	break;
			case AST_VAR_DECLARATION: fprintf(stderr, "AST_VAR_DECLARATION,\n"); 	break;
			case AST_CHAR_TYPE: fprintf(stderr, "AST_CHAR_TYPE,\n"); 		break;
			case AST_FLOAT_TYPE: fprintf(stderr, "AST_FLOAT_TYPE,\n"); 		break;
			case AST_INT_TYPE: fprintf(stderr, "AST_INT_TYPE,\n"); 			break;
			case AST_LIT_LIST: fprintf(stderr, "AST_LIT_LIST,\n"); 			break;
			case AST_PARAM_LST: fprintf(stderr, "AST_PARAM_LST,\n"); 		break;
			case AST_FUNC_DEC: fprintf(stderr, "AST_FUNC_DEC,\n"); 			break;
			case AST_ARG_LIST: fprintf(stderr, "AST_ARG_LIST,\n"); 			break;
			case AST_COMMAND_LST: fprintf(stderr, "AST_COMMAND_LST,\n"); 		break;
			case AST_ATTRIB: fprintf(stderr, "AST_ATTRIB,\n"); 			break;
			case AST_ATTRIB_VEC: fprintf(stderr, "AST_ATTRIB_VEC,\n"); 		break;
			case AST_PRINT: fprintf(stderr, "AST_PRINT,\n"); 			break;
			case AST_RETURN: fprintf(stderr, "AST_RETURN,\n"); 			break;
			case AST_READ: fprintf(stderr, "AST_READ,\n"); 				break;
			case AST_IF_THEN: fprintf(stderr, "AST_IF_THEN,\n"); 			break;
			case AST_IF_THEN_ELSE: fprintf(stderr, "AST_IF_THEN_ELSE,\n"); 		break;
			case AST_WHILE: fprintf(stderr, "AST_WHILE,\n"); 			break;
			case AST_COMMAND: fprintf(stderr, "AST_COMMAND,\n"); 			break;
			case AST_LT: fprintf(stderr, "AST_LT,\n");				break;
			case AST_GT: fprintf(stderr, "AST_GT,\n"); 				break;
			case AST_LE: fprintf(stderr, "AST_LE,\n"); 				break;
			case AST_GE: fprintf(stderr, "AST_GE,\n"); 				break;
			case AST_EQ: fprintf(stderr, "AST_EQ,\n"); 				break;
			case AST_OR: fprintf(stderr, "AST_OR,\n"); 				break;
			case AST_AND: fprintf(stderr, "AST_AND,\n"); 				break;
			case AST_NOT: fprintf(stderr, "AST_NOT,\n"); 				break;
			case AST_ADD: fprintf(stderr, "AST_ADD,\n"); 				break;
			case AST_SUB: fprintf(stderr, "AST_SUB,\n"); 				break;
			case AST_DIV: fprintf(stderr, "AST_DIV,\n"); 				break;
			case AST_MUL: fprintf(stderr, "AST_MUL,\n"); 				break;
			case AST_VEC: fprintf(stderr, "AST_VEC,\n");				break;
			case AST_FUNCALL: fprintf(stderr, "AST_FUNCALL,\n");			break;
			case AST_DB: fprintf(stderr, "AST_DB,\n");				break;
			default: fprintf(stderr,"AST_UNKNOWN,\n");				break;

		}
		if(node->symbol != 0)
			fprintf(stderr, "%s, \n", node->symbol->text);
		else
			fprintf(stderr, "0, \n");
	
		for (i=0; i<MAX_SONS; i++)
			astToFile(level+1, node->son[i], fileTree);
			
	}
}

