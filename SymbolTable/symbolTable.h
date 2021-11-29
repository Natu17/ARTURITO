#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

// Enums
#include "../y.tab.h"

typedef enum op {ADD_OP=0, SUB_OP, MUL_OP, DIV_OP, LESS_OP, GREATER_OP, LESS_EQ_OP, GREATER_EQ_OP, EQUALS_OP, NEQ_OP, AND_OP, OR_OP} op;

// Structures

typedef union v_value {
    int intval;
    double doubleval;
    char * strval;
    char * classval;
    int idval;
    void* nothing;
} v_val;

typedef struct var { 
    char * name;    // variable name
    int type;    // type
    v_val value;    // value
} var_t;

typedef struct symbolTable {
    var_t ** vars;
    int size;
    int count;
} symbolTable;

typedef struct args {
    struct args * next;
    int type;
} args_t;

typedef struct function { 
    char * name;        // function name
    int argc;           // amount of arguments
    args_t * first;     // first argument of a list of arguments
    int retval;      // return value
} fun_t;


// Functions
void init();
void createVar(char * name, int type, v_val value);
void createFun(char * name, int retval, int argc, ...);
void freeSymbolTable();
void freeVar(var_t * var);
void freeFun(fun_t * f);
unsigned long hash(char * str);
void insert(var_t * var);
void insertBasicFun();
var_t * search(char * name);
void delete(char * name);

#endif