#ifndef __resolution__h
#define __resolution__h



#define GT 62
#define AS_EQ 61 // Assign Equal
#define LT 60

void execute_bool(Node* node, int op);
void execute_exp(Node* node, int op);
void execute_if_node(Node* node);
void execute_while_node(Node *node);
void execute_tree(Node* node);
#endif