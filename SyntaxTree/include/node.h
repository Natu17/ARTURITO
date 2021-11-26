#ifndef __node_h__
#define __node_h__

/* Generic Node */
typedef struct Node {
    int node_type;
    int line_number;

    struct Node* left;
    struct Node* right;
} Node;

/* Some nodes have a special format: */
typedef struct IfNode {
    int line_number;
    int node_type; // We need to include the node type because of the casting

    Node* condition;

    Node* if_branch;
    Node* else_branch;
} IfNode;

typedef struct WhileNode {
    int line_number;
    int node_type;

    Node* condition;
    Node* loop;
} WhileNode;

typedef struct AssignmentNode {
    int line_number;
    int node_type;

    char* symbol_lvalue;
    Node* symbol_rvalue;
} AssignmentNode;


typedef struct IntNode {
    int line_number;
    int node_type;

    int value;

} IntNode;


#endif