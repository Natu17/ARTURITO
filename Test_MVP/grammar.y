%code requires {
        #include <stdio.h>
        #include <stdlib.h>
        
        #include "../SyntaxTree/include/node.h"

        extern int yylineno;
        int yylex();
        void yyerror(const char *s);
}

%union{
  char * string;
  int operation;
  int int_value;
  Node* node;
}

%nonassoc STATEMENT_LIST


%token<string> NAME VALUE
%token<operation> NEW INT DOUBLE STR COLOR SELECTOR DIV P BODY H1 H2 ID CLASS, ASSIGN
%token<operation> IF WHILE START END
%token<int_value> INT_LITERAL

%right "="
%left AND OR 
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left NOT
%left '('
%right ')'

%type <node> STATMENTS STATMENT EXP LIST_ARG VALUES NOT_ID_NUM ARITH CND BLOCK
%type <operation> '<' '>' '(' ')' '{' '}'

%start PROGRAM

%%

PROGRAM     : MAIN { printf("Finished Parsing =)\n"); }

MAIN        : STATMENTS {}

STATMENTS   : STATMENT STATMENTS {$$ = create_node(STATEMENT_LIST, $1, $2, yylineno); }
            |      { $$ = NULL; }
            ;

STATMENT    : CND  { $$ = $1; }
            ;

BLOCK       : '{' STATMENTS '}'  { $$=$2; }
            |  { $$=NULL; }

CND         : IF '(' EXP ')' BLOCK {$$ = create_if_node($3, $5, NULL, yylineno);}
            ;

EXP         : ARITH { $$ = $1;}
            | VALUES      {return 0;}
            ;

VALUES      : NOT_ID_NUM { $$=$1; }
            ;   

NOT_ID_NUM  : INT_LITERAL  {$$ = create_int_node($1, yylineno);}
            ;

ARITH       : NOT_ID_NUM '>' NOT_ID_NUM  { $$ = create_node($2, $1, $3, yylineno); }
            | NOT_ID_NUM '<' NOT_ID_NUM  { $$ = create_node($2, $1, $3, yylineno); }
            ;
            
%%

/* int yywrap(){
        return 1;
}  */

int main() {
    printf("Hello world\n");
    int ret = yyparse();
    exit(0);
} 