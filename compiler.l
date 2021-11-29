%{
    #include <strings.h>
    #include "y.tab.h"
%}

BLANK_LINE          ^[ \t]*\n
DIGIT               [0-9]
START_COMMENT       \/\*
END_COMMENT         \*\/
WHITESPACE          [ \t]*
ID                  [a-zA-Z][a-zA-Z0-9_-]*
WORD                 \"[a-zA-Z0-9_-]*\"
DOUBLE              [0-9]+\.[0-9]+

%%
[\n]			               {yylineno++;}
\/\/(.*)                       { /* Remove comments */}
{START_COMMENT}.*{END_COMMENT} { /* Remove comments */}

"if"                           { yylval.operation = IF; return IF; }
"while"                        { yylval.operation = WHILE; return WHILE; }
"and"                          { yylval.operation = AND; return AND; }
"or"                           { yylval.operation = OR; return OR; }
"not"                          { yylval.operation = NOT; return NOT; }
"int"                          { yylval.operation = INT_TYPE; return INT_TYPE; }
"double"                       { yylval.operation = DOUBLE; return DOUBLE; }
"H1"                           { yylval.operation = H1; return H1; }
"H2"                           { yylval.operation = H2; return H2; }
"body"                         { yylval.operation = BODY; return BODY; }
"p"                            { yylval.operation = P; return P; }
"div"                          { yylval.operation = DIV; return DIV; }
"class"                        { yylval.operation = CLASS; return CLASS; }
"id"                           { yylval.operation = ID_TYPE; return ID_TYPE; }
"Selector"                     { yylval.operation = SELECTOR; return SELECTOR; }
"String"                       { yylval.operation = STR; return STR; }
"<="                           { yylval.operation = LE; return LE; }
">="                           { yylval.operation = GE; return GE; }
"=="                           { yylval.operation = EQ; return EQ; }
{ID}                           { yylval.string = strdup(yytext); return ID; }
{WORD}                         { yylval.string = strdup(yytext); return STR_LITERAL; }
{BLANK_LINE}                   { yylineno++; }
{WHITESPACE}                   { /* Ignore */}
{DIGIT}*                       { yylval.int_value  = atoi(yytext); return INT_LITERAL; }
{DOUBLE}                       { yylval.double_value  = atof(yytext); return DOUBLE_LITERAL; }
.                              { return *yytext; }


%%

int yywrap(void){
    return 1;
}