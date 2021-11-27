#ifndef __resolution__h
#define __resolution__h

#define GT 62
#define LT 60

int execute_bool(Node* node, int op);
int execute_if_node(Node* node);
int execute_node(Node* node);
int execute_tree(Node* node);
#endif