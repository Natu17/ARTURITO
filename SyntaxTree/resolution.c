#include "../ErrorHandling/errorHandling.h"
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
        invalidOperatorErr(op);
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


int execute_assignment_node(Node* node){
    AssignmentNode a_node = node->node_kind.assignment_node;
    char* var_name = a_node.symbol_lvalue;

    if(a_node.value_type == REASSIGNMENT){
        if(search(var_name) == NULL){
            reassignmentErr();
        }
        printf("%s = ", a_node.symbol_lvalue);
        v_val ret = execute_node(a_node.symbol_rvalue);
        createVar(var_name, a_node.value_type, ret); 
        
        printf(";\n");
        return -1;
    }


    if( search(var_name) != NULL) {
        variableExistsErr();
    }
    
     switch (a_node.value_type)
        {
        case INT_TYPE:
            printf("int %s = ", a_node.symbol_lvalue);
            break;
        case SELECTOR:
            printf("struct selector *%s = ", a_node.symbol_lvalue);
            fflush(stdout);
            break;
        case  STR:
            printf("char * %s = ", a_node.symbol_lvalue);
            break;
        case  DOUBLE:
            printf("double %s = ", a_node.symbol_lvalue);
            break;
        default: printf("Unknown type %d", a_node.value_type);
        }
         
    v_val ret = execute_node(a_node.symbol_rvalue);
    createVar(var_name, a_node.value_type, ret); 
    
    printf(";\n");
    return 0;
}

void execute_function_node(Node* node){
    FunctionNode f = node->node_kind.function_node;
    if(f.params == NULL){
        if(search(f.name) == NULL){
            //TODO ERRORS
            printf("ERROR");
            return;
        }

        printf("%s();\n", f.name);
        return;
    }

    printf("%s(", f.name);
    execute_node(f.params);
    printf(");\n");

}

void execute_param_node(Node* node){
    ParamsNode p = node->node_kind.param_node;
    execute_node(p.param);
    printf(", ");
    execute_node(p.rest);
}

int is_letter(int val){
    return (val >= 65 && val <=90) || (val>=97 && val<= 122);
}

v_val execute_node(Node *node)
{
    if (node != NULL)
    {

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
        case H1:
            printf("selectorInit(H1)");
            break;
        case H2:
            printf("selectorInit(H2)");
            fflush(stdout);
            break;
        case BODY:
            printf("selectorInit(body)");
            fflush(stdout);
            break;
        case P:
            printf("selectorInit(p)");
            fflush(stdout);
            break;
        case DIV:
            printf("selectorInit(div)");
            fflush(stdout);
            break;
        case CLASS:
            printf("selectorInit(class)");
            fflush(stdout);
            break;
        case ID_TYPE:
            printf("selectorInit(id)");
            fflush(stdout);
            break;
        case STR:
            printf("%s", node->node_kind.str_node);
            break;
        case INT_LITERAL:;
            printf("%d", node->node_kind.int_node);
            v_val ret;
            ret.intval = node->node_kind.int_node;
            return ret;
        case DOUBLE:;
            printf("%.2f", node->node_kind.double_node);
            v_val reti;
            reti.intval = node->node_kind.double_node;
            return reti;
        case FUN_CALL:
            execute_function_node(node);
            break;
        case PARAM:
            execute_param_node(node);
            break;
        default:
            if(is_letter(node->node_type)){
                printf("%c ", node->node_type);
            }else{
                invalidNodeTypeErr(node->node_type);
            }
            
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


