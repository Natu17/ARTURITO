#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

// Enums

typedef enum v_type {INT=0, DOUBLE, STR, SELECTOR, H1, H2, DIV, P, BODY, CLASS, ID} v_type;
typedef enum op {ADD=0, SUB, MUL, DIV, LESS, GREATER, LESS_EQ, GREATER_EQ, EQUALS, NEQ, AND_OP, OR_OP} op;

// Structures

typedef union v_value { // possible values: int, double, str, class, id
    int intval;
    double doubleval;
    char * strval;
    char * classval;
    int idval;
} v_val;

typedef struct var { 
    char * name;    // variable name
    v_type type;    // type
    v_val value;    // value
} var_t;

typedef struct symbolTable {
    var_t ** vars;
    int size;
    int count;
} symbolTable;

typedef struct args {
    args_t * next;
    v_type type;
} args_t;

typedef struct function { 
    char * name;        // function name
    int argc;           // amount of arguments
    args_t * first;     // first argument of a list of arguments
    v_type retval;      // return value
} fun_t;


// Functions

unsigned long hash(char * str);


#endif