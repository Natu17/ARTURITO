%code requires {
        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>

        #include "SyntaxTree/include/node.h"
        #include "SyntaxTree/include/resolution.h"
        #include "SymbolTable/symbolTable.h"

        extern int yylineno;
        int yylex();
        void yyerror(Node* root, const char* msg);
}

%union{
  char * string;
  int operation;
  int int_value;
  double double_value;
  Node* node;
  Node* root_node;
}

%token<int_value> STATEMENT_LIST


%token<string> NAME VALUE
%token<operation> NEW INT_TYPE DOUBLE STR SELECTOR DIV P BODY H1 H2 CLASS VOID ID_TYPE 
%token<operation> IF WHILE REASSIGNMENT FUN_CALL PARAM
%token<int_value> INT_LITERAL
%token<double_value> DOUBLE_LITERAL
%token<string> STR_LITERAL

%right "="
%left AND OR 
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left NOT

%type <node> STATMENTS STATMENT EXP LIST_ARG VALUES NOT_ID_NUM ARITH CND BLOCK LOOP ASSIGN OP TYPE_MASTER TYPE_SON NOT_ID_STR REASSIGN 
%type<node> ARG CALL
%type <operation> '<' '>' ')' '(' '+' '-' '/' '*' LE GE EQ NE AND OR TYPE
%token<string> ID

%parse-param {Node* root}

%start PROGRAM

%%

PROGRAM     : MAIN { return 0; }

MAIN        : STATMENTS {memcpy(root, $1, sizeof(*root));}

STATMENTS   : STATMENT STATMENTS {$$ = create_node(STATEMENT_LIST, $1, $2, yylineno); }
            |      { $$ = NULL; }
            ;

STATMENT    : CND      { $$ = $1; }
            | LOOP     { $$ = $1;}
            | ASSIGN   { $$ = $1; }
            | REASSIGN { $$ = $1;}
            | CALL     { $$ = $1; }
            
            ;

ASSIGN      : TYPE ID '=' VALUES ';' { $$ = create_assignment_node($1, $2, $4, yylineno); } 
            | TYPE_MASTER ID '=' TYPE_SON ';' { $$ = create_assignment_node($1, $2, $4, yylineno); } 
          
REASSIGN    : ID '=' EXP ';' { $$ = create_assignment_node(REASSIGNMENT, $1, $3, yylineno);} 
            ;
CALL        : ID '(' LIST_ARG ')' ';' {$$ = create_function_node($1, $3, yylineno);}

LIST_ARG    : ARG {$$ = $1;}
            |     {$$ = NULL;}
            ; 

ARG         : EXP {$$ = $1;}
            | EXP ',' ARG  {$$ = concat_params($1, $3, yylineno); }
            ;

BLOCK       : '{' STATMENTS '}'  { $$=$2; }
            |  { $$=NULL; }
            ;

CND         : IF '(' EXP ')' BLOCK {$$ = create_if_node($3, $5, NULL, yylineno);}
            ;

LOOP        : WHILE '(' EXP ')' BLOCK {$$ = create_while_node($3, $5, yylineno);}

EXP         : EXP OP EXP  {$$ = create_node($2, $1, $3, yylineno);}
            | NOT EXP     {return 0;}
            | VALUES      {$$=$1;}
            ;

VALUES      : NOT_ID_NUM { $$=$1; }
            | NOT_ID_STR { $$=$1; }
            | ID         { $$=$1; }
            ;   

TYPE        : INT_TYPE  {$$=$1;}
            | STR       {$$=$1;}
            | DOUBLE    {$$=$1;}
            ;

NOT_ID_NUM  : INT_LITERAL  {$$ = create_int_node($1, yylineno);}
            | DOUBLE_LITERAL  {$$ = create_double_node($1, yylineno);}
            ; 

NOT_ID_STR  : STR_LITERAL  {$$ = create_str_node($1, yylineno);}
            ; 

OP          : '+' {$$='+';}
            | '-' {$$='-';}
            | '*' {$$='*';}
            | '/' {$$='/';}
            | '<' {$$='<';}
            | '>' {$$='>';}
            | LE  {$$=LE;}
            | GE  {$$=GE;}
            | EQ  {$$=EQ;}
            | NE  {$$=NE;}
            | AND {$$=AND;}
            | OR  {$$=OR;}
            ;


TYPE_MASTER : SELECTOR 
            ;

TYPE_SON    : H1    {$$ = create_especial_node($1, yylineno);}
            | H2    {$$ = create_especial_node($1, yylineno);}
            | DIV   {$$ = create_especial_node($1, yylineno);}
            | P     {$$ = create_especial_node($1, yylineno);}
            | BODY  {$$ = create_especial_node($1, yylineno);}
            | CLASS {$$ = create_especial_node($1, yylineno);}
            | ID_TYPE    {$$ = create_especial_node($1, yylineno);}
            ;
            
%%

void yyerror(Node* root, const char* msg) {
    fprintf(stderr, "%s\n", msg);
}

int main() {

    /* #ifdef YYDEBUG
      yydebug = 1;
    #endif */

    Node root;
    int ret = yyparse(&root);

    init();
    execute_tree(&root);
    exit(0);
} 