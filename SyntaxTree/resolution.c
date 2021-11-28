#include "include/node.h"
#include "../Test_MVP/y.tab.h"
#include "include/resolution.h"
#include "../SymbolTable/symbolTable.h"

int execute_bool(Node* node, int op){
    IntNode* left = (IntNode*) node->left;
    IntNode* right = (IntNode*) node->right;

    switch(op){
        case GT:
            return left->value > right->value;
        case LT:
            return left->value < right->value;
        case LE:
            return left->value <= right->value;
        case GE:
            return left->value >= right->value;
        case EQ:
            return left->value == right->value;
        case NE:
            return left->value != right->value;
        
        default:
            printf("Error: Invalid operator %d", op);
    }
}

int execute_if_node(Node* node){

    int ret = execute_node(node->condition);

    if (ret){
        printf("DEBUG: ENTERED IF\n");
        // v_val v;
        // v.intval = 200;
        // var_t* my_var = createVar("hello", V_INT, v);
        // insert(my_var);

        // var_t* ret = search("hello");

        // printf("VALUE: %d\n", ret->value.intval);
        return execute_node(node->if_branch);
    }

    printf("DEBUG: NOT ENTERED IF");
    return execute_node(node->else_branch);
}

int execute_while_node(Node* node){
    int ret = execute_node(node->condition);

    printf("RET->%d ", ret);
    while(ret){
        printf("DEBUG: Entered while\n");
        execute_node(node->loop);
        ret = execute_node(node->condition);
    }

    printf("DEBUG: Exited while\n");
    return 1;
}

int execute_assignment_node(AssignmentNode* node){
    char* var_name = node->symbol_lvalue;
    printf("INSERTING %s", var_name);
}

int execute_node(Node* node){
    if ( node != NULL ){
        printf("Node type: %d\n", node->node_type);

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