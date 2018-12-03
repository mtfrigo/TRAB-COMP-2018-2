#include "assembly_gen.h"
#include "hash.h"
#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///////////////////////////////////////////////////////////////////////////////////////////////////
char reg_temp[32] = "%edx";
int genco_initialized = 0;

void gencoVarDeclaration(FILE* output, TAC *tac);
void gencoLongLiteralDeclaration(FILE *output, HASH_NODE *hashNode, TAC* tac);
void gencoByteLiteralDeclaration(FILE *output, HASH_NODE *hashNode, TAC* tac);

void gencoArrayDeclaration(FILE* output, TAC *tac);
void gencoByteArrayDeclaration(FILE *output, HASH_NODE *hashNode, TAC *tac);
void gencoLongArrayDeclaration(FILE* output, TAC *tac);

void initTempVar(FILE *output);
void initParamVar(FILE *output);
///////////////////////////////////////////////////////////////////////////////////////////////////

void initTempVar(FILE *output){
    HASH_NODE *node;
    int i;
    for(i = 0; i < HASH_SIZE; i++) {
        for (node = Table[i]; node ; node = node->next){
            if(node->datatype == DATATYPE_TEMP){
                fprintf(output, "\t.globl\t%s\n", node->text);
                fprintf(output, "\t.data\n");
                fprintf(output, "\t.align\t4\n");
                fprintf(output, "\t.size\t%s, 4\n", node->text);
                fprintf(output, "%s:\n", node->text);
                fprintf(output, "\t.zero\t4\n");
            }
        }
    }
}

void initParamVar(FILE *output) {
    //printf("teste1\n");
    LIST_FUNC_DECL *func;
    AST *lstArg;
    AST *arg;
    for(func = listFuncDecl; func; func = func->next) {
        //printf("teste2\n");
        lstArg = func->ast_node->sons[1];

        while(lstArg) {
            arg = lstArg->sons[0];
            //printf("Datatype = %d\n", arg->dataType);
            if(arg->dataType == DATATYPE_DOUBLE) {
                fprintf(output, "\t.globl\t%s\n", arg->symbol->text);
                fprintf(output, "\t.data\n");
                fprintf(output, "\t.align\t8\n");
                fprintf(output, "\t.size\t%s, 8\n", arg->symbol->text);
                fprintf(output, "%s:\n", arg->symbol->text);
                fprintf(output, "\t.long\t0\n");
            }
            else if(arg->dataType == DATATYPE_INTEIRO || arg->dataType == DATATYPE_BOOLEANO || arg->dataType == DATATYPE_LONG ) {
                fprintf(output, "\t.globl\t%s\n", arg->symbol->text);
                fprintf(output, "\t.data\n");
                fprintf(output, "\t.align\t4\n");
                fprintf(output, "\t.size\t%s, 4\n", arg->symbol->text);
                fprintf(output, "%s:\n", arg->symbol->text);
                fprintf(output, "\t.long\t0\n");
            }
            else if(arg->dataType == DATATYPE_SHORT) {
                fprintf(output, "\t.globl\t%s\n", arg->symbol->text);
                fprintf(output, "\t.data\n");
                fprintf(output, "\t.align\t2\n");
                fprintf(output, "\t.size\t%s, 2\n", arg->symbol->text);
                fprintf(output, "%s:\n", arg->symbol->text);
                fprintf(output, "\t.long\t0\n");
            }
            else if(arg->dataType == DATATYPE_CHAR) {
                fprintf(output, "\t.globl\t%s\n", arg->symbol->text);
                fprintf(output, "\t.data\n");
                fprintf(output, "\t.size\t%s, 1\n", arg->symbol->text);
                fprintf(output, "%s:\n", arg->symbol->text);
            }
            lstArg = lstArg->sons[1];
        }
    }
}

void gencoLongArrayDeclaration(FILE *output, TAC *tac){
    int arraySize = atoi(tac->op1->text);
    fprintf(output, "\t.globl\t%s\n", tac->res->text);
    fprintf(output, "\t.data\n");
    fprintf(output, "\t.size\t%s, %d\n", tac->res->text, arraySize * 4);
    fprintf(output, "%s:\n", tac->res->text);

    TAC *temp = tac->next;
    if(tac->op2){
        int i;
        for (i = 0; i < arraySize; ++i, temp = temp->next) {
            fprintf(output, "\t.long\t%d\n", atoi(temp->res->text));
        }
    }
}
void gencoByteArrayDeclaration(FILE *output, HASH_NODE *hashNode, TAC *tac) {
    int arraySize = atoi(tac->op1->text);
    fprintf(output, "\t.globl\t%s\n", tac->res->text);
    fprintf(output, "\t.data\n");
    fprintf(output, "\t.size\t%s, %i\n", tac->res->text, arraySize);
    fprintf(output, "%s:\n", tac->res->text);

    int literalValue = 0;

    TAC *temp = tac->next;
    if(tac->op2) {
        int i;
        for (i = 0; i < arraySize; ++i, temp = temp->next) {
            if(hashNode->dataType == DATATYPE_CHAR) { // CHAR
                literalValue = temp->res->text[1];
            } else { // BOOL
                if(!strcmp(temp->res->text, "TRUE")){
                    literalValue = 1;
                } else {
                    literalValue = 0;
                }
            }
            fprintf(output, "\t.byte\t%d\n", literalValue);
        }
    }
}

void gencoArrayDeclaration(FILE* output, TAC *tac){
    HASH_NODE* hashNode = hashFind(tac->res?tac->res->text:NULL);
    if(hashNode) {
        switch(hashNode->dataType) {
            case DATATYPE_INTEIRO:
            case DATATYPE_REAL:
            case DATATYPE_STRING:
            case DATATYPE_BYTE:
            case DATATYPE_SHORT:
            case DATATYPE_LONG:
            case DATATYPE_FLOAT:
            case DATATYPE_DOUBLE:
                gencoLongArrayDeclaration(output, tac);
                break;
            case DATATYPE_CHAR:
            case DATATYPE_BOOLEANO:
                gencoByteArrayDeclaration(output, hashNode, tac);
                break;
        }
    }
}

void gencoVarDeclaration(FILE* output, TAC *tac) {
	HASH_NODE* hashNode = hashFind(tac->res?tac->res->text:NULL);
	if(hashNode) {
		switch(hashNode->dataType) {
            case DATATYPE_INTEIRO:
            case DATATYPE_REAL:
            case DATATYPE_STRING:
            case DATATYPE_BYTE:
            case DATATYPE_SHORT:
            case DATATYPE_LONG:
            case DATATYPE_FLOAT:
            case DATATYPE_DOUBLE:
				gencoLongLiteralDeclaration(output, hashNode, tac);
				break;
			case DATATYPE_CHAR:
			case DATATYPE_BOOLEANO:
				gencoByteLiteralDeclaration(output, hashNode, tac);
				break;
		}
	}
}

void gencoByteLiteralDeclaration(FILE* output, HASH_NODE *hashNode, TAC* tac) {
	fprintf(output, "\t.globl\t%s\n", tac->res->text);
	fprintf(output, "\t.data\n");
	fprintf(output, "\t.size\t%s, 1\n", tac->res->text);
	fprintf(output, "%s:\n", tac->res->text);
	int literalValue = 0;
	if(hashNode->dataType == DATATYPE_CHAR) { // CHAR
		literalValue = tac->op1->text[1];
	} else { // BOOL
		if(!strcmp(tac->op1->text, "TRUE")){
			literalValue = 1;
		} else {
			literalValue = 0;
		}
	}
	fprintf(output, "\t.byte\t%d\n", literalValue);
}

void gencoLongLiteralDeclaration(FILE* output, HASH_NODE *hashNode, TAC* tac) 
{
    if(hashNode->dataType == DATATYPE_DOUBLE) {
	    fprintf(output, "\t.globl\t%s\n", tac->res->text);
	    fprintf(output, "\t.data\n");
	    fprintf(output, "\t.align\t8\n");
	    fprintf(output, "\t.size\t%s, 8\n", tac->res->text);
	    fprintf(output, "%s:\n", tac->res->text);
	    fprintf(output, "\t.long\t%d\n", atoi(tac->op1->text));
    }
    else 
    {
        if(hashNode->dataType == DATATYPE_SHORT) 
        {
	        fprintf(output, "\t.globl\t%s\n", tac->res->text);
	        fprintf(output, "\t.data\n");
	        fprintf(output, "\t.align\t2\n");
	        fprintf(output, "\t.size\t%s, 2\n", tac->res->text);
	        fprintf(output, "%s:\n", tac->res->text);
    	    fprintf(output, "\t.long\t%d\n", atoi(tac->op1->text));
        }
        else
        {
	        fprintf(output, "\t.globl\t%s\n", tac->res->text);
	        fprintf(output, "\t.data\n");
	        fprintf(output, "\t.align\t4\n");
	        fprintf(output, "\t.size\t%s, 4\n", tac->res->text);
	        fprintf(output, "%s:\n", tac->res->text);
	        fprintf(output, "\t.long\t%d\n", atoi(tac->op1->text));
        }
    }
}

void gencoNumericOp(TAC* tac, FILE* output)  {
    char op[8];
    switch(tac->type){
        case TAC_ADD:
            strcpy(op, "addl");
            break;
        case TAC_SUB:
            strcpy(op, "subl");
            break;
        case TAC_MULT:
            strcpy(op, "imull");
            break;
        default:
            return;
            break;
    }

    if(tac->op1->type == TAC_LABEL) {
        fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
    }
    else{
        fprintf(output, "\tmovl\t$%s, %%eax\n", tac->op1->text);
    }

    if(tac->op2->type == TAC_LABEL) {
        fprintf(output, "\tmovl\t%s(%%rip), %%ebx\n", tac->op2->text);
    }
    else{
        fprintf(output, "\tmovl\t$%s, %%ebx\n", tac->op2->text);
    }

    fprintf(output, "\t%s\t%%ebx, %%eax\n", op);
    fprintf(output, "\tmovl\t%%eax, %s\n", tac->res->text);
}

void gen_assembly(TAC*node, FILE* output){

    if(!genco_initialized ) {
        initTempVar(output);
        initParamVar(output);
        genco_initialized  = 1;
    }
    int stop_declaration = 0;


	TAC *tac;
	for(tac = node; tac; tac = tac->next){
		switch(tac->type){
		case TAC_VAR:
			gencoVarDeclaration(output, tac);
			break;
        case TAC_ARRAY_DECLARADO:
            gencoArrayDeclaration(output, tac);
            break;
		case TAC_BEGIN_FUNCTION:
            if(strcmp(tac->res->text, "main") == 0) {
                fprintf(output, ".PINT:\n"
                                "\t.string\t\"%%d\\n\"\n"
                                ".RINT:\n"
                                "\t.string\t\"%%d\"\n"
                                ".PCHAR:\n"
                                "\t.string\t\"%%c\\n\"\n");

                stop_declaration = 1;
            }

            fprintf(output, "\t.globl\t%s\n", tac->res->text);
			fprintf(output, "%s:\n"
                            "\tpushq\t%%rbp\n"
                            "\tmovq\t%%rsp, %%rbp\n", tac->res->text);
			break;
		case TAC_END_FUNCTION:
			fprintf(output, "\tpopq\t%%rbp\n"
                            "\tret\n");
			break;
		case TAC_ADD:
		case TAC_SUB:
		case TAC_MULT:
			gencoNumericOp(tac, output);
			break;

        case TAC_ATRIBUICAO:
            //printf("%s: %d\n", tac->res->text, tac->op1->type);
            if(tac->op1->type == TAC_LABEL || tac->op1->type == SYMBOL_LIT) {
                fprintf(output, "\tmovl\t%s(%%rip), %%eax\n"
                                "\tmovl\t%%eax, %s(%%rip)\n", tac->op1->text, tac->res->text);
            }
            else {
                fprintf(output, "\tmovl\t$%s, %s(%%rip)\n", tac->op1->text, tac->res->text);
            }
            break;

        case TAC_ATRIBUICAO_ARRAY:
            // Valor
            if(tac->op2->type == TAC_LABEL) {
                fprintf(output, "\tmovl\t%s(%%rip), %%ebx\n", tac->op2->text);
            }
            else {
                fprintf(output, "\tmovl\t$%s, %%ebx\n", tac->op2->text);
            }
            // Posição do array
            if(tac->op1->type == TAC_LABEL) {
                fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
                fprintf(output, "\tcltq\n");
                fprintf(output, "\tmovl\t%%ebx, %s(,%%rax,4)\n", tac->res->text);
            }
            else {
                fprintf(output, "\tmovl\t%%ebx, %s+%s*4(%%rip)\n", tac->res->text, tac->op1->text);
            }

            break;


        case TAC_PRINT:
            if(tac->op1->dataType == DATATYPE_CHAR) {
                fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
                fprintf(output, "\tmovl\t%%eax, %%esi\n");
                fprintf(output, "\tmovl\t$.PCHAR, %%edi\n");
                fprintf(output, "\tcall\tprintf\n");
            }
            else if(tac->op1->type == TAC_LABEL)
            {
                fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
                fprintf(output, "\tmovl\t%%eax, %%esi\n");
                fprintf(output, "\tmovl\t$.PINT, %%edi\n");
                fprintf(output, "\tcall\tprintf\n");
            }
            else {
                fprintf(output, "\tmovl\t$%s, %%eax\n", tac->op1->text);
                fprintf(output, "\tmovl\t%%eax, %%esi\n");
                fprintf(output, "\tmovl\t$.PINT, %%edi\n");
                fprintf(output, "\tcall\tprintf\n");
            }
            break;

        case TAC_LABEL:
            // printf("%s: %d\n",tac->res->text, tac->type);
            // if(!stop_declaration || tac->type != TAC_SYMBOL)
                fprintf(output, "%s:\n", tac->res->text);
            break;

        case TAC_INCREMENT:
            fprintf(output, "\tmovl\t%s(%%rip), %%eax\n"
                            "\taddl\t$1, %%eax\n"
                            "\tmovl\t%%eax, %s(%%rip)\n"
                            , tac->res->text, tac->res->text);
            break;


        case TAC_LE:
            fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
            if(tac->op2->type == TAC_SYMBOL || tac->op2->type == SYMBOL_LIT_INTEGER) {
                fprintf(output, "\tcmpl\t$%s, %%eax\n", tac->op2->text);
            }
            else {
                // TODO - Verificar se comparação entre variáveis funciona
                fprintf(output, "\tmovl\t%s(%%rip), %%ecx\n", tac->op2->text);
                fprintf(output, "\tcmpl\t%%ecx, %%eax\n");
            }
            fprintf(output, "\tsetle\t%%al\n");
            break;

        case TAC_IFZ:
            if(tac->op1->dataType != DATATYPE_TEMPORARIO) {
                // TODO - Implementar caso seja para verificar uma variavel
                fprintf(output, "Nao era para ter parado aqui\n");
            }
            else {
                fprintf(output, "\tmovzbl\t%%al, %%eax\n");
            }
            fprintf(output, "\tjz\t%s\n", tac->res->text);
            break;

        case TAC_JUMP:
            fprintf(output, "\tjmp\t%s\n", tac->res->text);
            break;

        case TAC_READ:
            if(tac->op1->dataType == DATATYPE_INTEIRO) {
                fprintf(output, "\tmovl\t$%s, %%esi\n", tac->op1->text);
                fprintf(output, "\tmovl\t$.RINT, %%edi\n");
                fprintf(output, "\tmovl\t$0, %%eax\n");
                fprintf(output, "\tcall\t__isoc99_scanf\n");
            }
            break;

        case TAC_CALL:
            // TODO - Passagem de parâmetros
            fprintf(output, "\tcall\t%s\n", tac->op1->text);
            fprintf(output, "\tmovl\t%%eax, %s(%%rip)\n", tac->res->text);
            break;

        case TAC_RETURN:
            if(tac->op1->type == TAC_LABEL) {
                fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
            }
            else {
                fprintf(output, "\tmovl\t$%s, %%eax\n", tac->op1->text);
            }
            break;

        case TAC_ARG:
            if(tac->op1->type == TAC_LABEL) {
                fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
            }
            else {
                fprintf(output, "\tmovl\t$%s, %%eax\n", tac->op1->text);
            }
            fprintf(output, "\tmovl\t%%eax, %s(%%rip)\n", tac->res->text);
            break;
		}
	}
	genco_initialized  = 0;
}
