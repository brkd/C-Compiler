#include "defs.h"
#include "data.h"
#include "decl.h"


int interpretAST(struct ASTnode *node) {
    int leftval, rightval;

    if(node->left)
        leftval = interpretAST(node->left);
    if(node->right)
        rightval = interpretAST(node->right);

    switch (node->op) {
        case A_ADD:
            printf("%d + %d\n", leftval, rightval);
            return (leftval + rightval);
        case A_SUBTRACT:
            printf("%d - %d\n", leftval, rightval);
            return (leftval - rightval);
        case A_MULTIPLY:
            printf("%d * %d\n", leftval, rightval);
            return (leftval * rightval);
        case A_DIVIDE:
            printf("%d / %d\n", leftval, rightval);
            return (leftval / rightval);
        case A_INTLIT:
            printf("int %d\n", node->intvalue);
            return (node->intvalue);
        default:
        fprintf(stderr, "Unknown AST operator %d\n", node->op);
        exit(1);
    }
}