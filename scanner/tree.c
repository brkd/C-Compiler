#include "defs.h"
#include "data.h"
#include "decl.h"

struct ASTnode *makeastnode(int op, struct ASTnode* left, struct ASTnode* right, int intvalue) {
    struct ASTnode *newNode = (struct ASTnode *) malloc(sizeof(struct ASTnode));

    if (newNode == NULL) {
        fprintf(stderr, "Unable to malloc in mkastnode()\n");
    }

    newNode->op = op;
    newNode->left = left;
    newNode->right = right;
    newNode->intvalue = intvalue;

    return (newNode);
}

struct ASTnode *makeastleaf(int op, int intvalue) {
    return (makeastnode(op, NULL, NULL, intvalue));
}

