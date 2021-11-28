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
%token<operation> NEW INT_TYPE DOUBLE STR COLOR SELECTOR DIV P BODY H1 H2 CLASS
%token<operation> IF WHILE
%token<int_value> INT_LITERAL

%right "="
%left AND OR 
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left NOT
%left '('
%right ')'

%type <node> STATMENTS STATMENT EXP LIST_ARG VALUES NOT_ID_NUM ARITH CND BLOCK LOOP ASSIGN
%type <operation> '<' '>' '(' ')' '+' '-' '/' '*' TYPE LE GE EQ NE AND OR
%token<string> ID

%parse-param {Node* root}

%start PROGRAM

%%

PROGRAM     : MAIN { printf("Finished Parsing =)\n"); }

MAIN        : STATMENTS {memcpy(root, $1, sizeof(*root));}

STATMENTS   : STATMENT STATMENTS {$$ = create_node(STATEMENT_LIST, $1, $2, yylineno); }
            |      { $$ = NULL; }
            ;

STATMENT    : CND  { $$ = $1; }
            | LOOP { $$ = $1;}
            | ASSIGN { $$=$1; }
            ;

ASSIGN      : INT_TYPE ID '=' VALUES ';' { $$ = create_assignment_node($1, $2, $4, yylineno); } 

BLOCK       : '{' STATMENTS '}'  { $$=$2; }
            |  { $$=NULL; }

CND         : IF '(' EXP ')' BLOCK {$$ = create_if_node($3, $5, NULL, yylineno);}
            ;

LOOP        : WHILE '(' EXP ')' BLOCK {$$ = create_while_node($3, $5, yylineno);}

EXP         : ARITH { $$ = $1;}
            | VALUES      {return 0;}
            ;

VALUES      : NOT_ID_NUM { $$=$1; }
            ;   

NOT_ID_NUM  : INT_LITERAL  {$$ = create_int_node($1, yylineno);}
            ;

ARITH       : NOT_ID_NUM '>' NOT_ID_NUM  { $$ = create_node($2, $1, $3, yylineno); }
            | NOT_ID_NUM '<' NOT_ID_NUM  { $$ = create_node($2, $1, $3, yylineno); }
            | NOT_ID_NUM '+' NOT_ID_NUM  { $$ = create_node($2, $1, $3, yylineno); }
            | NOT_ID_NUM '-' NOT_ID_NUM  { $$ = create_node($2, $1, $3, yylineno); }
            | NOT_ID_NUM '*' NOT_ID_NUM  { $$ = create_node($2, $1, $3, yylineno); }
            | NOT_ID_NUM '/' NOT_ID_NUM  { $$ = create_node($2, $1, $3, yylineno); }
            | NOT_ID_NUM LE NOT_ID_NUM  { $$ = create_node($2, $1, $3, yylineno);}
            | NOT_ID_NUM GE NOT_ID_NUM  { $$ = create_node($2, $1, $3, yylineno);}
            | NOT_ID_NUM EQ NOT_ID_NUM  { $$ = create_node($2, $1, $3, yylineno);}
            | NOT_ID_NUM NE NOT_ID_NUM  { $$ = create_node($2, $1, $3, yylineno);}
            ;

            
%%

void yyerror(Node* root, const char* msg) {
    fprintf(stderr, "%s\n", msg);
}

int main() {

    Node root;
    int ret = yyparse(&root);
    
    /* init_symbol_table(); */
    /* init(); */
    printf("Finished parsing \n");

    printf("Executing tree \n");
    execute_tree(&root);
    exit(0);
} 