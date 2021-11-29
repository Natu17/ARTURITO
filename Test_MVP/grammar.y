%code requires {
        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>

        #include "../SyntaxTree/include/node.h"
        #include "../SyntaxTree/include/resolution.h"
        #include "../SymbolTable/symbolTable.h"

        extern int yylineno;
        int yylex();
        void yyerror(Node* root, const char* msg);
}

%union{
  char * string;
  int operation;
  int int_value;
  Node* node;
  Node* root_node;
}

%token<int_value> STATEMENT_LIST


%token<string> NAME VALUE
%token<operation> NEW INT_TYPE DOUBLE STR SELECTOR DIV P BODY H1 H2 CLASS VOID ID_TYPE 
%token<operation> IF WHILE
%token<int_value> INT_LITERAL
%token<string> STR_LITERAL

%right "="
%left AND OR 
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left NOT
%left '('
%right ')'

%type <node> STATMENTS STATMENT EXP LIST_ARG VALUES NOT_ID_NUM ARITH CND BLOCK LOOP ASSIGN OP TYPE_MASTER TYPE_SON NOT_ID_STR 
%type <operation> '<' '>' '(' ')' '+' '-' '/' '*' LE GE EQ NE AND OR TYPE
%token<string> ID

%parse-param {Node* root}

%start PROGRAM

%%

PROGRAM     : MAIN { printf("Finished Parsing :)\n"); }

MAIN        : STATMENTS {memcpy(root, $1, sizeof(*root));}

STATMENTS   : STATMENT STATMENTS {$$ = create_node(STATEMENT_LIST, $1, $2, yylineno); }
            |      { $$ = NULL; }
            ;

STATMENT    : CND  { $$ = $1; }
            | LOOP { $$ = $1;}
            | ASSIGN { $$=$1; }
            ;

ASSIGN      : TYPE ID '=' VALUES ';' { $$ = create_assignment_node($1, $2, $4, yylineno); } 
            | TYPE_MASTER ID '=' TYPE_SON ';' { $$ = create_assignment_node($1, $2, $4, yylineno); } 
            ;

BLOCK       : '{' STATMENTS '}'  { $$=$2; }
            |  { $$=NULL; }

CND         : IF '(' EXP ')' BLOCK {$$ = create_if_node($3, $5, NULL, yylineno);}
            ;

LOOP        : WHILE '(' EXP ')' BLOCK {$$ = create_while_node($3, $5, yylineno);}

EXP         : EXP OP EXP  {$$ = create_node($2, $1, $3, yylineno);}
            | NOT EXP     {return 0;}
            | VALUES      {$$=$1;}
            ;

VALUES      : NOT_ID_NUM { $$=$1; }
            | NOT_ID_STR { $$=$1; }
            ;   

TYPE        : INT_TYPE  {$$=$1;}
            | STR       {$$=$1;}
            ;

NOT_ID_NUM  : INT_LITERAL  {$$ = create_int_node($1, yylineno);}
            ; 

NOT_ID_STR  : STR_LITERAL  {$$ = create_str_node($1, yylineno);}
            ; 

OP          : '+' {$$=$1;}
            | '-' {$$=$1;}
            | '*' {$$=$1;}
            | '/' {$$=$1;}
            | '<' {$$=$1;}
            | '>' {$$=$1;}
            | LE  {$$=$1;}
            | GE  {$$=$1;}
            | EQ  {$$=$1;}
            | NE  {$$=$1;}
            | AND {$$=$1;}
            | OR  {$$=$1;}
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

    Node root;
    int ret = yyparse(&root);

    init();
    printf("Finished parsing \n");

    printf("Executing tree \n");
    execute_tree(&root);
    exit(0);
} 