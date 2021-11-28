%code requires {
        #include <stdio.h>
        #include <stdlib.h>
        
        #include "SyntaxTree/include/node.h"
        int yylex();
}

%union{
  char * string;
  int operation;
  int int_value;
  Node* node;
}

%nonassoc STATEMENT_LIST

%token<string> NAME VALUE
%token<operation> NEW INT DOUBLE STR COLOR SELECTOR DIV P BODY H1 H2 ID CLASS 
%token<operation> IF WHILE START END
%token<int_value> INT_LITERAL

%token LET LE GE EQ NE
%token AND OR NOT

%token<node> PARAM

%right "="
%left AND OR 
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left '!'
%start PROGRAM

%type <node> STATMENTS STATMENT EXP LIST_ARG ASSIGN VALUES NOT_ID_NUM


%%

PROGRAM     : MAIN { printf("Finished Parsing =)"); }

MAIN        : START STATMENTS END {return 0;}

STATMENTS   : STATMENT  {$$ = $1}
            | STATMENT STATMENTS {$$ = create_node(STATEMENT_LIST, $1, $2, yylineno); }
            ;

STATMENT    : DECL { $$ = $1; }
            | CALL { $$ = $1; }
            | LOOP { $$ = $1; }
            | CND  { $$ = $1; }

DECL        : TYPE NAME '=' NEW TYPE '(' LIST_ARG ')' ';' {return 0;}
            | TYPE TYPE_MASTER '=' NEW TYPE_SON '(' LIST_ARG ')' ';' {return 0;}
            ;

ASSIGN      : VALUE '=' VALUES { $$ = create_assignment_node($1, $3, yylineno);}

CALL        : NAME '(' LIST_ARG ')' {return 0;}
            ;


LIST_ARG    : ARG {$$ = $1;}
            | {$$ = 0;}
            ; 

ARG         : EXP {return 0;}
            | EXP ',' PARAM  {return 0;}
            ;

LOOP        : WHILE '(' EXP ')' {return 0;} '{' STATMENTS '}' {return 0;} {create_while_node($3, $6, yylineno);}
            ;

CND         : IF '(' EXP {return 0;} '{' STATMENTS '}' {return 0;} {create_if_node($3, $6, NULL, yylineno);}
            ;

EXP         : EXP OP EXP  {return 0;}
            | NOT EXP     {return 0;}
            | VALUES      {return 0;}
            ;
VALUES      :NAME  {return 0;}
            |ID    {return 0;}
            |NOT_ID_NUM {$$=$1}
            |CALL {return 0;}
            ;   

NOT_ID_NUM  : INT_LITERAL  {$$ = create_int_node($1, yylineno);}
            ;

OP          : '+' {$$ = ADD;}
            | '-' {$$ = SUB;}
            | '*' {$$ = MUL;}
            | '/' {$$ = DIV;}
            | '<' {$$ = LESS;}
            | '>' {$$ = GREATER;}
            | LE  {$$ = LESS_EQ;}
            | GE  {$$ = GREATER_EQ;}
            | EQ  {$$ = EQUALS;}
            | NE  {$$ = NEQ;}
            | AND {$$ = AND_OP;}
            | OR {$$ = OR_OP;}
            ;
            
TYPE        : INT 
            | DOUBLE
            | STR
            ;

TYPE_MASTER : SELECTOR 
            ;

TYPE_SON    : H1
            | H2
            | DIV
            | P
            | BODY
            | CLASS
            | ID 
%%

int yywrap(){
        return 1;
} 


int main() {

    exit(0);
} 