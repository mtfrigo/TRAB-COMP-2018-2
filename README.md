

# Trabalho de Compiladores

Professor: Marcelo Johann.

Disciplina: Compiladores (INF01147).

Semestre: 2018/2.

http://www.inf.ufrgs.br/~johann/comp

* [Etapa 1](#etapa-1)
* [Etapa 2](#etapa-2)

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

- [X] reconhecer as expressões regulares que descrevem cada tipo de lexema;

- [X] classificar os lexemas reconhecidos em tokens retornando as constantes definidas no arquivo tokens.h fornecido ou codigos ascii para caracteres simples;

- [X] incluir os identificadores e os literais (inteiros, caracteres e strings) em uma tabela de símbolos implementada com estrutura hash;

- [X] controlar o número de linha do arquivo fonte, e fornecer uma função declarada como int getLineNumber(void) a ser usada nos testes e pela futura análise sintática;

- [X] ignorar comentários no formato C99 de única linha e múltiplas linhas;

- [X] informar erro léxico ao encontrar caracteres inválidos na entrada, retornando o token de erro;

- [X] definir e atualizar uma variável global e uma função int isRunning(void), que mantém e retorna valor true (diferente de 0) durante a análise e muda para false (igual a 0) ao encontrar a marca de fim de arquivo; 

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

O trabalho consiste na implementação de um compilador para a linguagem que chamaremos a
partir de agora de **dbqp182**. Na segunda etapa do trabalho é preciso fazer um analisador
sintático utilizando a ferramenta de geração de reconhecedores yacc (ou bizon) e completar o
preenchimento da tabela de símbolos encontrados, associando os valores e tipos corretos aos
tokens.

## Funcionalidades

- [ ] o programa principal deve chamar uma única vez a rotina yyparse para reconhecer
programas que fazem parte da linguagem, e se concluída com sucesso, a análise deve
retornar o valor 0 com exit(0); 

- [ ] imprimir uma mensagem de erro sintático para os programas não reconhecidos,
informando a linha onde o erro ocorreu, e retornar o valor 3 como código genérico de
erro sintático, chamando exit(3);

- [ ] os nodos armazenados na tabela hash devem distinguir entre os tipos de símbolos
armazenados, e o nodo deve ser associado ao token retornado através da atribuição
para yylval.symbol; 

## Descrição Geral da Linguagem

Um programa na linguagem dbqp182 é composto por um conjunto de declarações de funções ou declarações de variáveis, globais, que podem aparecer em qualquer ordem. 

As declarações de variáveis globais devem ser terminadas por ponto e vírgula, as funções não. 

Cada função é descrita por um cabeçalho seguido de seu corpo, sendo que o corpo da função é um bloco, como definido adiante.

Os comandos podem ser de atribuição, controle de fluxo ou os comandos read, print e return. Um bloco também é considerando sintaticamente como um comando, podendo aparecer no lugar de qualquer comando.

### Declarações de variáveis globais

As variáveis são declaradas pela sequência de seu tipo, nome, sinal de igual e o valor de inicialização, que é obrigatório. 

A linguagem inclui também a declaração de vetores, feita pela definição de seu tamanho inteiro positivo entre ‘q’ e ‘p’, colocada imediatamente à direita do nome. 

No caso dos vetores, a inicialização é opcional, e quando presente, será dada pela  sequência de valores literais separados por caracteres em branco, entre um sinal de dois pontos (“:”) após o tamanho e o terminador ponto-e-vírgula. 

Se não estiver presente, o terminador ponto-e-vírgula segue imediatamente o tamanho entre ‘q’ e ‘p’. 

Variáveis e vetores podem ser dos tipos char, int, float. 

Os valores de inicialização podem ser literais inteiros, literais reais ou literais de caracteres entre aspas simples. 

### Definições de funções

Cada função é definida por seu cabeçalho seguido de seu corpo. 

O cabeçalho consiste no tipo do valor de retorno, seguido do nome da função e depois de uma lista, possivelmente vazia, entre ‘d’ e ‘b’, de parâmetros de entrada, separados por vírgula, onde cada parâmetro é definido por tipo e nome, e não podem ser do tipo vetor. 

O corpo da função é composto por um bloco, como definido adiante.

### Bloco de Comandos

Um bloco de comandos é definido entre chaves, e consiste em uma sequência, possivelmente vazia, de comandos, terminados por ponto-e-vírgula. 

O símbolo de ponto-e-vírgula, por definição, está associado à lista de comandos presentes dentro de um bloco, e não a cada comando em si. 

Considerando que os comandos poderão aparecer recursivamente dentro de outros comandos, não é necessário e nem permitido que cada um deles venha acompanhado de um ponto-e-vírgula adicional, mas apenas quando ocorrem na formação da lista dentro do bloco. 

Um bloco de comandos é considerado como um comando único simples, recursivamente, e pode ser utilizado em qualquer construção que aceite um comando simples.

### Comandos simples

Os comandos da linguagem podem ser: atribuição, construções de controle de fluxo, read, print, return e comando vazio. 

O comando vazio segue as mesmas regras dos demais, sendo terminado por ponto-e-vírgula quando está na lista do bloco, ou não quando estiver dentro de um comando recursivo. 

Na atribuição usa-se uma das seguintes formas: 

```
variável = expressão
vetor q expressão p = expressão 
```

Os tipos corretos para o assinalamento e para o índice serão verificados somente na análise semântica. 

O comando read é identificado pela palavra reservada read, seguida de variável, na qual o valor lido da entrada padrão, se disponível e compatível, será colocado. 

Somente variáveis escalares são aceitas no comando read, e não vetores ou posições de vetores. 

O comando print é identificado pela palavra reservada print, seguida de uma lista de elementos separados por vírgula, onde cada elemento pode ser um string ou uma expressão aritmética a ser impressa. 

O comando return é identificado pela palavra reservada return seguida de uma expressão que dá o valor de retorno. 

Os comandos de controle de fluxo são descritos adiante. 



### Expressões Aritméticas e Lógicas

As expressões aritméticas têm como folhas identificadores, opcionalmente seguidos de expressão inteira entre ‘q’ e ‘p’, para acesso a posições de vetores, ou podem ser literais numéricos e ASCII. 

As expressões aritméticas podem ser formadas recursivamente com operadores aritméticos, assim como permitem o uso de ‘d’ e ‘b’ para associatividade.

Expressões Lógicas (Booleanas) podem ser formadas através dos operadores relacionais aplicados a expressões aritméticas, ou de operadores lógicos aplicados a expressões lógicas, recursivamente. 

Os operadores válidos são: +,-,*,/,<,>,and,or,not,<=,>= e ==, listados na etapa1 representados com um ou mais de um caractere. 

Expressões também podem ser formadas considerando literais do tipo caractere. Nesta etapa do trabalho, porém, não haverá distinção alguma entre expressões aritméticas, inteiras, de caractere ou lógicas. 

A descrição sintática deve aceitar qualquer operador e sub-expressão de um desses tipos como válidos, deixando para a análise semântica das próximas etapas verificar a validade dos operandos e operadores. 

Finalmente, um operando possível de expressão é uma chamada de função, feita pelo seu nome, seguido de lista de argumentos entre ‘d’ e ‘b’, separados por vírgula.

### Comandos de controle de fluxo

Para controle de fluxo, a linguagem possui as construções condicionais listadas abaixo

```
if expressão then comando
if expressão then comando else comando
while expressão comando 
```

## Tipos e Valores na tabela de Símbolos

A tabela de símbolos até aqui poderia representar o tipo do símbolo usando os mesmos #defines criados para os tokens (agora gerados pelo yacc). 

Mas logo será necessário fazer mais distinções, principalmente pelo tipo dos identificadores. 

Assim, é preferível criar códigos especiais para símbolos, através de definições como: 

```
#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_REAL 2
...
#define SYMBOL_IDENTIFIER 7
```

## Controle e organização do seu códugo fonte

O arquivo tokens.h usado na etapa1 não é mais necessário. 

Você deve seguir as demais regras especificadas na etapa1, entretanto. 

A função main escrita por você será usada sem alterações para os testes da etapa2. 

Você deve utilizar um Makefile para que seu programa seja completamente compilado com o comando make. 

Utilize o exemplo disponibilizado na página como referência. 

O formato de entrega será o mesmo da etapa1, e todas as regras devem ser observadas, apenas alterando o nome do arquivo executável e do arquivo .tgz para “etapa2”.

## Authors

* **Matheus Frigo** - [xfrigo](https://github.com/xfrigo)
* **Gerônimo Acosta** - [GerVeit](https://github.com/gerveit)

