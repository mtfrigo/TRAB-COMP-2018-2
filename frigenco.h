#include "tacs.h"

void gen_assembly(TAC*node, FILE* output, AST *root);
void gen_var_declaration(FILE* output, AST *node);
void gen_vec_declaration(FILE* output, AST *node);
void gen_beginfun(FILE* output, TAC *tac);
void gen_var_attr(FILE* output, TAC *tac, AST* node);
void gen_vec_attr(FILE* output, TAC *tac, AST* node);
void gen_numeric_expr(FILE *output, TAC *tac);
void gen_vec_rd(FILE *output, TAC *tac, AST* root);
void gen_return(FILE* output, TAC *tac);
void gen_param(FILE *output, TAC* tac, AST *root);
void gen_arg(FILE *output, TAC* tac);

void get_temps(FILE* output, AST *root);
void get_print_parameters(FILE* output, AST *node, AST *root, int *count);
int getAlign(int type, int n);
void get_declarations(FILE* output, AST *node);

AST* findDecNode(char *text, AST* root);
void printTacInfo(char *type, TAC* tac);



