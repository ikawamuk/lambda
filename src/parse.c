#define _GNU_SOURCE
#include <string.h>
#include "token_list/TokenList.h"
#include "ast/AST.h"

static int	parse_expr(AST *ast, TokenNode *cur);
static int	parse_abstraction(AST *ast, TokenNode *cur);
static int	parse_primary(AST *ast, TokenNode *cur);
static int	parse_application(AST *ast, TokenNode *cur);

int	parse(AST *ast_root, const TokenList *token_list) {
	TokenNode	*head = token_list->head;
	if (parse_expr(ast_root, head) < 0)
		return (0);
	return (0);
}

static int	parse_expr(AST *ast, TokenNode *cur) {

	return (0);
}

static int	parse_abstraction(AST *ast, TokenNode *cur) {

	return (0);
}

static int	parse_primary(AST *ast, TokenNode *cur) {
	return (0);
}

static int	parse_application(AST *ast, TokenNode *cur) {
	return (0);
}

static int	parse_parameter(AST *ast, TokenNode *cur) {
	return (0);
}
