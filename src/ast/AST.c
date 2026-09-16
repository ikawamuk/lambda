#include "AST.h"

void	ast_construct(AST *this) {
	this->root = NULL;
}

int	ast_abstruction(ASTNode *this, char *parameter, ASTNode *body) {
	return (0);
}

int	ast_appliacation(ASTNode *this, ASTNode *function, ASTNode *argument) {
	return (0);
}

int	ast_identifier(ASTNode *this, char *name, size_t index) {
	return (0);
}
