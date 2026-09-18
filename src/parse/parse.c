#define _GNU_SOURCE
#include <string.h>
#include "../token_list/TokenList.h"
#include "../ast/AST.h"
#include "parse.h"

int	parse_expr(AST *ast, ParseState *parse_state);

static void	parse_state_construct(ParseState *this, const TokenList *token_list);

int	parse(AST *ast_root, const TokenList *token_list) {
	ParseState	state;
	parse_state_construct(&state, token_list);
	return (parse_expr(ast_root, &state));
}

static void	parse_state_construct(ParseState *this, const TokenList *token_list) {
	this->list_ptr = token_list;
	this->cur = token_list->head;
}

TokenType	peek_type(ParseState *this) {
	return (token_node_type(this->cur));
}

void	consume(ParseState *this) {
	this->cur = this->cur->next;
}

