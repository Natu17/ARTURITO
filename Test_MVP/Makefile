# taken from https://github.com/meyerd/flex-bison-example/blob/master/Makefile

C_FILES=lex.yy.c y.tab.c ../SyntaxTree/node.c ../SyntaxTree/resolution.c ../SymbolTable/symbolTable.c
all: css_wizard
	@echo "COMPILED TEST_MVP"

y.tab.c y.tab.h: grammar.y
	yacc -d grammar.y

lex.yy.c: y.tab.h
	lex compiler.l

css_wizard: lex.yy.c y.tab.c y.tab.h
	gcc -o parser ${C_FILES}

clean:
	rm -f lex.yy.c y.tab.c y.tab.h parser parser_debug

debug: debug_wizard
	echo "Finished Debugging Session"

debug_wizard: lex.yy.c y.tab.c y.tab.h
	gcc -g -o parser_debug ${C_FILES}
