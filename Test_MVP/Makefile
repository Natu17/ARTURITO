# taken from https://github.com/meyerd/flex-bison-example/blob/master/Makefile

all: css_wizard
	@echo "COMPILED TEST_MVP"

y.tab.c y.tab.h: grammar.y
	yacc -Wcex -d grammar.y

lex.yy.c: y.tab.h
	lex compiler.l

css_wizard: lex.yy.c y.tab.c y.tab.h
	gcc -o parser lex.yy.c y.tab.c ../SyntaxTree/node.c -ly

clean:
	rm -f lex.yy.c y.tab.c y.tab.h