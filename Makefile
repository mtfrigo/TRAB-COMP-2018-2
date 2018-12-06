etapa6: main.o hash.o lex.yy.o y.tab.o ast.o tacs.o semantic.o frigenco.o
	gcc main.o hash.o lex.yy.o y.tab.o ast.o tacs.o semantic.o frigenco.o -o etapa6

main.o: main.c
	gcc -c -Wall  main.c

ast.o: ast.c
	gcc -c -Wall ast.c

tacs.o: tacs.c
	gcc -c -Wall tacs.c

hash.o: hash.c
	gcc -c -Wall hash.c

semantic.o: semantic.c
	gcc -c -Wall semantic.c

frigenco.o: frigenco.c
	gcc -c -Wall frigenco.c

lex.yy.o: lex.yy.c
	gcc -c -Wall lex.yy.c

y.tab.o: y.tab.c
	gcc -c -Wall y.tab.c

lex.yy.c: y.tab.c scanner.l
	lex scanner.l

y.tab.c: parser.y
	yacc -d parser.y

clean:
	rm *.o etapa6 lex.yy.c y.tab.c
