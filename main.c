#include <stdio.h>
#include "src/types.h"

int	lex(TokenList* token_list, const char *source_code);
int	parse(ASTNode* ast_root, const TokenList *token_list);
int	evaluate(ASTNode *value, const ASTNode *ast_root);
int	encode(int *status, const ASTNode *value);

int	main(int argc, char *argv[]) {
	if (argc < 2)
		return (1);
	int	status = run_interpreter(argv[1]);
	if (status < 0)
		return (1);
	printf("status: %d\n", status);
	return (0);
}

static int	run_interpreter(const char *source_code) {
	TokenList	token_list;
	if (lex(&token_list, source_code) < 0)
		return (-1);
	ASTNode		ast_root;
	if (parse(&ast_root, &token_list) < 0)
		return (-1);
	ASTNode		value;
	if (evaluate(&value, &ast_root) < 0)
		return (-1);
	int	status;
	if (encode(&status, &value) < 0)
		return (-1);
	return (status);
}
