#ifndef __node_h__
#define __node_h__

typedef union SymbolValue {
    int int_value;
    char* str_value;

} SymbolValue;

/* Generic Node */

typedef struct GenericNode {
    struct Node* left;
    struct Node* right;
} GenericNode;


/* Some nodes have a special format: */
typedef struct IfNode {

    struct Node* condition;

    struct Node* if_branch;
    struct Node* else_branch;
} IfNode;

typedef struct WhileNode {
    struct Node* condition;
    struct Node* loop;
} WhileNode;

typedef struct AssignmentNode {
    int value_type;
    char* symbol_lvalue;
    struct Node* symbol_rvalue;
} AssignmentNode;

typedef union NodeKind {
    IfNode if_node;
    WhileNode while_node;
    GenericNode generic_node;
    AssignmentNode assignment_node;
    int int_node;
    char * str_node;
} NodeKind;

typedef struct Node {
    int node_type;
    int line_number;

    NodeKind node_kind;
    
} Node;


Node* create_node(int node_type, Node* left, Node* right, int line_number);
Node* create_if_node(Node* condition, Node* if_branch, Node* else_branch, int line_number);
Node* create_while_node(Node* condition, Node* loop, int line_number);
Node* create_assignment_node(int data_type, char* lvalue, Node* rvalue, int line_number);
Node* create_int_node(int value, int line_number);
Node* create_str_node(char * value, int line_number);

#endif