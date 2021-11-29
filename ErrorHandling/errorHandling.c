#include <stdio.h>
#include <stdlib.h>
#include "errorHandling.h"

void memoryAllocationErr(){
    fprintf(stderr, "ERROR: Memory not allocated.\n");
}

void fullHashTableErr(){
    fprintf(stderr, "ERROR: Hash Table is full.\n");
}

void collisionErr(){
    fprintf(stderr, "ERROR: Collision in Hash Table.\n");
}

void invalidOperatorErr(int oper){
    fprintf(stderr, "ERROR: Invalid Operator %d.\n", oper);
}

void reassignmentErr(){
    fprintf(stderr, "ERROR: Failure in reassignment.\n");
}

void variableExistsErr(){
    fprintf(stderr, "ERROR: Variable has already been asigned.\n");
}

void invalidNodeTypeErr(int type){
    fprintf(stderr, "ERROR: Invalid node type %d.\n", type);
}

void unknownTypeErr(int type){
    fprintf(stderr, "ERROR: Unknown type %d.\n", type);
}

void functionDoesNotExistErr(){
    fprintf(stderr, "ERROR: Function doesn't exist.\n");
}