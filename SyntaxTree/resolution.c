#include "include/node.h"
#include "../Test_MVP/y.tab.h"
#include "include/resolution.h"
#include "../SymbolTable/symbolTable.h"

int execute_bool(Node* node, int op){
    GenericNode gen = node->node_kind.generic_node;

    int left =  gen.left->node_kind.int_node;
    int right = gen.right->node_kind.int_node;

    switch(op){
        case GT:
            printf("%d > %d", left, right);
            return left > right;
        case LT:
            printf("%d < %d", left, right);
            return left < right;
        case LE:
            printf("%d <= %d", left, right);
            return left <= right;
        case GE:
            printf("%d >= %d", left, right);
            return left >= right;
        case EQ:
            printf("%d == %d", left, right);
            return left == right;
        case NE:
            printf("%d != %d", left, right);
            return left != right;
        case AND:
            printf("%d && %d", left, right);
            return left && right;
        
        default:
            printf("Error: Invalid operator %d", op);
    }
}

int execute_if_node(Node* node){

    IfNode if_node = node->node_kind.if_node;
    printf("if (");
    execute_node(if_node.condition);
    printf(" ){\n\t");
    execute_node(if_node.if_branch);
    printf("}\n");
    if(if_node.else_branch != NULL){
        printf("else{\n");
        execute_node(if_node.else_branch);
        printf("}\n");
    }
}

int execute_while_node(Node* node){
    printf("while (");
    WhileNode while_node = node->node_kind.while_node;
    execute_node(while_node.condition);
    printf("){\n\t");
    execute_node(while_node.loop);
    printf("}\n");

    // printf("DEBUG: Exited while\n");
    return 1;
}

int execute_assignment_node(Node* node){
    AssignmentNode a_node = node->node_kind.assignment_node;
    char* var_name = a_node.symbol_lvalue;
    
    if (a_node.value_type == INT_TYPE){
        printf("int %s = ", a_node.symbol_lvalue);
    }else{
        printf("Unknown type %d", a_node.value_type);
    }

    execute_node(a_node.symbol_rvalue);
    printf(";\n");

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
            case AND:
                return execute_bool(node, AND);
            case OR:
                return execute_bool(node, OR);
            case STATEMENT_LIST:;
                GenericNode gen = node->node_kind.generic_node;
                execute_node(gen.left);
                execute_node(gen.right);
                break;
            case WHILE:
                return execute_while_node(node);
            case AS_EQ:
                return execute_assignment_node(node);
            case INT_LITERAL:
                printf("%d", node->node_kind.int_node);
                break;
            default:
                printf("ERROR: %d", node->node_type);
        }
    }
}

int execute_tree(Node* node) {
    execute_node(node);
}