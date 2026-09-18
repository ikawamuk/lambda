#include "../token_list/TokenList.h"
#include "../ast/AST.h"
#include "parse.h"

int	parse_abstraction(Abstruction *abstruction, ParseState *parse_state);
int	parse_application(AST *ast, ParseState *parse_state);

static int	case_abstraction(AST *ast, ParseState *parse_state);

int	parse_expr(AST *ast, ParseState *parse_state) {
	switch (peek_type(parse_state)) {
		case TK_LAMBDA: return (case_abstraction(ast, parse_state));
		default: return (parse_application(ast, parse_state));
	}
}

static int	case_abstraction(AST *ast, ParseState *parse_state) {
	Abstruction	abstruction = {0};
	if (parse_abstraction(&abstruction, parse_state) < 0)
		return (-1);
	if (ast_append_abstraction(ast, &abstruction) < 0)
		return (-1);
	return (0);
}
