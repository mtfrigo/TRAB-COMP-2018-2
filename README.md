

# Trabalho de Compiladores

Professor: Marcelo Johann.
Disciplina: Compiladores (INF01147).
Semestre: 2018/2.

## Getting Started

bla bla

### Prerequisites

Install LEX.

### Installing

```
sudo apt-get install flex
```

## Running


```
lex scanner.l input.txt
gcc lex.yy.c
./a.out input.txt
```

# Etapa 1

O trabalho consiste na implementação de um compilador funcional. Esta primeira etapa do
trabalho consiste em fazer um analisador léxico utilizando a ferramenta de geração de
reconhecedores lex (ou flex) e inicializar uma tabela de símbolos encontrados. 

## Funcionalidades

* reconhecer as expressões regulares que descrevem cada tipo de lexema;

* classificar os lexemas reconhecidos em tokens retornando as constantes definidas no
arquivo tokens.h fornecido ou codigos ascii para caracteres simples;

* incluir os identificadores e os literais (inteiros, caracteres e strings) em uma tabela de
símbolos implementada com estrutura hash;

* controlar o número de linha do arquivo fonte, e fornecer uma função declarada como
int getLineNumber(void) a ser usada nos testes e pela futura análise sintática;

* ignorar comentários no formato C99 de única linha e múltiplas linhas;

* informar erro léxico ao encontrar caracteres inválidos na entrada, retornando o token
de erro;

* definir e atualizar uma variável global e uma função int isRunning(void), que
mantém e retorna valor true (diferente de 0) durante a análise e muda para false (igual
a 0) ao encontrar a marca de fim de arquivo; 


## Authors

* **Matheus Frigo** - [xfrigo](https://github.com/xfrigo)
* **Gerônimo Acosta** - [GerVeit](https://github.com/gerveit)

