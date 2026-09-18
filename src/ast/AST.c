#define _GNU_SOURCE
#include <string.h>
#include "../string/String.h"
#include "token_list/TokenList.h"
#include "AST.h"

void	ast_construct(AST *this) {
	this->data = NULL;
}

void	ast_destruct(AST *this) {
	ast_node_destruct(this->data);
	free(this->data);
}

int	ast_move(AST *dest, AST *src) {
	if (!src)
		return (-1);
	*dest = *src;
	src->data = NULL;
	return (0);
}

int	ast_append_abstraction(AST *this, Abstruction *abstruction) {
	ASTNode	*node = calloc(1, sizeof(ASTNode));
	if (!node)
		retur (-1);
	node->type = AST_ABSTRUCTION;
	if (abstruction_move(&node->abstruction, abstruction) < 0) {
		free(node);
		return (-1);
	}
	this->data = node;
	return (0);
}

int	ast_append_application(AST *this, Application *application) {
	ASTNode	*node = calloc(1, sizeof(ASTNode));
	if (!node)
		retur (-1);
	node->type = AST_APPLICATION;
	if (application_move(&node->abstruction, application) < 0) {
		free(node);
		return (-1);
	}
	this->data = node;
	return (0);
}

int	ast_append_variable(AST *this, String *variable) {
	ASTNode	*node = calloc(1, sizeof(ASTNode));
	if (!node)
		retur (-1);
	node->type = AST_VARIABLE;
	if (string_move(&node->variable, variable) < 0) {
		free(node);
		return (-1);
	}
	this->data = node;
	return (0);
}

static void	ast_node_destruct(ASTNode *this) {
	switch (this->type)
	{
	case AST_ABSTRUCTION:
		abstruction_destruct(&this->abstruction);
		break ;
	case AST_APPLICATION:
		application_destruct(&this->application);
		break ;
	case AST_VARIABLE:
		variable_destruct(&this->variable);
		break ;
	default:
		break;
	}
}

int	abstruction_move(Abstruction *dest, Abstruction *src) {
	if (!dest || !src)
		return (-1);
	string_move(&dest->body, &src->body);
	ast_move(&dest->body, &src->body);
	return (0);
}

void	abstruction_destruct(Abstruction *this) {
	string_destruct(&this->parameter);
}

int	application_move(Application *dest, Application *src) {
	if (!dest || !src)
		return (-1);
	ast_move(&dest->function, &src->function);
	ast_move(&dest->argument, &src->argument);
	return (0);
}

void	application_destruct(Application *this) {
	ast_destruct(&this->function);
	ast_destruct(&this->argument);
}

void	variable_destruct(Variable *this) {
	string_destruct(&this->name);
}
