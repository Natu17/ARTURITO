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
"H1"                           { yylval.operation = H1; return H1; }
"Selector"                     { yylval.operation = SELECTOR; return SELECTOR; }
"String"                       { yylval.operation = STR; return STR; }
"<="                           { yylval.operation = LE; return LE; }
">="                           { yylval.operation = GE; return GE; }
"=="                           { yylval.operation = EQ; return EQ; }
{ID}                           { yylval.string = strdup(yytext); return ID; }
{WORD}                         { yylval.string = strdup(yytext); return STR_LITERAL; }
{BLANK_LINE}                   { yylineno++; }
{WHITESPACE}                  { /* Ignore */}
{DIGIT}*                       { yylval.int_value  = atoi(yytext); return INT_LITERAL; }
.                              { yylval.operation = yytext[0]; return yytext[0]; }

%%

int yywrap(void){
    return 1;
}