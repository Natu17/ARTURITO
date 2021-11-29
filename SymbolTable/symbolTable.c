#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "symbolTable.h"
#include "../ErrorHandling/errorHandling.h"

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

void createVar(char * name, int type, v_val value){ 
    var_t * var = calloc(1, sizeof(var_t));
    int len = strlen(name);
    var->name = calloc(1, sizeof(len) + 1);
    strncpy(var->name, name, len);
    var->type = type;
    var->value = value;
    
    insert(var);
}

void createFun(char * name, int retval, int argc, ...){
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
        arg->type = va_arg(list, int);
        args_t * aux = arg;
        int i=1;
        while(i < argc){
            aux->next = calloc(1, sizeof(args_t));
            aux->next->type = va_arg(list, int);
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
    free((void *) &var->type);
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
    free((void *) &f->retval);
    args_t * arg = f->first;
    args_t * aux;
    while(arg != NULL){
        aux = arg->next;
        free((void *) &arg->type);
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
            fullHashTableErr();
            free(var);
            return;
        }
        sTable->vars[index] = var;
        sTable->count++;
    }
    else {
        if(strcmp(current_var->name, var->name) == 0 && current_var->type == var->type){  // update
            sTable->vars[index]->value = var->value;
            return;
        }
        else {
            collisionErr();     // Collisions are quite rare for djb2 algorithm
            return;
        }
    }
}

void insertBasicFun(){
    createFun("newSelector", SELECTOR, 0);
    createFun("setColor", VOID, 5, SELECTOR, INT_TYPE, INT_TYPE, INT_TYPE, INT_TYPE);
    createFun("addSelectors", VOID, 1, SELECTOR);
    createFun("setFontSize", VOID, 2, SELECTOR, INT_TYPE);
    createFun("setMargin", VOID, 2, SELECTOR, DOUBLE);
    createFun("setMarginTop", VOID, 2, SELECTOR, DOUBLE);
    createFun("setMarginBottom", VOID, 2, SELECTOR, DOUBLE);
    createFun("setMarginLeft", VOID, 2, SELECTOR, DOUBLE);
    createFun("setMarginRight", VOID, 2, SELECTOR, DOUBLE);
    createFun("setPadding", VOID, 2, SELECTOR, DOUBLE);
    createFun("setPaddingTop", VOID, 2, SELECTOR, DOUBLE);
    createFun("setPaddingBottom", VOID, 2, SELECTOR, DOUBLE);
    createFun("setPaddingLeft", VOID, 2, SELECTOR, DOUBLE);
    createFun("setPaddingRight", VOID, 2, SELECTOR, DOUBLE);
    createFun("setName", VOID, 2, SELECTOR, STR);
    // Other not implemented yet
    // newH1, newH2, newDiv, newP, newBody, newClass, newId
    // setBackgroundColor, setWidth, setHeight, textAlign
    /*
    createFun("newH1", H1, 0);
    createFun("newH2", H2, 0);
    createFun("newDiv", DIV, 0);
    createFun("newP", P, 0);
    createFun("newBody", BODY, 0);
    createFun("newClass", CLASS, 0);
    createFun("newId", ID, 0);
    createFun("setBackgroundColor", VOID, 5, SELECTOR, INT_TYPE, INT_TYPE, INT_TYPE, INT_TYPE);
    createFun("setWidth", VOID, 2, SELECTOR, DOUBLE);
    createFun("setHeight", VOID, 2, SELECTOR, DOUBLE);
    createFun("textAlign", VOID, 2, SELECTOR, STR);
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
    return NULL;
}

void delete(char * name){
    int index = hash(name) % CAPACITY;
    var_t * var = sTable->vars[index];
    if(var == NULL){
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