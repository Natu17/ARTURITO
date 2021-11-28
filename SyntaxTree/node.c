#include <stdio.h>
#include <stdlib.h>
#include "../Test_MVP/y.tab.h"

#include "include/node.h"

Node* create_node(int node_type, Node* left, Node* right, int line_number){
    printf("DEBUG: HENLO GENERIC NODE ");
    Node* node = malloc(sizeof(*node));

    node->node_type   = node_type;
    node->line_number = line_number;

    node->left        = left;
    node->right       = right;

    printf("Node type: %d \n", node->node_type);

    return node;
}

Node* create_if_node(Node* condition, Node* if_branch, Node* else_branch, int line_number){
    printf("DEBUG: HENLO IF NODE ");
    // IfNode * node = malloc(sizeof(*node));
    Node * node = malloc(sizeof(*node));
    
    node->node_type   = IF;
    node->line_number = line_number;

    node->condition   = condition;
    node->if_branch   = if_branch;
    node->else_branch = else_branch;

    printf("Node type: %d \n", node->node_type);
    
    return node;
}

Node* create_while_node(Node* condition, Node* loop, int line_number){
    printf("DEBUG: HENLO WHILE NODE ");
    // WhileNode* node = malloc(sizeof(*node));
    Node* node = malloc(sizeof(*node));

    node->node_type   = WHILE;
    node->line_number = line_number;
    
    node->condition   = condition;
    node->loop        = loop;

    printf("Node type: %d\n", node->node_type);

    return (Node *) node;
}

Node* create_assignment_node(int data_type, char* lvalue, Node* rvalue, int line_number){
    printf("DEBUG: HENLO ASSIGNMENT NODE ");
    AssignmentNode* node = malloc(sizeof(*node));

    node->node_type      = 61;
    node->line_number    = line_number;
    node->symbol_lvalue  = lvalue;
    
    node->symbol_rvalue  = rvalue;

    printf("Node type: %d \n", node->node_type);

    return (Node *) node;
}

Node* create_int_node(int value, int line_number){
    printf("DEBUG: HENLO INT NODE ");
    IntNode* node = malloc(sizeof(*node));

    node->node_type   = INT_LITERAL;
    node->line_number = line_number;

    node->value       = value;

    printf("Node type: %d\n", node->node_type);

    return (Node *) node;

}
