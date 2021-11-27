#ifndef __node_h__
#define __node_h__

typedef union SymbolValue {
    int int_value;
    char* str_value;

} SymbolValue;

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

Node* create_node(int node_type, Node* left, Node* right, int line_number);
Node* create_if_node(Node* condition, Node* if_branch, Node* else_branch, int line_number);
Node* create_while_node(Node* condition, Node* loop, int line_number);
Node* create_assignment_node(char* lvalue, Node* rvalue, int line_number);
Node* create_int_node(int value, int line_number);

#endif