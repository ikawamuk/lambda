#include "token_list/TokenList.h"
#include "ast/AST.h"
#include "parse.h"

int	parse_expr(AST *ast, ParseState *parse_state);

static int	case_identifier(AST *ast, ParseState *parse_state);
static int	case_paren(AST *ast, ParseState *parse_state);

int	parse_primary(AST *ast, ParseState *parse_state) {
	switch (peek_type(parse_state)) {
		case TK_IDENTIFIER: return (case_identifier(ast, parse_state));
		case TK_LPAREN: return (case_paren(ast, parse_state));
		default: return (-1);
	}
}

static int	case_identifier(AST *ast, ParseState *parse_state) {
	String	variable = {0};
	if (token_node_move_literal(parse_state->cur, &variable) < 0)
		return (-1);
	consume(parse_state);
	if (ast_append_variable(ast, &variable) < 0) {
		string_destruct(&variable);
		return (-1);
	}
	return (0);
}

static int	case_paren(AST *ast, ParseState *parse_state) {
	AST	tmp_ast = {0};
	consume(parse_state);
	if (parse_expr(&tmp_ast, parse_state) < 0)
		return (-1);
	if (peek_type(parse_state) != TK_RPAREN) {
		ast_destruct(&tmp_ast);
		return (-1);
	}
	consume(parse_state);
	ast_move(ast, &tmp_ast);
	return (0);
}
