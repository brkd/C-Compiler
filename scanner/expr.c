#include "defs.h"
#include "data.h"
#include "decl.h"


// Convert a token into an AST operation.
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

static struct ASTnode * primary(void) {
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

struct ASTnode *binexpr(void) {
  struct ASTnode *node, *left, *right;
  int nodetype;

  left = primary();

  if(Token.token == T_EOF) {
    return left;
  }

  nodetype = arithop(Token.token);

  scan(&Token);
  right = binexpr();
  node = makeastnode(nodetype, left, right, 0);

  return(node);
}