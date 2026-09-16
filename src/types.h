#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>

typedef struct TokenList	TokenList;
typedef struct Token		Token;
typedef enum TokenType		TokenType;

struct TokenList {
	Token		data;
	TokenList	*next;
};

enum TokenType {
	LAMBDA, // '\'
	DOT,    // '.'
	LPAREN, // '('
	RPAREN, // ')'
	IDENTIFIER
};

struct Token {
	TokenType	type;
	char		*literal;
};

typedef struct ASTNode	ASTNode;
typedef enum ASTType	ASTType;

enum ASTType {
	ABSTRUCTION,
	APPLICATION,
	IDENTIFIER
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
