#include "defs.h"
#include "data.h"
#include "decl.h"

int arithop(int tok) {
  switch (tok) {
    case T_PLUS:
      return (A_ADD);
    case T_MINUS:
      return (A_SUBTRACT);
    case T_STAR:
      return (A_MULTIPLY);
    case T_SLASH:
      return (A_DIVIDE);
    default:
      fprintf(stderr, "unknown token in arithop() on line %d\n", Line);
      exit(1);
  }
}

static struct ASTnode *primary(void) {
  struct ASTnode *node;

  switch (Token.token) {
    case T_INTLIT:
      node = makeastleaf(A_INTLIT, Token.intvalue);
      scan(&Token);
      return (node);
    default:
      fprintf(stderr, "syntax error on line %d\n", Line);
      exit(1);
  }
}

static struct ASTnode *multiplicative_expr(void) {
    struct ASTnode *left, *right;

    left = primary();

    if(Token.token == T_EOF) {
        return left;
    }

    int nodetype = arithop(Token.token);

    while((Token.token == T_STAR) || (Token.token == T_SLASH)) {
        scan(&Token);
        right = primary();

        left = makeastnode(nodetype, left, right, 0);
        
        if (Token.token == T_EOF) break;

    }

    return (left);
}

struct ASTnode *additive_expr(void) {
    struct ASTnode *left, *right;

    left = multiplicative_expr();

    if(Token.token == T_EOF) {
        return left;
    }

    int nodetype = arithop(Token.token);

    while(1) {
        scan(&Token);
        right = multiplicative_expr();

        left = makeastnode(nodetype, left, right, 0);

        if (Token.token == T_EOF) break;
    }

    return (left);
}
