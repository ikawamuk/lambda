#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include <stddef.h>
# include "String.h"

typedef struct TokenList	TokenList;
typedef struct TokenNode	TokenNode;
typedef struct Token		Token;
typedef enum TokenType		TokenType;

struct TokenList {
	TokenNode	*head;
	TokenNode	*tail;
	size_t		size;
};

void	token_list_construct(TokenList *this);
int		token_list_push_back(TokenList *this, const Token *new_token);
void	token_list_destruct(TokenList *this);

struct TokenNode {
	Token		data;
	TokenNode	*next;
	TokenNode	*prev;
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
	String		literal;
};

int		token_construct(Token *this, TokenType type, String literal);
int		token_construct_c_str(Token *this, TokenType type, char *c_str);
void	token_destruct(Token *this);

#endif
