#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "symbolTable.h"

#define CAPACITY 5000      // Capacity of the Hash Table

symbolTable * sTable;

void init(){
    sTable = calloc(1, sizeof(symbolTable));
    sTable->size = CAPACITY;
    sTable->count = 0;
    sTable->vars = calloc(CAPACITY, sizeof(var_t *));
    for(int i=0; i<CAPACITY; i++){
        sTable->vars[i] = NULL;
    }

    insertBasicFun();    // insert predefined functions
}

void createVar(char * name, v_type type, v_val value){ 
    var_t * var = calloc(1, sizeof(var_t));
    int len = strlen(name);
    var->name = calloc(1, sizeof(len) + 1);
    strncpy(var->name, name, len);
    var->type = type;
    var->value = value;
    
    insert(var);
}

void createFun(char * name, v_type retval, int argc, ...){
    fun_t * f = calloc(1, sizeof(fun_t));
    int len = strlen(name);
    f->name = calloc(1, sizeof(len) + 1);
    strncpy(f->name, name, len);
    f->retval = retval;
    f->argc = argc;
    if(argc > 0){
        va_list list;
        va_start(list, argc);
        args_t * arg = calloc(1, sizeof(args_t));
        arg->type = va_arg(list, v_type);
        args_t * aux = arg;
        int i=1;
        while(i < argc){
            aux->next = calloc(1, sizeof(args_t));
            aux->next->type = va_arg(list, v_type);
            aux = aux->next;
            i++;
        }
        f->first = arg;
        va_end(list);
    }

    insert((var_t *) f);
}

void freeSymbolTable(){
    for(int i=0; i<sTable->size; i++){
        var_t * var = sTable->vars[i];
        if(var != NULL){
            freeVar(var);
        }
    }
    free((void *) sTable->vars);
    free((void *) &sTable->count);
    free((void *) &sTable->size);
    free((void *) sTable);
}

void freeVar(var_t * var){
    free((void *) var->name);
    free((void *) var->type);
    v_val value = var->value;
    free((void *) &value.intval);
    free((void *) &value.doubleval);
    free((void *) &value.strval);
    free((void *) &value.classval);
    free((void *) &value.idval);
    free((void *) &var->value);
    free((void *) var);
}

void freeFun(fun_t * f){
    free((void *) f->name);
    free((void *) &f->argc);
    free((void *) f->retval);
    args_t * arg = f->first;
    args_t * aux;
    while(arg != NULL){
        aux = arg->next;
        free((void *) arg->type);
        free((void *) arg);
        arg = aux;
    }
    free((void *) f);
}

unsigned long hash(char * str){     // djb2
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; 

    return hash;
}

void insert(var_t * var) {
    int index = hash(var->name) % CAPACITY;
    var_t * current_var = sTable->vars[index];
    if(current_var == NULL){                    // insert
        if(sTable->count == sTable->size){
            // ERROR: Hash Table is full
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
            // ERROR: Collision (quite rare for djb2 algorithm)
            return;
        }
    }
}

void insertBasicFun(){
    createFun("newSelector", V_SELECTOR, 0);
    createFun("setColor", V_VOID, 5, V_SELECTOR, V_INT, V_INT, V_INT, V_INT);
    createFun("setFontSize", V_VOID, 2, V_SELECTOR, V_INT);
    createFun("setMargin", V_VOID, 2, V_SELECTOR, V_DOUBLE);
    createFun("setMarginTop", V_VOID, 2, V_SELECTOR, V_DOUBLE);
    createFun("setMarginBottom", V_VOID, 2, V_SELECTOR, V_DOUBLE);
    createFun("setMarginLeft", V_VOID, 2, V_SELECTOR, V_DOUBLE);
    createFun("setMarginRight", V_VOID, 2, V_SELECTOR, V_DOUBLE);
    createFun("setPadding", V_VOID, 2, V_SELECTOR, V_DOUBLE);
    createFun("setPaddingTop", V_VOID, 2, V_SELECTOR, V_DOUBLE);
    createFun("setPaddingBottom", V_VOID, 2, V_SELECTOR, V_DOUBLE);
    createFun("setPaddingLeft", V_VOID, 2, V_SELECTOR, V_DOUBLE);
    createFun("setPaddingRight", V_VOID, 2, V_SELECTOR, V_DOUBLE);
    createFun("setName", V_VOID, 2, V_SELECTOR, V_STR);
    // Other not implemented yet
    // newH1, newH2, newDiv, newP, newBody, newClass, newId
    // setBackgroundColor, setWidth, setHeight, textAlign
    /*
    createFun("newH1", V_H1, 0);
    createFun("newH2", V_H2, 0);
    createFun("newDiv", V_DIV, 0);
    createFun("newP", V_P, 0);
    createFun("newBody", V_BODY, 0);
    createFun("newClass", V_CLASS, 0);
    createFun("newId", V_ID, 0);
    createFun("setBackgroundColor", V_VOID, 5, V_SELECTOR, V_INT, V_INT, V_INT, V_INT);
    createFun("setWidth", V_VOID, 2, V_SELECTOR, V_DOUBLE);
    createFun("setHeight", V_VOID, 2, V_SELECTOR, V_DOUBLE);
    createFun("textAlign", V_VOID, 2, V_SELECTOR, V_STR);
    */
}

var_t * search(char * name){
    int index = hash(name) % CAPACITY;
    var_t * var = sTable->vars[index];
    if(var != NULL){
        if(strcmp(var->name, name) == 0){
            return var;
        }
    }
    // ERROR: Not found
    return NULL;
}

void delete(char * name){
    int index = hash(name) % CAPACITY;
    var_t * var = sTable->vars[index];
    if(var == NULL){
        // ERROR: Doesn't exists
        return;
    }
    free(var);
    sTable->vars[index] = NULL;
    sTable->count--;
    return;
}



// https://www.javatpoint.com/symbol-table
// https://www.journaldev.com/35238/hash-table-in-c-plus-plus
// http://www.cse.yorku.ca/~oz/hash.html
// https://stackoverflow.com/questions/7666509/hash-function-for-string
// https://www.tutorialspoint.com/cprogramming/c_variable_arguments.htm