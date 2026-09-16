#ifndef AST_H
# define AST_H

# include <stddef.h>

typedef struct AST		AST;
typedef struct ASTNode	ASTNode;
typedef enum ASTType	ASTType;

enum ASTType {
	AST_ABSTRUCTION,
	AST_APPLICATION,
	AST_IDENTIFIER
};

struct ASTNode {
	ASTType	type;
	union {
		struct {
			char	*parameter;
			ASTNode	*body;
		};
		struct {
			ASTNode	*function;
			ASTNode	*argument;
		};
		struct {
			size_t	index;
			char	*name;
		};
	};
};

struct AST {
	ASTNode	*root;
};

void	ast_construct(AST *this);

#endif
