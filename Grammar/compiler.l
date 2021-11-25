%{
    #include "y.tab.h"

%}

WHITESPACE          ^[ \t]*\n
DIGIT               [0-9]
%%
"//"[^\n]*                  { /* Consume */}

"if"                        { yylval.operation = IF; return IF; }
"while"                     { yylval.operation = WHILE; return WHILE; }

"and"                       { yylval.operation = AND; return AND; }
"or"                        { yylval.operation = OR; return OR; }
"not"                       { yylval.operation = NOT; return NOT; }

"int"                       { yylval.operation = INT; return INT; }
"str"                       { yylval.operation = STR; return STR; }

"Color"                     { yylval.operation = COLOR; return COLOR; }
"Selector"                  { yylval.operation = SELECTOR; return SELECTOR; }
"Div"                       { yylval.operation = DIV; return DIV; }
"P"                         { yylval.operation = P; return P; }
"Body"                      { yylval.operation = Body; return Body; }
"H1"                        { yylval.operation = H1; return H1; }
"H2"                        { yylval.operation = H2; return H2; }
"Id"                        { yylval.operation = Id; return Id; }
"Class"                     { yylval.operation = Class; return Class; }

"+"                         { yylval.operation = SUM; return SUM; }
"*"                         { yylval.operation = MULT; return MULT; }
"-"                         { yylval.operation = SUB; return SUB; }    
"/"                         { yylval.operation = DIVIDE; return DIVIDE; }

">"                         { yylval.operation = LT; return LT; }
"<"                         { yylval.operation = GT; return GT; }
"<="                        { yylval.operation = LE; return LE; }
">="                        { yylval.operation = GE; return GE; }
"=="                        { yylval.operation = EQ; return EQ; }

"="                         { yylval.operation = ASSIGN; return ASSIGN}

";"                         { yylval.operation = END_STATEMENT; return END_STATEMENT;}

{WHITESPACE}                { /* Ignore whitespaces*/ }
{DIGIT}*                    { yylval.intValue  = atoi(yytext); return INT_VALUE; }
.                           { yylval.operation = yytext[0]; return yytext[0]; }

%%

int yywrap(void){
    return 1;
}
