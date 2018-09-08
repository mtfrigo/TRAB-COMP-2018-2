#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define IF 256
#define WHILE 257
#define THEN 258
#define DO 259
#define NUM 260
#define ID 261

int func_BL();
int func_CMDL();
int func_CMD();
int func_RESTO();
int func_IF();
int func_ASS();
int func_WHI();
int func_L();
int func_E();

int Entrada[15] = {IF, ID, THEN, '{', ID, '=', NUM, ';', '*', ID, '=', NUM, '}', '$'};
int Atual = 0;
int tok = 0;

int le_tok(){
    return Entrada[Atual++];
}

int main(){
    printf("Sou um analisador...\n");
    tok = le_tok();
    if(func_CMD())
        if(tok == '$')
            printf("Success! CARALHO\n");
        else
            printf("Ok, ok, but there is waste at the end!\n");
    else
        printf("Wrong program, not a CMD...\n");
}

int func_CMD(){
    printf("Sou uma CMD: Tok = %d\n", tok);
    if(tok == IF)
        if(func_IF())
            return TRUE;
        else
            return FALSE;
    else if(tok == '*' || tok == NUM || tok == ID)
        if(func_ASS())
            return TRUE;
        else
            return FALSE;
    else if(tok == WHILE)
        if(func_WHI())
            return TRUE;
        else
            return FALSE;
    else if(tok == '{')
        if(func_BL())
            return TRUE;
        else
            return FALSE;
    else 
        return FALSE;
}

int func_IF(){
    printf("Sou uma IF: tok = %d\n", tok);
    if(tok == IF){
        tok = le_tok();
        if(func_E()){
            if(tok == THEN){
                tok = le_tok();
                if(func_CMD())
                    return TRUE;
                else
                    return FALSE;
            }
            else
                return FALSE;
        }
        else
            return FALSE;
    }
    else
        return FALSE;
}

int func_WHI(){

}

int func_CMDL(){
    printf("Sou uma CMDL: tok = %d\n", tok);

    if(func_CMD()){
        if(func_RESTO())
            return TRUE;
        else
            return FALSE;
    }
    else 
        return FALSE;
}

int func_ASS(){
    printf("Sou uma ASS: tok = %d\n", tok);
    if(func_L()){
        if(tok == '='){
            tok = le_tok();
            if(func_E())
                return TRUE;
            else
                return FALSE;
        }
        else
            return FALSE;
    }
    else
        return FALSE;
}

int func_L(){
    printf("Sou uma L: tok = %d\n", tok);
    if(tok == '*'){
        tok = le_tok();
        if(func_E())
            return TRUE;
        else
            return FALSE;
    }
    else{
        if (func_E())
            return TRUE;
        else
            return FALSE;
    }
}

int func_E(){
    printf("Sou uma E: tok = %d\n", tok);
    if( tok == NUM || tok == ID){
        tok = le_tok();
        return TRUE;
    }
    else
        return FALSE;
}

int func_BL(){
    printf("Sou uma BL: tok = %d\n", tok);
    if(tok == '{'){
        tok = le_tok();
        if(func_CMDL()){
            if(tok == '}'){
                tok = le_tok();
                return TRUE;
            }
            else
                return FALSE;
        }
        else
            return FALSE;
    }
    else
        return FALSE;
}

int func_RESTO(){
    printf("Sou uma RESTO: tok = %d\n", tok);
    if(tok == ';'){
        tok = le_tok();
        if(func_CMDL())
            return TRUE;
        else
            return FALSE;
    }
    else
        return TRUE;
}