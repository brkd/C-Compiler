int scan(struct token *t);
struct ASTnode *makeastnode(int op, struct ASTnode *left,
			  struct ASTnode *right, int intvalue);
struct ASTnode *makeastleaf(int op, int intvalue);
struct ASTnode *binexpr(void);
struct ASTnode *additive_expr(void);
int interpretAST(struct ASTnode *node);