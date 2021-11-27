#include "include/node.h"
#include "../Test_MVP/y.tab.h"
#include "include/resolution.h"

int execute_bool(Node* node, int op){
    IntNode* left = (IntNode*) node->left;
    IntNode* right = (IntNode*) node->right;

    switch(op){
        case GT:
            return left->value > right->value;
        case LT:
            return left->value < right->value;
    }
}

int execute_if_node(Node* node){

    int ret = execute_node(node->condition);

    if (ret){
        printf("ENTERED IF");
        return execute_node(node->if_branch);
    }

    printf("NOT ENTERED IF");
    return execute_node(node->else_branch);
}

int execute_node(Node* node){
    if ( node != NULL ){
        switch(node->node_type){
            case IF:
                execute_if_node(node);
                break;
            case GT:
                execute_bool(node, GT);
                break;
            case LT:
                execute_bool(node, LT);
                break;
            case STATEMENT_LIST:
                execute_node(node->left);
                execute_node(node->right);
        }
    }
}

int execute_tree(Node* node) {
    execute_node(node);
}