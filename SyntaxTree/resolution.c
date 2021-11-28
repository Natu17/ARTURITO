#include "include/node.h"
#include "../Test_MVP/y.tab.h"
#include "include/resolution.h"
#include "../SymbolTable/symbolTable.h"

int execute_bool(Node* node, int op){
    IntNode* left = (IntNode*) node->left;
    IntNode* right = (IntNode*) node->right;

    switch(op){
        case GT:
            printf("%d > %d", left->value, right->value);
            return left->value > right->value;
        case LT:
            printf("%d < %d", left->value, right->value);
            return left->value < right->value;
        case LE:
            printf("%d <= %d", left->value, right->value);
            return left->value <= right->value;
        case GE:
            printf("%d >= %d", left->value, right->value);
            return left->value >= right->value;
        case EQ:
            printf("%d == %d", left->value, right->value);
            return left->value == right->value;
        case NE:
            printf("%d != %d", left->value, right->value);
            return left->value != right->value;
        
        default:
            printf("Error: Invalid operator %d", op);
    }
}

int execute_if_node(Node* node){

    printf("if (");
    execute_node(node->condition);
    printf(" ){\n");
    execute_node(node->if_branch);
    printf("}\n");
    if(node->else_branch != NULL){
        printf("else{\n");
        execute_node(node->else_branch);
        printf("}\n");
    }
}

int execute_while_node(Node* node){
    printf("while (");
    execute_node(node->condition);
    printf("){\n");
    execute_node(node->loop);
    printf("}\n");

    // printf("DEBUG: Exited while\n");
    return 1;
}

int execute_assignment_node(AssignmentNode* node){
    char* var_name = node->symbol_lvalue;
    // printf("INSERTING %s", var_name);
}

int execute_node(Node* node){
    if ( node != NULL ){
        // printf("Node type: %d\n", node->node_type);

        switch(node->node_type){
            case IF:
                return execute_if_node(node);
            case GT:
                return execute_bool(node, GT);
            case LT:
                return execute_bool(node, LT);
            case LE:
                return execute_bool(node, LE);
            case GE:
                return execute_bool(node, GE);
            case EQ:
                return execute_bool(node, EQ);
            case NE:
                return execute_bool(node, NE);
            case STATEMENT_LIST:
                execute_node(node->left);
                execute_node(node->right);
                break;
            case WHILE:
                return execute_while_node(node);
            case AS_EQ:
                return execute_assignment_node((AssignmentNode*) node);
            default:
                printf("ERROR: %d", node->node_type);
        }
    }
}

int execute_tree(Node* node) {
    execute_node(node);
}