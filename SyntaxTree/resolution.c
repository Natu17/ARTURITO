#include "include/node.h"
#include "../Test_MVP/y.tab.h"
#include "include/resolution.h"
#include "../SymbolTable/symbolTable.h"

v_val execute_node(Node* node);

void execute_bool(Node *node, int op)
{   
    GenericNode gen = node->node_kind.generic_node;

    Node * left = gen.left;
    Node * right = gen.right;
    execute_node(left);

    if(op == AND){

         printf(" && ");


    }else
    {
        printf(" || ");
    }

    execute_node(right);
    
}


void execute_exp(Node *node, int op){
    GenericNode gen = node->node_kind.generic_node;

    Node * left = gen.left;
    Node * right = gen.right;
    v_val l = execute_node(left);

    switch (op)
    {
    case GT:
        printf(">");
        break;
    case LT:
        printf("<");
        break;
    case LE:
        printf("<=");
        break;
    case GE:
        printf(">=");
        break;
    case EQ:
        printf("==");
        break;
    case NE:
        printf("!=");
        break;
    default:
        printf("Error: Invalid operator %d", op);
    }
    v_val r = execute_node(right);
}

void execute_if_node(Node *node)
{

    IfNode if_node = node->node_kind.if_node;
    printf("if (");
    execute_node(if_node.condition);
    printf(" ){\n\t");
    execute_node(if_node.if_branch);
    printf("}\n");
    if (if_node.else_branch != NULL)
    {
        printf("else{\n");
        execute_node(if_node.else_branch);
        printf("}\n");
    }
}

void execute_while_node(Node *node)
{
    printf("while (");
    WhileNode while_node = node->node_kind.while_node;
    execute_node(while_node.condition);
    printf("){\n\t");
    execute_node(while_node.loop);
    printf("}\n");

    // printf("DEBUG: Exited while\n");
}

void execute_assignment_node(Node* node){
    AssignmentNode a_node = node->node_kind.assignment_node;
    char* var_name = a_node.symbol_lvalue;

    if( search(var_name) != NULL) {
        //Error Handling
        printf("ERROR");
    }
    
    if (a_node.value_type == INT_TYPE){
        printf("int %s = ", a_node.symbol_lvalue);
    } 
    else if (a_node.value_type == STR)
    {
        printf("char * %s = ", a_node.symbol_lvalue);
    }
    else{
        printf("Unknown type %d", a_node.value_type);
    }

    v_val ret = execute_node(a_node.symbol_rvalue);
    createVar(var_name, a_node.value_type, ret); 
    
    printf(";\n");
}

v_val execute_node(Node *node)
{
    if (node != NULL)
    {
        // printf("Node type: %d\n", node->node_type);

        switch (node->node_type)
        {
        case IF:
             execute_if_node(node);
             break;
        case GT:
            execute_exp(node, GT);
            break;
        case LT:
            execute_exp(node, LT);
            break;
        case LE:
            execute_exp(node, LE);
            break;
        case GE:
            execute_exp(node, GE);
            break;
        case EQ:
            execute_exp(node, EQ);
            break;
        case NE:
            execute_exp(node, NE);
            break;
        case AND:
            execute_bool(node, AND);
            break;
         case OR:
            execute_bool(node, OR);
            break;
         case STATEMENT_LIST:;
            GenericNode gen = node->node_kind.generic_node;
            execute_node(gen.left);
            execute_node(gen.right);
            break;
        case WHILE:
            execute_while_node(node);
            break;
        case AS_EQ:
            execute_assignment_node(node);
            break;
        case INT_LITERAL:;
            printf("%d", node->node_kind.int_node);
            v_val ret;
            ret.intval = node->node_kind.int_node;
            return ret;
        case STR:;
            printf("%s", node->node_kind.str_node);
            break;
        default:
            printf("ERROR: %d", node->node_type);
        }
    }
    v_val ret_null;
    ret_null.nothing = NULL;
    return ret_null;
}

void execute_tree(Node *node)
{
    execute_node(node);
}