#include <stdlib.h>
#include "../token_list/TokenList.h"
#include "../ast/AST.h"
#include "parse.h"

int	parse_primary(AST *ast, ParseState *parse_state);

int	parse_application(AST *ast, ParseState *parse_state) {
	AST	left = {0};
	AST	right = {0};
	if (parse_primary(&left, parse_state) < 0)
		return (-1);
	while (1) {
		if (parse_primary(&right, parse_state) < 0) {
			break ;
		}
		Application	app = {0};
		ast_move(&app.function, &left);
		ast_move(&app.argument, &right);
		AST tmp_ast = {0};
		if (ast_append_application(&tmp_ast, &app) < 0) {
			application_destruct(&app);
			ast_destruct(&left);
			return (-1);
		}
		ast_move(&left, &tmp_ast);
	}
	ast_move(ast, &left);
	return (0);
}
