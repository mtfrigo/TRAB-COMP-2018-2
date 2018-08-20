

# Trabalho de Compiladores

Professor: Marcelo Johann.

Disciplina: Compiladores (INF01147).

Semestre: 2018/2.

http://www.inf.ufrgs.br/~johann/comp

## Getting Started
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

or 

```
make
./etapa1 input.txt
```

# Etapa 1

O trabalho consiste na implementação de um compilador funcional. 
Esta primeira etapa do trabalho consiste em fazer um analisador léxico utilizando a ferramenta de geração de reconhecedores lex (ou flex) e inicializar uma tabela de símbolos encontrados. 

## Funcionalidades

* reconhecer as expressões regulares que descrevem cada tipo de lexema;

Status: OK.

* classificar os lexemas reconhecidos em tokens retornando as constantes definidas no arquivo tokens.h fornecido ou codigos ascii para caracteres simples;

Status: não implementada.

* incluir os identificadores e os literais (inteiros, caracteres e strings) em uma tabela de símbolos implementada com estrutura hash;

Status: Falta para string (qual a diferença de string e identificador?).

* controlar o número de linha do arquivo fonte, e fornecer uma função declarada como int getLineNumber(void) a ser usada nos testes e pela futura análise sintática;

Status: não implementada.

* ignorar comentários no formato C99 de única linha e múltiplas linhas;

Status: não implementada.

* informar erro léxico ao encontrar caracteres inválidos na entrada, retornando o token de erro;

Status: não implementada.

* definir e atualizar uma variável global e uma função int isRunning(void), que mantém e retorna valor true (diferente de 0) durante a análise e muda para false (igual a 0) ao encontrar a marca de fim de arquivo; 

Status: não implementada.

## Descrição dos tokens 

  Existem tokens que correspondem a caracteres particulares, como vírgula, ponto-e-vírgula,
parênteses, para os quais é mais conveniente usar seu próprio código ascii, convertido para
inteiro, como valor de retorno que os identifica. Para os tokens compostos, como palavras
reservadas e identificadores, cria-se uma constante (#define em C ANSI) com um código
maior do que 255 para representá-los.

  Os tokens representam algumas categorias diferentes, como palavras reservadas, operadores
de mais de um caractere e literais, e as constantes definidas no código do trabalho são
precedidas por um prefixo para melhor identificar sua função, separando-as de outras
constantes que serão usadas no compilador. 

## Palavras reservadas

As palavras reservadas da linguagem são: 

```
char, int, float, if, then, else, while, or, and, not, read, print e return.
```

Para cada uma deve ser retornado o token correspondente.

## Caracteres especiais 

Os caracteres simples especiais empregados pela linguagem são listados abaixo (estão
separados apenas por espaços), e devem ser retornados com o próprio código ascii convertido
para inteiro. Você pode fazer isso em uma única regra léxica que retorna yytext[0]. São
eles: 

```
, ; : d b q p { } + - * / < > = ! & $ #
```

## Operadores Compostos

A linguagem possui, além dos operadores representados por alguns dos caracteres acima,
operadores compostos, que necessitam mais de um caractere (na verdade, somente dois) para
serem representados no código fonte. São somente seis, quatro operadores relacionais e dois
operadores lógicos, conforme a tabela abaixo: 

| Source Representation  | Returned Token |
| ------------- | ------------- |
| <=  | OPERATOR_LE  |
| >=  | OPERATOR_GE  |
| ==  | OPERATOR_EQ  |

## Identificadores

Os identificadores da linguagem são usados para designar variáveis, vetores e nomes de
funções, são formados por uma sequência de um ou mais caracteres alfabéticos, excluindo os
caracteres **‘d' ‘b' ‘q' ‘p'**, incluindo underline **(´_´)**, e permitindo dígitos **(´0´-´9´)** em qualquer
posição, inclusive no início. Um identificador deve ter, entretanto, pelo menos um caractere
não numérico, para se distinguir de literal inteiro, como definido abaixo.

## Literais

Literais são formas de descrever constantes no código fonte. 
Literais inteiros são representados como repetições de um ou mais dígitos decimais. 
Literais reais são formados por duas sequências de um ou mais dígitos decimais, contendo um ponto decimal entre elas, sem espaços. 
Literais do tipo caracter são representados por um único caractere entre aspas simples, como por exemplo: **´a´, ´X´, ´-´**. 
Literais do tipo string são qualquer sequência de caracteres entre aspas duplas, como por exemplo "meu nome" ou "Mensagem!", e servem apenas para imprimir mensagens com o comando ´print´. 
Strings consecutivas não podem ser consideradas como apenas uma, o que significa que o caractere de aspas duplas não pode fazer parte de uma string. 
Para incluir o caracter de aspas duplas e final de linha, devem ser usadas sequências de escape, como ** "\"" e "\n". **

## Controle e organização do seu código fonte 

Você deve manter o arquivo tokens.h intacto, e separar a sua função main em um arquivo especial chamado main.c, já que a função main não pode estar contida no código de scanner.l. 
Isso é necessário para facilitar a automação dos testes, que utilizará uma função main especial escrita pelo professor, substituindo a que você escreveu para teste e desenvolvimento. 
Você deve usar essa estrutura de organização, manter os nomes tokens.h e scanner.l. 
Instruções mais detalhadas sobre o formato de submissão do trabalho e cuidados com detalhes específicos estão em outro documento separado. 

## Atualizações e Dicas 

Verifique regularmente a página da disciplina e o final desse documento para informar-se de alguma eventual atualização que se faça necessária ou dicas sobre estratégias que o ajudem a resolver problemas particulares. 
Em caso de dúvida, consulte o professor. 

# Etapa 2

Não disponível.

## Authors

* **Matheus Frigo** - [xfrigo](https://github.com/xfrigo)
* **Gerônimo Acosta** - [GerVeit](https://github.com/gerveit)

