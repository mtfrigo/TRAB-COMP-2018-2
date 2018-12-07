#include "tacs.h"

void gen_assembly(TAC*node, FILE* output, AST *root);
void get_declarations(FILE* output, AST *node);
void gen_var_declaration(FILE* output, AST *node);
void gen_vec_declaration(FILE* output, AST *node);
int getAlign(int type, int n);
void printTacInfo(char *type, TAC* tac);
void gen_beginfun(FILE* output, TAC *tac);
void gen_var_attr(FILE* output, TAC *tac, AST* node);
void gen_vec_attr(FILE* output, TAC *tac, AST* node);
void get_print_parameters(FILE* output, AST *node, AST *root, int *count);
AST* findDecNode(char *text, AST* root);