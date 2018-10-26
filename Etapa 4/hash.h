#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HASH_SIZE 997
#define STRING_SIZE 100 

#define SYMBOL_LITINT 1
#define SYMBOL_IDENTIFIER 2
#define SYMBOL_SCALAR 3
#define SYMBOL_VECTOR 4
#define SYMBOL_FUNCTION 5

#define DATATYPE_INT 1
#define DATATYPE_CHAR 2
#define DATATYPE_FLOAT 3


typedef struct hash_node
{
    int type;
    int datatype;
    char *text;
    struct hash_node *next;

} HASH_NODE;

void hashInit (void);
int hashAddress(char *text);
HASH_NODE* hashInsert(int type, char *text);
HASH_NODE* hashFind(char *text);
void hashPrint(void);
void hashCheckUndeclared();
void hashSetType(char * text, int type);

#endif
