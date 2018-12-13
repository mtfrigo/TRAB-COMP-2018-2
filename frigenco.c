#include "frigenco.h"
#include "hash.h"
#include "semantic.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RBP "rbp"
#define RETURN_REGISTER "eax"

char fun_reg[6][6] = {"edi", "esi", "edx", "ecx", "r8d", "r9d"};

void printTacInfo(char *type, TAC *tac)
{
	fprintf(stderr, "%s; \tres: %s ; \top1: %s ; \top2: %s", 
		type,
		tac->res ? tac->res->text : "---",
		tac->op1 ? tac->op1->text : "---", 
		tac->op2 ? tac->op2->text : "---") ; 

	return;
}

void gen_var_declaration(FILE* output, AST *node)
{
	fprintf(output, "\t.globl\t%s\n", node->son[0]->symbol->text);
	
	if(strcmp(node->son[1]->symbol->text, "0") == 0 ||
	   strcmp(node->son[1]->symbol->text, "0.0") == 0)
		fprintf(output, "\t.bss\n");
	else
		fprintf(output, "\t.data\n");

	if(node->son[0]->type != AST_CHAR_TYPE)
		fprintf(output, "\t.align\t4\n"); 

	fprintf(output, "\t.type\t%s, @object\n", node->son[0]->symbol->text); 
	
	if(node->son[0]->type != AST_CHAR_TYPE)
		fprintf(output, "\t.size\t%s, 4\n", node->son[0]->symbol->text);
	else
		fprintf(output, "\t.size\t%s, 1\n", node->son[0]->symbol->text);

	fprintf(output, "%s:\n", node->son[0]->symbol->text);
	
	if(node->son[0]->type == AST_CHAR_TYPE)
		fprintf(output, "\t.byte\t%d\n", node->son[0]->symbol->text[0]);
	else
	{
		if(strcmp(node->son[1]->symbol->text, "0") == 0 ||
		strcmp(node->son[1]->symbol->text, "0.0") == 0)
			fprintf(output, "\t.zero\t4\n");
		else
		{
			if(node->son[0]->type == AST_INT_TYPE)
				fprintf(output, "\t.long\t%s\n", node->son[1]->symbol->text);
			else
				fprintf(output, "\t.long\t%s\n", "FAZER ESSA CONVERSAO");
		}
			
	}

	fprintf(output, "\n");

}

void gen_beginfun(FILE* output, TAC *tac)
{
	fprintf(output, "\t.globl\t%s\n", tac->res->text);
	
	fprintf(output, "\t.type\t%s, @function\n", tac->res->text); 
		
	fprintf(output, "%s:\n", tac->res->text);

	//needed?
	fprintf(output, "\t.cfi_startproc\n");
	fprintf(output, "\tpushq\t%%%s \n", RBP);
	fprintf(output, "\tmovq\t%%rsp, %%rbp\n");

	fprintf(output, "\n");
}

void gen_return(FILE* output, TAC *tac)
{
	if(tac->op1->isLiteral)
		fprintf(output, "\tmovl\t$%s, %%%s \n", tac->op1->text, RETURN_REGISTER);
	else
		fprintf(output, "\tmovl\t%s(%%rip), %%%s \n", tac->op1->text, RETURN_REGISTER);

	
	fprintf(output, "\n");

	//TODO implementar return caso seja vetor!!
}

void gen_endfun(FILE* output, TAC *tac)
{

	//fprintf(output, "\tmovl\t$%d, %%%s \n", 0, RETURN_REGISTER);

	fprintf(output, "\tpopq\t%%%s \n", RBP);
	
	fprintf(output, "\tret\n");

	fprintf(output, "\t.cfi_endproc\n");

	fprintf(output, "\n");
	
}

void gen_var_attr(FILE* output, TAC *tac, AST* root)
{

	AST* node = findDecNode(tac->res->text, root);

	if(node->son[0]->type == AST_CHAR_TYPE)
	{
		if(tac->op2->isLiteral)
		{
			fprintf(output, "\tmovb\t$%d, %s(%%rip) \n", tac->op2->text[1], tac->res->text);
		}
		else{

			fprintf(output, "\tmovzbl\t%s(%%rip), %%%s \n", tac->op2->text, RETURN_REGISTER);
			fprintf(output, "\tmovl\t%%%s, %s(%%rip) \n", "eax",  tac->res->text);
		}

	}
	else
	{
		if(tac->op2->isLiteral)
		{
			fprintf(output, "\tmovl\t$%s, %s(%%rip) \n", tac->op2->text, tac->res->text);
		}
		else{
			fprintf(output, "\tmovl\t%s(%%rip), %%%s \n", tac->op2->text, RETURN_REGISTER);
			fprintf(output, "\tmovl\t%%%s, %s(%%rip) \n", RETURN_REGISTER, tac->res->text);
		}
	}

	fprintf(output, "\n");
	
}

//USADA PARA ACHAR O NODO DE DETERMINADO SIMBOLO DA HASH A PARTIR DE SEU NOME!
AST* findDecNode(char *text, AST* root)
{
	AST* node = root;

	while(node->son[0])
	{
		if(node->son[0]->type == AST_VEC_DECLARATION ||
			node->son[0]->type == AST_VAR_DECLARATION)
		{
			if(strcmp(node->son[0]->son[0]->symbol->text, text) == 0)
				return node->son[0];
		}

		if(node->son[1])
		{
			if(node->son[1]->type == AST_VEC_DECLARATION ||
				node->son[1]->type == AST_VAR_DECLARATION)
			{
				if(strcmp(node->son[1]->son[0]->symbol->text, text) == 0)
					return node->son[1];
			}
		}
		node = node->son[0];
	}
	return NULL;
}



void gen_vec_attr(FILE* output, TAC *tac, AST* root)
{
	int byte_size;
	int index = atoi(tac->op1->text);
	AST* node = findDecNode(tac->res->text, root);

	if(node->son[0]->type == AST_CHAR_TYPE)
	{
		byte_size = 1;

		if(tac->op2->isLiteral)
		{
			fprintf(output, "\tmovb\t$%d, %d+%s(%%rip) \n", tac->op2->text[1],index*byte_size, tac->res->text);
		}
		else{
			fprintf(output, "\tmovzbl\t$%s(%%rip), %%%s \n", tac->op2->text, RETURN_REGISTER);
			fprintf(output, "\tmovl\t%%%s, %d+%s(%%rip) \n", RETURN_REGISTER, index*byte_size, tac->res->text);
		}

	}
	else
	{
		byte_size = 4;
		
		if(tac->op2->isLiteral)
		{
			fprintf(output, "\tmovl\t$%s, %d+%s(%%rip) \n", tac->op2->text,index*byte_size, tac->res->text);
		}
		else{
			fprintf(output, "\tmovl\t$%s(%%rip), %%%s \n", tac->op2->text, RETURN_REGISTER);
			fprintf(output, "\tmovl\t%%%s, %d+%s(%%rip) \n", RETURN_REGISTER, index*byte_size, tac->res->text);
		}
	}
	
	fprintf(output, "\n");
	
}

void gen_vec_declaration(FILE* output, AST *node)
{

	//TODO ARRUMAR SIZE E ALIGN !!!
	if(node->son[2])
	{
		//VETOR INICIALIZADO
		int n = atoi(node->son[1]->symbol->text);
		int align = getAlign(node->son[0]->type, n);

		fprintf(output, "\t.globl\t%s\n", node->son[0]->symbol->text);
	
		fprintf(output, "\t.data\n");

		//if(node->son[0]->type != AST_CHAR_TYPE)
			fprintf(output, "\t.align\t%d\n", getAlign(node->type, n)); 

		fprintf(output, "\t.type\t%s, @object\n", node->son[0]->symbol->text); 
		
		if(node->son[0]->type != AST_CHAR_TYPE)
			fprintf(output, "\t.size\t%s, %d\n", node->son[0]->symbol->text, n * 4);
		else
			fprintf(output, "\t.size\t%s, %d\n", node->son[0]->symbol->text, n);

		fprintf(output, "%s:\n", node->son[0]->symbol->text);
		

		int type = node->son[0]->type;
		node = node->son[2];
		while(node->son[0])
		{
			char auxChar;
			if(type == AST_CHAR_TYPE)
			{
				if(node->son[0]->type == AST_LIT_LIST)
					auxChar =  node->son[1]->symbol->text[1];
				else
					auxChar =  node->son[0]->symbol->text[1];
				fprintf(output, "\t.byte\t%d\n", auxChar);
			}
			else
			{
				if(node->son[0]->type == AST_LIT_LIST)
				{
					if(type == AST_INT_TYPE)
						fprintf(output, "\t.long\t%s\n", node->son[1]->symbol->text);
					else
						fprintf(output, "\t.long\t%s\n", "FAZER ESSA CONVERSAO");
						
				}
				else
				{
					if(type == AST_INT_TYPE)
						fprintf(output, "\t.long\t%s\n", node->son[0]->symbol->text);
					else
						fprintf(output, "\t.long\t%s\n", "FAZER ESSA CONVERSAO");
					
				}
			}
			node = node->son[0];
		}
	}
	else
	{
		//VETOR NAO INICIALIZADO!!
		if(node->son[0]->type == AST_CHAR_TYPE)
		{
			int align = getAlign(AST_CHAR_TYPE, atoi(node->son[1]->symbol->text));

			fprintf(output, "\t.comm\t%s, %s, %d\n", 
			node->son[0]->symbol->text, 
			node->son[1]->symbol->text,
			align);
		}
		else
		{
			int align = getAlign(AST_INT_TYPE, atoi(node->son[1]->symbol->text));
			int size = atoi(node->son[1]->symbol->text) * 4;
			
			fprintf(output, "\t.comm\t%s, %d, %d\n", 
			node->son[0]->symbol->text, 
			size,
			align);
		}
	}
}

int getAlign(int type, int n)
{
	if(type == AST_CHAR_TYPE)
	{
		int align = (n /  8) * 8;
		if(align == 0) align = 1;
		return align;
	}
	else
	{
		int align = 4;

		if(n > 7 )
			align = 32;
		else if( n > 3)
			align = 16;
		else if(n > 1)
			align = 8;
		else
			align = 4;

		return align;
	}
}

void get_declarations(FILE* output, AST *node)
{

	
    if(!node) return;
	
	switch(node->type)
	{
		case AST_DEC: 
			if(node->son[1])
				get_declarations(output, node->son[0]);
			get_declarations(output, node->son[1]);	
			break;

		case AST_VAR_DECLARATION: 
			gen_var_declaration(output, node);
			break;

		case AST_VEC_DECLARATION: 
			gen_vec_declaration(output, node);
			break;
	}

}

void get_temps(FILE* output, AST *root)
{
	HASH_NODE *hnode;

    int i;

    for (i = 0; i < HASH_SIZE; ++i){
        for (hnode = Table[i]; hnode; hnode = hnode->next){
			if(hnode->type == SYMBOL_TEMP)
			{
				fprintf(output, "%s:\n", hnode->text);
				fprintf(output, "\t.long\t0");
				fprintf(output, "\n");
			}
        }
    }

	fprintf(output, "\n");

}

void get_param(FILE* output, AST *node, AST *root)
{
	int i = 0;

	if(node == 0)
		return;

	if(node->type == AST_FUNC_DEC){

		AST *pnode = node->son[1];

		while(pnode)
		{
			fprintf(output, "%s:\n", pnode->son[0]->symbol->text);

			if(pnode->son[0]->type == AST_INT_TYPE)
			{
				fprintf(output, "\t.long\t%d\n", 0);
			}

			pnode = pnode->son[1];
		}
	}


	for (i=0; i<MAX_SONS; i++){
		get_param(output, node->son[i], root);
	}
}


void get_print_parameters(FILE* output, AST *node, AST *root, int *count)
{
	int i = 0;

	if(node == 0)
		return;
	if(node->type == AST_PRINT){

		AST *pnode = node->son[0];

		//fprintf(output, ".LC%d:\n", *count);

		while(pnode)
		{
			fprintf(output, ".LC%d:\n", *count);

			//CASO PARAMETRO NAO FOR UMA STRING JA EXISTEM AS CONSTANTE PRA PRINT
			if(pnode->son[0]->type == AST_STRING)
			{
				printf("tipo string %d\n", pnode->son[0]->type);
				fprintf(output, "\t.string\t\"%s\"\n", pnode->son[0]->symbol->text);

				pnode->son[0]->symbol->assemblyLabel = *count;

			}
			
			pnode = pnode->son[1];
			*count = *count + 1;;
			fprintf(output, "\n");
		}
	}

	for (i=0; i<MAX_SONS; i++){
		get_print_parameters(output, node->son[i], root, count);
	}
}

void gen_print(FILE *output, TAC *tac, AST* root)
{
	if(tac->node->son[0]->type == AST_STRING)
	{
		fprintf(output, "\tleaq\t.LC%d(%%rip), %%rdi\n", tac->res->assemblyLabel);
		fprintf(output, "\tcall\tputs@PLT\n");
	}
	//todas expressoes numericas!!!!
	else if(tac->node->son[0]->type == AST_ADD || tac->node->son[0]->type == AST_SUB || tac->node->son[0]->type == AST_DIV || tac->node->son[0]->type == AST_MUL)
	{
		fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->res->text);
		fprintf(output, "\tmovl\t%%eax, %%esi\n");
		fprintf(output, "\tleaq\t.printInt(%%rip), %%rdi\n");
		fprintf(output, "\tmovl\t$0, %%eax\n");
		fprintf(output, "\tcall\tprintf@PLT\n");
	}
	else 
	{
		AST *dec = 0 ;

		if(tac->node->son[0]->type == AST_VEC)
			dec = findDecNode(tac->node->son[0]->son[0]->symbol->text, root);
		else
			dec = findDecNode(tac->res->text, root);

		if(dec->son[0]->type == AST_INT_TYPE)
		{
			fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->res->text);
			fprintf(output, "\tmovl\t%%eax, %%esi\n");
			fprintf(output, "\tleaq\t.printInt(%%rip), %%rdi\n");
			fprintf(output, "\tmovl\t$0, %%eax\n");
			fprintf(output, "\tcall\tprintf@PLT\n");
		}
		else if(dec->son[0]->type == AST_CHAR_TYPE)
		{
			fprintf(output, "\tmovzbl\t%s(%%rip), %%eax\n", tac->res->text);
			fprintf(output, "\tmovsbl\t%%al, %%eax\n");
			fprintf(output, "\tmovl\t%%eax, %%esi\n");

			fprintf(output, "\tleaq\t.printChar(%%rip), %%rdi\n");
			fprintf(output, "\tmovl\t$0, %%eax\n");
			fprintf(output, "\tcall\tprintf@PLT\n");
		}
		else if(dec->son[0]->type == AST_FLOAT_TYPE)
		{
			fprintf(output, "\tmovss\t%s(%%rip), %%xmm0\n", tac->res->text);
			fprintf(output, "\tcvtss2sd\t%%xmm0, %%xmm0\n");
			fprintf(output, "\tleaq\t.printFloat%d(%%rip), %%rdi\n");
			fprintf(output, "\tmovl\t$1, %%eax\n");
			fprintf(output, "\tcall\tprintf@PLT\n");
		}
		
	}

	fprintf(output, "\n");
//	printf("String: %s; Label: .LC%d \n", tac->res->text, tac->res->assemblyLabel);;

}

void gen_numeric_expr(FILE *output, TAC *tac)
{
	char op[8];
    
	switch(tac->type)
	{
        case TAC_ADD:
            strcpy(op, "addl");
            break;
        case TAC_SUB:
            strcpy(op, "subl");
            break;
        case TAC_MUL:
            strcpy(op, "imull");
            break;
		case TAC_DIV:
            strcpy(op, "idivl");
            break;
        default:
            return;
            break;
    }

    if(!tac->op1->isLiteral) {
        fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
    }
    else{
        fprintf(output, "\tmovl\t$%s, %%eax\n", tac->op1->text);
    }

    if(!tac->op2->isLiteral) {
        fprintf(output, "\tmovl\t%s(%%rip), %%ebx\n", tac->op2->text);
    }
    else{
        fprintf(output, "\tmovl\t$%s, %%ebx\n", tac->op2->text);
    }

	if(tac->type == TAC_DIV) 
		fprintf(output, "\tcltd\n");

    fprintf(output, "\t%s\t%%ebx\n", op);
	
    fprintf(output, "\tmovl\t%%eax, %s(%%rip)\n", tac->res->text);

	fprintf(output, "\n");

}

void gen_vec_rd(FILE *output, TAC *tac, AST* root)
{
	AST *node = findDecNode(tac->node->son[0]->symbol->text, root);

	int byte_size;

	if(node->son[0]->type == AST_CHAR_TYPE)
		byte_size = 1;
	else
		byte_size = 4;

	fprintf(output, "\tmovl\t%d+%s(%%rip), %%eax\n", byte_size * atoi(tac->op2->text), tac->op1->text);
	fprintf(output, "\tmovl\t%%eax\t, %s(%%rip)\n", tac->res->text);
	fprintf(output, "\n");
}

void gen_bool(FILE *output, TAC* tac)
{
	char op[8];

	if(tac->op1->isLiteral) {
        fprintf(output, "\tmovl\t$%s, %%edx\n", tac->op1->text);
    }
    else{
        fprintf(output, "\tmovl\t%s(%%rip), %%edx\n", tac->op1->text);
    }

    if(tac->op2->isLiteral) {
        fprintf(output, "\tmovl\t$%s, %%eax\n", tac->op2->text);
    }
    else{
        fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op2->text);
    }

	fprintf(output, "\tcmpl\t%%eax, %%edx\n", tac->op2->text);

	switch(tac->type)
	{
        case TAC_EQ:
            strcpy(op, "jne");
            break;
        case TAC_GT:
            strcpy(op, "jle");
            break;
        case TAC_LT:
            strcpy(op, "jge");
        case TAC_GE:
            strcpy(op, "jl");
            break;
        case TAC_LE:
            strcpy(op, "jg");
            break;
        default:
            return;
            break;
    }

	fprintf(output, "\t%s", op);

}

void gen_if(FILE *output, TAC* tac)
{
	fprintf(output, "\t.%s\n", tac->res->text);
}

void gen_jump(FILE *output, TAC* tac)
{
	fprintf(output, "\tjmp\t.%s\n", tac->res->text);
}

void gen_label(FILE *output, TAC* tac)
{
	fprintf(output, ".%s:\n", tac->res->text);
}

void gen_funcall(FILE *output, TAC* tac)
{
	fprintf(output, "\tcall\t%s\n", tac->op1->text);

	fprintf(output, "\tmovl\t%%eax, %s(%%rip)\n", tac->res->text);

	fprintf(output, "\n");
}

void gen_arg(FILE *output, TAC* tac)
{
	if(tac->res->isLiteral)
	{
		fprintf(output, "\tmovl\t$%s, %%%s\n", tac->res->text, fun_reg[atoi(tac->op2->text)-1]);
	}
	else
	{
		fprintf(output, "\tmovl\t%s(%%rip), %%%s\n", tac->res->text, fun_reg[atoi(tac->op2->text)-1]);
	}
	
}

void gen_param(FILE *output, TAC* tac, AST *root)
{
	int byte_size = 4;

	fprintf(output, "\tmovl\t%%%s, %s(%%rip)\n", fun_reg[atoi(tac->op2->text)-1], tac->res->text);

}




void gen_assembly(TAC*node, FILE* output, AST *root){

    fprintf(stderr, "INITIALIZED GEN\n");

	//WRITE GLOBAL VARIABLES ASSEMBLY
	fprintf(output, "\t.text\n");
	get_declarations(output, root);
	//WRITE ALL TEMP VARIABLES
	get_temps(output, root);
	//WRITE ALL PARAMS
	get_param(output, root, root);
	//WRITE ALL STRINGS IN HASH
	int count = 0;
	fprintf(output, "\t.section\t.rodata\n\n");

	fprintf(output, ".printChar:\n");
	fprintf(output, "\t.string \"%%c\\n\"\n");

	fprintf(output, ".printInt:\n");
	fprintf(output, "\t.string \"%%d\\n\"\n");

	fprintf(output, ".printFloat:\n");
	fprintf(output, "\t.string \"%%f\\n\"\n");

	get_print_parameters(output, root, root, &count);
	
	fprintf(output, "\t.text\n");

	TAC *tac;
	

	for(tac = node; tac; tac = tac->next){

		if(tac->type == TAC_SYMBOL) continue;
		fprintf(stderr, "("); 
		switch(tac->type)
		{
			//case TAC_SYMBOL: printTacInfo("TAC_SYMBOL", tac) ; 
			//	break;

			case TAC_ADD: printTacInfo("TAC_ADD", tac);
						  gen_numeric_expr(output, tac); 
				break;

			case TAC_SUB: printTacInfo("TAC_SUB", tac); 
						  gen_numeric_expr(output, tac); 
				break;

			case TAC_DIV: printTacInfo("TAC_DIV", tac);
						  gen_numeric_expr(output, tac); 
				break;

			case TAC_MUL: printTacInfo("TAC_MUL", tac); 
						  gen_numeric_expr(output, tac); 
				break;

			case TAC_LT: printTacInfo("TAC_LT", tac); 
						 gen_bool(output, tac);
				break;

			case TAC_GT: printTacInfo("TAC_GT", tac); 
						 gen_bool(output, tac);
				break;

			case TAC_LE: printTacInfo("TAC_LE", tac); 
						 gen_bool(output, tac);
				break;

			case TAC_GE: printTacInfo("TAC_GE", tac); 
						 gen_bool(output, tac);
				break;

			case TAC_EQ: printTacInfo("TAC_EQ", tac); 
						 gen_bool(output, tac);
				break;

			case TAC_BEGINFUN:  printTacInfo("TAC_BEGINFUN", tac); 
								gen_beginfun(output, tac);
				break;

			case TAC_RETURN: printTacInfo("TAC_RETURN", tac); 
							 gen_return(output, tac);
				break;

			case TAC_ENDFUN: printTacInfo("TAC_ENDFUN", tac);
							 gen_endfun(output, tac); 
				break;

			case TAC_PRINT: printTacInfo("TAC_PRINT", tac);
							gen_print(output, tac, root); 
				break;

			case TAC_MOVE: printTacInfo("TAC_MOVE", tac); 
						   gen_var_attr(output, tac, root);
				break;

			case TAC_VEC_WR: printTacInfo("TAC_VEC_WR", tac); 
							 gen_vec_attr(output, tac, root);
				break;

			case TAC_VEC_RD: printTacInfo("TAC_VEC_RD", tac); 
							 gen_vec_rd(output, tac, root);
				break;

			//case TAC_WHILE: printTacInfo("TAC_WHILE", tac); 
			//	break;

			case TAC_LABEL: printTacInfo("TAC_LABEL", tac); 
							gen_label(output, tac);
				break;

			case TAC_IFZ: printTacInfo("TAC_IFZ", tac); 
						  gen_if(output, tac);
				break;

			case TAC_JUMP: printTacInfo("TAC_JUMP", tac); 
						   gen_jump(output, tac);
				break;

			case TAC_ARG_LIST: printTacInfo("TAC_ARG_LIST", tac); 
							   gen_arg(output, tac);
				break;

			case TAC_PARAM_LIST: printTacInfo("TAC_PARAM_LIST", tac); 
								gen_param(output, tac, root);
				break;

			case TAC_FUNCALL: printTacInfo("TAC_FUNCALL", tac); 
							  gen_funcall(output, tac);
				break;

			// FALTA!

			case TAC_OR: printTacInfo("TAC_OR", tac); 
				break;

			case TAC_AND: printTacInfo("TAC_AND", tac); 
				break;

			case TAC_CALL: printTacInfo("TAC_CALL", tac); 
				break;

			//case TAC_ARG: printTacInfo("TAC_ARG", tac); 
			//	break;

			case TAC_READ: printTacInfo("TAC_READ", tac); 
				break;

			default: fprintf(stderr, "TAC_UNKNOWN"); 
				break;
				
		}
	fprintf(stderr, ")\n");

	}

	fprintf(stderr, "\nEXITED GEN.\n");

}

