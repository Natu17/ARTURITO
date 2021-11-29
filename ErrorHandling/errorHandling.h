#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

void memoryAllocationErr();
void fullHashTableErr();
void collisionErr();
void invalidOperatorErr(int oper);
void reassignmentErr();
void variableExistsErr();
void invalidNodeTypeErr(int type);

#endif