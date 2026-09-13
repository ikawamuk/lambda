#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "ast.h"

void print_value(Value *val);

AST	*make_var(char *name) {
	AST	*node = calloc(1, sizeof(AST));
	if (!node)
		return (NULL);
	node->type = AST_IDENTIFIER;
	node->name = strdup(name);
	if (!node->name)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

AST	*make_abs(char *param, AST *body) {
	AST	*node = calloc(1, sizeof(AST));
	if (!node)
		return (NULL);
	node->type = AST_ABSTRACT;
	node->abs.param = strdup(param);
	if (!node->abs.param)
	{
		free(node);
		return (NULL);
	}
	node->abs.body = body;
	return (node);
}

AST	*make_app(AST *func, AST *arg) {
	AST	*node = calloc(1, sizeof(AST));
	if (!node)
		return (NULL);
	node->type = AST_APPLICATE;
	node->app.func = func;
	node->app.arg = arg;
	return (node);
}

Value	*env_lookup(Env *env, const char *name) {
	while (env) {
		if (!strcmp(env->name, name))
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

Value	*evaluate(AST *node, Env *env);

Env	*env_extend(Env *env, const char *name, Value *val) {
	Env	*new_env = calloc(1, sizeof(Env));
	if (!new_env)
		return (NULL);
	new_env->name = strdup(name);
	new_env->val = val;
	new_env->next = env;
	return (new_env);
}

Value *evaluate_var(AST *node, Env *env) {
	Value *val = env_lookup(env, node->name);
	if (val)
		return (val);
	Value *v = calloc(1, sizeof(Value));
	if (!v)
		return (NULL);
	v->type = VAL_VAR;
	v->var_name = strdup(node->name);
	return (v);
}

Value *evaluate_abs(AST *node, Env *env) {
	Value *v = calloc(1, sizeof(Value));
	if (!v)
		return (NULL);
	v->type = VAL_CLOSURE;
	v->param = node->abs.param;
	v->body = node->abs.body;
	v->env = env;
	return (v);
}

Value *evaluate_app(AST *node, Env *env) {
	Value *func = evaluate(node->app.func, env);
	Value *arg = evaluate(node->app.arg, env);
	if (func && func->type == VAL_CLOSURE) {
		Env *new_env = env_extend(func->env, func->param, arg);
		return (evaluate(func->body, new_env));
	}
	return (NULL);
}

Value	*evaluate(AST *node, Env *env) {
	if (!node)
		return (NULL);
	switch (node->type) {
		case AST_IDENTIFIER:
			return (evaluate_var(node, env));
		case AST_ABSTRACT:
			return (evaluate_abs(node, env));
		case AST_APPLICATE:
			return (evaluate_app(node, env));
		default:
			return (NULL);
	}
}

void	print_value(Value *val) {
	if (!val)
		printf("<nil>\n");
	else if (val->type == VAL_CLOSURE)
		printf("<closure \\%s>\n", val->param);
	else if (val->type == VAL_VAR)
		printf("%s\n", val->var_name);
}

char	*read_file(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror("the file couldn't open");
		return (NULL);
	}
	fseek(file, 0, SEEK_END);
	long	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	char	*buffer = malloc(length + 1);
	if (!buffer) {
		fclose(file);
		return (NULL);
	}
	long	read_size = fread(buffer, 1, length, file);
	buffer[read_size] = '\0';
	fclose(file);
	return (buffer);
}

void skip_whitespace(Parser *parser) {
	while (*parser->p == ' ' || *parser->p == '\t' /* || *parser->p == '\n' */ || *parser->p == '\r') {
		parser->p++;
	}
}

char *parse_ident(Parser *parser) {
	skip_whitespace(parser);
	if (!isalnum(*parser->p))
		return (NULL);
	char *start = parser->p;
	while (isalnum(*parser->p)) {
		parser->p++;
	}
	int len = parser->p - start;
	char *name = malloc(len + 1);
	strncpy(name, start, len);
	name[len] = '\0';
	return (name);
}

AST *parse_expr(Parser *parser);

AST *parse_atom(Parser *parser) {
	skip_whitespace(parser);
	if (*parser->p == '\0') return (NULL);
	// 0. カッコの処理を追加
	if (*parser->p == '(') {
			parser->p++; // '(' をスキップ
			AST *node = parse_expr(parser);
			skip_whitespace(parser);
			if (*parser->p == ')') {
				parser->p++; // ')' をスキップ
			}
			return node;
		}
	if (*parser->p == '\\') {
		parser->p++; // '\' をスキップ
		char *param = parse_ident(parser);
		if (!param) return NULL;
		skip_whitespace(parser);
		/* if (*parser->p == '-' && *(parser->p + 1) == '>') {
			parser->p += 2; // "->" をスキップ
		} else */ if (*parser->p == '.') {
			parser->p++;    // "." をスキップ
		}
		AST *body = parse_expr(parser);
		AST *node = make_abs(param, body);
		free(param);
		return node;
	}

	// 2. 変数の場合
	char *name = parse_ident(parser);
	if (name) {
		AST *node = make_var(name);
		free(name);
		return node;
	}
	return NULL;
}

AST *parse_expr(Parser *parser) {
	// 最初の式（関数または変数）を取得
	AST *left = parse_atom(parser);
	if (!left)
		return (NULL);
	while (1) {
		skip_whitespace(parser);
		if (*parser->p == '\0' || *parser->p == '\n' || *parser->p == '\r' || *parser->p == ')')
			break;
		AST *right = parse_atom(parser);
		if (!right)
			break;
		// 連鎖的に適用ノードを作る（例: f x y -> (f x) y）
		left = make_app(left, right);
	}
	return (left);
}

int parse_let(Parser *parser, Env **global_env) {
	if (strncmp(parser->p, "let", 3) != 0 || (parser->p[3] != ' ' && parser->p[3] != '\t')) {
		return (0); // let 文ではない
	}

	parser->p += 3; // "let" をスキップ
	char *name = parse_ident(parser);
	skip_whitespace(parser);

	if (name && *parser->p == '=') {
		parser->p++; // '=' をスキップ
		AST *expr = parse_expr(parser);
		if (expr) {
			Value *val = evaluate(expr, *global_env);
			*global_env = env_extend(*global_env, name, val);
			printf("定義完了: %s\n", name);
			free(name);
			return (1); // 正常終了
		}
	}

	if (name)
		free(name);
	printf("定義エラーだにゃ\n");
	return (-1); // エラー
}

void run_program(char *source) {
	Parser parser = { .p = source };
	Env *global_env = NULL;

	while (*parser.p != '\0') {
		while (*parser.p == ' ' || *parser.p == '\t' || *parser.p == '\n' || *parser.p == '\r') {
			parser.p++;
		}
		if (*parser.p == '\0') break;
		int is_let = parse_let(&parser, &global_env);
		if (is_let == 1) {
			continue; // let成功時は次へ
		} else if (is_let == -1) {
			while (*parser.p != '\0' && *parser.p != '\n' && *parser.p != '\r') parser.p++;
			continue; // letエラー時も次へ
		}

		// 通常の式のパース・評価（ここで1回だけ実行する！）
		AST *ast = parse_expr(&parser);
		if (ast) {
			Value *val = evaluate(ast, global_env);
			printf("結果: ");
			print_value(val);
		} else {
			printf("パースエラーだにゃ\n");
			while (*parser.p != '\0' && *parser.p != '\n' && *parser.p != '\r') parser.p++;
		}

		skip_whitespace(&parser);
		// 行末の改行を消費する
		if (*parser.p == '\n') {
			parser.p++;
		} else if (*parser.p == '\r') {
			parser.p++;
			if (*parser.p == '\n') parser.p++; // CR-LF 対策
		}
	}
}



void print_ast(AST *node) {
	if (!node) return;
	if (node->type == AST_IDENTIFIER) {
		printf("%s", node->name);
	} else if (node->type == AST_ABSTRACT) {
		printf("(\\%s. ", node->abs.param);
		print_ast(node->abs.body);
		printf(")");
	} else if (node->type == AST_APPLICATE) {
		printf("(");
		print_ast(node->app.func);
		printf(" ");
		print_ast(node->app.arg);
		printf(")");
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <file name>\n", argv[0]);
		return (1);
	}
	char *source = read_file(argv[1]);
	if (!source)
		return (1);

	run_program(source);

	free(source);
	return (0);
}