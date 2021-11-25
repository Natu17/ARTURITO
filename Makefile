all:
	yacc -d Grammar/grammar.y
	lex Grammar/compiller.l
	gcc -o parser lex.yy.c y.tab.c -ly