#include "include/node.h"
#include "../Test_MVP/y.tab.h"
#include "include/resolution.h"
#include "../SymbolTable/symbolTable.h"
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
    execute_node(left);

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
      execute_node(right);
}

int execute_if_node(Node *node)
{

    IfNode if_node = node->node_kind.if_node;
    printf("if (");
    execute_node(if_node.condition);
    printf(" ){\n");
    execute_node(if_node.if_branch);
    printf("}\n");
    if (if_node.else_branch != NULL)
    {
        printf("else{\n");
        execute_node(if_node.else_branch);
        printf("}\n");
    }
}

int execute_while_node(Node *node)
{
    printf("while (");
    // execute_node(node->condition);
    // printf("){\n");
    // execute_node(node->loop);
    printf("}\n");

    // printf("DEBUG: Exited while\n");
    return 1;
}

int execute_assignment_node(AssignmentNode *node)
{
    char *var_name = node->symbol_lvalue;
    // printf("INSERTING %s", var_name);
}

int execute_node(Node *node)
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
            return execute_while_node(node);
        case AS_EQ:
            return execute_assignment_node((AssignmentNode *)node);
        case INT_LITERAL:
                printf("%d", node->node_kind.int_node);
                break;
        default:
            printf("ERROR: %d", node->node_type);
        }
    }
}

int execute_tree(Node *node)
{
    execute_node(node);
}