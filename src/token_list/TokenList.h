#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include <stddef.h>
# include "../string/String.h"

typedef struct TokenList	TokenList;
typedef struct TokenNode	TokenNode;
typedef struct Token		Token;
typedef enum TokenType		TokenType;

enum TokenType {
	TK_LAMBDA, // '\'
	TK_DOT,    // '.'
	TK_LPAREN, // '('
	TK_RPAREN, // ')'
	TK_IDENTIFIER,
	TK_EOF
};

struct Token {
	TokenType	type;
	String		literal;
};

int			token_construct(Token *this, TokenType type, String literal);
int			token_construct_c_str(Token *this, TokenType type, char *c_str);
void		token_destruct(Token *this);
Token		*token_assign(Token *this, const Token *rhs);
TokenType	token_type(const Token *this);
int			token_move_literal(Token *this, String *dest);
void		token_print(const Token *this);


struct TokenNode {
	Token		data;
	TokenNode	*next;
	TokenNode	*prev;
};

TokenType	token_node_type(const TokenNode *this);
int			token_node_move_literal(TokenNode *this, String *dest);

struct TokenList {
	TokenNode	*head;
	TokenNode	*tail;
	size_t		size;
};

void	token_list_construct(TokenList *this);
int		token_list_push_back(TokenList *this, const Token *new_token);
void	token_list_destruct(TokenList *this);
void	token_list_print(const TokenList *this);

#endif
