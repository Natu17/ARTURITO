%code requires {
        #include <stdio.h>
        #include <stdlib.h>
        int yylex();
}

%union{
  char * string;
}

%token<string> NAME VALUE
%token INT DOUBLE STR COLOR SELECTOR DIV P BODY H1 H2 ID CLASS 
%token IF WHILE EXP START END SEMICOLON
%token LET LE GE EQ NE
%token AND OR NOT

%right "="
%left AND OR 
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left '!'
%start PROGRAM



%

PROGRAM 
            | MAIN {return 0;}

MAIN        : START STATMENTS END {return 0;}

STATMENTS   : STATMENT  {return 0;}
            | STATMENT SEMICOLON STATMENTS {return 0;}
            ;

STATMENT    : DECL {return 0;}
            | CALL {return 0;}
            | LOOP {return 0;}
            | CND  {return 0;}


DECL        : TYPE NAME '=' NEW TYPE '(' LIST_ARG ')' ';' {return 0;}
            ;

ASSIGN      : VALUE '=' VALUES {return 0;}

CALL        : NAME '(' LIST_ARG ')' {return 0;}
            ;


LIST_ARG    : ARG {$$ = $1;}
            | {$$ = 0;}
            ; 

ARG         : EXP {return 0;}
            | EXP ',' PARAM  {return 0;}
            ;

LOOP        : WHILE '(' EXP ')' {return 0;} '{' STATMENTS'}' {return 0;} {return 0;}
            ;

CND         : IF '(' EXP ')' {return 0;} '{' STATMENTS '}' {return 0;} {return 0;}
            ;

EXP         : EXP OP EXP  {return 0;}
            | NOT EXP     {return 0;}
            | VALUES      {return 0;}

VALUES      :NAME  {return 0;}
            |CALL {return 0;}
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
            | SELECTOR
            | H1
            | H2
            | COLOR
            | DIV
            | P
            | BODY
            | STR
            | CLASS
            | ID
            
            ;
%%

int yywrap(){
        return 1;
} 


int main() {

    exit(0);
} 