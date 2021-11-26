#include <stdio.h>
#include <stdlib.h>
#include "Grammar/y.tab.h"

#include "include/node.h"

Node* create_node(int node_type, Node* left, Node* right, int line_number){
    Node* node = malloc(sizeof(*node));

    node->node_type   = node_type;
    node->line_number = line_number;

    node->left        = left;
    node->right       = right;

    return node;
}

Node* create_if_node(Node* condition, Node* if_branch, Node* else_branch, int line_number){
    IfNode * node = malloc(sizeof(*node));

    node->node_type   = IF;
    node->line_number = line_number;

    node->condition   = condition;
    node->if_branch   = if_branch;
    node->else_branch = else_branch;  
    
    return (Node*) node;
}

Node* create_while_node(Node* condition, Node* loop, int line_number){
    WhileNode* node = malloc(sizeof(*node));

    node->node_type   = WHILE;
    node->line_number = line_number;
    
    node->condition   = condition;
    node->loop        = loop;

    return (Node *) node;
}

Node* create_assignment_node(char* lvalue, Node* rvalue, int line_number){
    AssignmentNode* node = malloc(sizeof(*node));

    node->node_type      = ASSIGN;
    node->line_number    = line_number;
    node->symbol_lvalue  = lvalue;
    node->symbol_rvalue  = rvalue;

    return (Node *) node;
}

Node* create_int_node(int value, int line_number){
    IntNode* node = malloc(sizeof(*node));

    node->node_type   = INT;
    node->line_number = line_number;

    node->value       = value;

    return (Node *) node;

}
