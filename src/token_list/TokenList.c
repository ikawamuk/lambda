#include <stdlib.h>
#include "TokenList.h"

void	token_list_construct(TokenList *this) {
	this->head = NULL;
	this->tail = NULL;
	this->size = 0;
}

int	token_list_push_back(TokenList *this, const Token *new_token) {
	TokenNode	*new_node = calloc(1, sizeof(TokenNode));
	if (!new_node)
		return (-1);
	if (!token_assign(&new_node->data, &new_token)) {
		free(new_node);
		return (-1);
	}
	new_node->next = NULL;
	new_node->prev = this->tail;
	if (!this->head)
		this->head = new_node;
	else
		this->tail->next = new_node;
	this->tail = new_node;
	++this->size;
	return (0);
}

void	token_list_destruct(TokenList *this) {
	TokenNode	*cur = this->head;
	while (cur) {
		destructToken(&cur->data);
		cur = cur->next;
	}
}

int	token_construct_c_str(Token *this, TokenType type, char *c_str) {
	this->type = type;
	if (string_construct(&this->literal, c_str) < 0)
		return (-1);
	return (0);
}

int	token_construct(Token *this, TokenType type, String literal) {
	this->type = type;
	if (!string_assign(&this->literal, &literal))
		return (-1);
	return (0);
}

Token	*token_assign(Token *this, const Token *rhs) {
	if (!this || !rhs) return (NULL);
	if (this != rhs) {
		String	*tmp;
		if (!string_assign(tmp, &rhs->literal))
			return (NULL);
		this->type = rhs->type;
	}
	return (this);
}

void	token_destruct(Token *this)
{
	string_destruct(&this->literal);
}
