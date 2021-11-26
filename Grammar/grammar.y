%code requires {
        #include <stdio.h>
        #include <stdlib.h>
        int yylex();
}

%union{
  char * string;
}

%token<string> VALUE
%token INT DOUBLE STR COLOR SELECTOR DIV P BODY H1 H2 ID CLASS 
%token IF WHILE RETURN NEW FUNCTION LEFT RIGHT EXP
%token LET LE GE EQ NE
%token AND OR NOT

%right "="
%left AND OR 
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left '!'
%start START



%

START 
      : LEFT EXP RIGHT {return 0}
      | EXP {return 0;}

EXP       : DECL EXP {return 0}
          | FUNC EXP {return 0}
          | CODE S {return 0}
          | {$$ = 0;}
          ;


OPERATOR  : '+' {$$ = ADD;}
          | '-' {$$ = SUB;}
          | '*' {$$ = MUL;}
          | '/' {$$ = DIV;}
          | '<' {$$ = LESS;}
          | '>' {$$ = GREATER;}
          | LE  {$$ = LESSEQ;}
          | GE  {$$ = GREATEQ;}
          | EQ  {$$ = EQUALS;}
          | NE  {$$ = NEQ;}
          | AND {$$ = ANDOP;}
          | OR {$$ = OROP;}
          ;
        
TYPE      : 
            INT 
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