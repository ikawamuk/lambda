#include <stdio.h>
#include "src/types.h"
#include "src/string/String.h"

int	lex(TokenList *token_list, const String src_str);
// int	parse(ASTNode *ast_root, const TokenList *token_list);
// int	evaluate(ASTNode *value, const ASTNode *ast_root);
// int	encode(int *status, const ASTNode *value);

static int	run_interpreter(const char *source_code);

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
	String		src_str;
	if (string_construct(&src_str, source_code) < 0)
		return (-1);
	TokenList	token_list;
	token_list_construct(&token_list);
	if (lex(&token_list, src_str) < 0) {
		string_destruct(&src_str);
		token_list_destruct(&token_list);
		return (-1);
	}
	token_list_print(&token_list);
	string_destruct(&src_str);
	// ASTNode		ast_root;
	// if (parse(&ast_root, &token_list) < 0)
	// 	return (-1);
	// ASTNode		value;
	// if (evaluate(&value, &ast_root) < 0)
	// 	return (-1);
	// int	status;
	// if (encode(&status, &value) < 0)
	// 	return (-1);
	// return (status);
	return (0);
}
