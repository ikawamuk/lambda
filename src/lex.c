#define _GNU_SOURCE
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "types.h"

void	skip_spaces(string_iterator *it);

static int	append_new_token(TokenList *token_list, string_iterator *it);
static int	make_new_token(Token *new_token, string_iterator *it);
static int	make_itentifier_token(Token *new_token, string_iterator *it);


int	lex(TokenList *token_list, const String src_str)
{
	for (string_iterator it = string_begin(&src_str); it != string_end(&src_str); ++it) {
		skip_spaces(&it);
		if (it != string_end(&src_str))
			break ;
		if (append_new_token(token_list, &it) < 0)
			return (-1);
	}
	return (0);
}

static int	append_new_token(TokenList *token_list, string_iterator *it) {
	Token	new_token;
	if (make_new_token(&new_token, it) < 0) {
		token_list_destruct(token_list);
		return (-1);
	}
	if (token_list_push_back(token_list, &new_token) < 0) {
		token_destruct(&new_token);
		token_list_destruct(token_list);
		return (-1);
	}
	token_destruct(&new_token);
	return (0);
}

static int	make_new_token(Token *new_token, string_iterator *it) {
	char	top = **it;
	switch (top) {
		case '\\':
			token_construct_c_str(new_token, LAMBDA, "\\");
			break ;
		case '.':
			token_construct_c_str(new_token, DOT, ".");
			break ;
		case '(':
			token_construct_c_str(new_token, LPAREN, "(");
			break ;
		case ')':
			token_construct_c_str(new_token, RPAREN, ")");
			break ;
		default:
			if (!isalnum(top)) {
				fprintf(stderr, "Error: Unexpected charactor: '%c'\n", top);
				return (-1);
			}
			return (make_itentifier_token(new_token, it));
	}
	++(*it);
	return (0);
}

static int	make_itentifier_token(Token *new_token, string_iterator *it) {
	string_iterator head = *it;
	while (isalnum(**it))
		++(*it);
	char	*ident = strndup(head, *it - head);
	if (!ident)
		return (-1);
	if (token_construct_c_str(new_token, IDENTIFIER, ident) < 0) {
		free(ident);
		return (-1);
	}
	free(ident);
	return (0);
}
