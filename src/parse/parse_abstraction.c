#include "token_list/TokenList.h"
#include "ast/AST.h"
#include "parse.h"

int	parse_expr(ASTNode **ast, ParseState *parse_state);

static int	skip_lambda(ParseState *parse_state);
static int	parse_parmeter(String *parameter, ParseState *parse_state);
static int	skip_dot(ParseState *parse_state);

int	parse_abstraction(Abstruction *abstruction, ParseState *parse_state) {
	if (skip_lambda(parse_state) < 0)
		return (-1);
	String	parameter = {0};
	if (parse_parmeter(&parameter, parse_state) < 0)
		return (-1);
	if (skip_dot(parse_state) < 0) {
		string_destruct(&parameter);
		return (-1);
	}
	AST	body = {0};
	if (parse_expr(&body, parse_state) < 0) {
		string_destruct(&parameter);
		return (-1);
	}
	string_move(&abstruction->parameter, &parameter); // アドレス演算子付きで入れてるので非NULLが確実。エラーチェック不要。ast_moveも同じ
	ast_move(&abstruction->body, &body);
	return (0);
}

static int	skip_lambda(ParseState *parse_state) {
	if (peek_type(parse_state) != TK_LAMBDA)
		return (-1);
	consume(parse_state);
	return (0);
}

static int	parse_parmeter(String *parameter, ParseState *parse_state) {
	if (peek_type(parse_state) != TK_IDENTIFIER)
		return (-1);
	if (token_node_move_literal(parse_state->cur, parameter) < 0)
		return (-1);
	consume(parse_state);
	return (0);
}

static int	skip_dot(ParseState *parse_state) {
	if (peek_type(parse_state) != TK_DOT)
		return (-1);
	consume(parse_state);
	return (0);
}
