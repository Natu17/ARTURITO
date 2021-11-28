/*variable o contantes o nombfre de funciones que vamos definiendo en el programa de entrada
representa el compilador, archivo de salida (con el estado del compilador)*/
#include <string.h>
#include "symbolTable.h"

#define CAPACITY 50000      // Capacity of the Hash Table

symbolTable * sTable;

void init(){
    sTable = createSymbolTable(CAPACITY);
}

symbolTable * createSymbolTable(int size){
    symbolTable * table = calloc(1, sizeof(symbolTable));
    table->size = size;
    table->count = 0;
    table->vars = calloc(size, sizeof(var_t *));
    for(int i=0; i<size; i++){
        table->vars[i] = NULL;
    }

    return table;
}


var_t * createVar(char * name, v_type type, v_val value){ 
    var_t * var = calloc(1, sizeof(var_t));
    int len = strlen(name);
    var->name = calloc(1, sizeof(len) + 1);
    strncpy(var->name, name, len);
    var->type = type;
    var->value = value;
    
    return var;
}

fun_t * createFun(char * name, v_type retval, int argc, ...){
    fun_t * f = calloc(1, sizeof(fun_t));
    int len = strlen(name);
    f->name = calloc(1, sizeof(len) + 1);
    strncpy(f->name, name, len);
    f->retval = retval;
    f->argc = argc;
    if(argc > 0){
        // add args
    }

    return f;
}

void freeSymbolTable(symbolTable * table){
    for(int i=0; i<table->size; i++){
        var_t * var = table->vars[i];
        if(var != NULL){
            freeVar(var);
        }
    }
    free(table->vars);
    free(table->count);
    free(table->size);
    free(table);
}

void freeVar(var_t * var){
    free(var->name);
    free(var->type);
    free(var->value);
    free(var);
}

void freeFun(var_t * var){
    // free fun
}

unsigned long hash(char * str){ // strings with the same length will collide, change the hash
    unsigned long i = 0;
    for(int j=0; str[j]; j++){
        i += str[j];
    }
    return i % CAPACITY;
}


void insert(var_t * var) {
    int index = hash(var->name);
    var_t * current_var = sTable->vars[index];
    if(current_var == NULL){                    // insert
        if(sTable->count == sTable->size){
            // Error: Hash Table is full
            free(var);
            return;
        }
        sTable->vars[index] = var;
        sTable->count++;
    }
    else {
        if(strcmp(current_var->name, var->name) == 0){  // update
            sTable->vars[index]->value = var->value;
            sTable->vars[index]->type = var->type;
            return;
        }
        else {
            handleCollision(sTable, var);           // collision
            return;
        }
    }
}

void handleCollision(symbolTable * table, var_t * var){
    // handle collision
}

var_t * search(char * name){
    int index = hash(name);
    var_t * var = sTable->vars[index];
    if(var != NULL){
        if(strcmp(var->name, name) == 0){
            return var;
        }
    }

    return NULL;
}

// https://www.javatpoint.com/symbol-table
// https://www.journaldev.com/35238/hash-table-in-c-plus-plus