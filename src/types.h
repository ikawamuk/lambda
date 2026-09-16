#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>

# include "token_list/TokenList.h"

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
			size_t	idex;
			char	*name;
		};
	};
};

#endif
