#include <stdio.h>
#include <stdlib.h>
#include "../Test_MVP/y.tab.h"

#include "include/node.h"

Node* create_node(int node_type, Node* left, Node* right, int line_number){
    printf("DEBUG: HENLO GENERIC NODE ");
    Node* node = malloc(sizeof(*node));

    node->node_type   = node_type;
    node->line_number = line_number;

    GenericNode generic_node;

    generic_node.left        = left;
    generic_node.right       = right;

    node->node_kind.generic_node = generic_node;

    return node;
}

Node* create_if_node(Node* condition, Node* if_branch, Node* else_branch, int line_number){
    printf("DEBUG: HENLO IF NODE ");
    // IfNode * node = malloc(sizeof(*node));
    Node * node = malloc(sizeof(*node));
    
    node->node_type   = IF;
    node->line_number = line_number;

    // IfNode* if_node = malloc(sizeof(*if_node));
    IfNode if_node;

    if_node.condition = condition;
    if_node.if_branch = if_branch;
    if_node.else_branch = else_branch;

    node->node_kind.if_node = if_node;

    printf("Node type: %d \n", node->node_type);
    
    return node;
}

Node* create_while_node(Node* condition, Node* loop, int line_number){
    printf("DEBUG: HENLO WHILE NODE ");
    // WhileNode* node = malloc(sizeof(*node));
    Node* node = malloc(sizeof(*node));

    node->node_type   = WHILE;
    node->line_number = line_number;

    WhileNode while_node;

    
    while_node.condition   = condition;
    while_node.loop        = loop;


    printf("Node type: %d\n", node->node_type);

    node->node_kind.while_node = while_node;
    return node;
}

Node* create_assignment_node(int data_type, char* lvalue, Node* rvalue, int line_number){
    printf("DEBUG: HENLO ASSIGNMENT NODE\n");
    Node* node = malloc(sizeof(*node));

    node->node_type = 61;
    node->line_number = line_number;

    AssignmentNode a_node;

    a_node.value_type = data_type;
    a_node.symbol_lvalue = lvalue;
    a_node.symbol_rvalue = rvalue;
    
    node->node_kind.assignment_node = a_node;

    // return (Node *) node;
    return node;
}

Node* create_int_node(int value, int line_number){
    printf("DEBUG: HENLO INT NODE ");

    Node* node = malloc(sizeof(*node));
    node->node_type   = INT_LITERAL;
    node->line_number = line_number;


    node->node_kind.int_node = value;

    return node;

}
