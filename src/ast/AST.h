#ifndef AST_H
# define AST_H

# include <stddef.h>
# include "../string/String.h"

typedef struct AST		AST;
typedef struct ASTNode	ASTNode;
typedef enum ASTType	ASTType;

enum ASTType {
	AST_ABSTRUCTION,
	AST_APPLICATION,
	AST_VARIABLE
};

typedef struct Abstruction	Abstruction;
typedef struct Application	Application;
typedef struct Variable		Variable;

struct Abstruction {
	String	parameter;
	AST		body;
};

void	abstruction_destruct(Abstruction *this);
int		abstruction_move(Abstruction *dest, Abstruction *src);

struct Application {
	AST	function;
	AST	argument;
};

void	application_destruct(Application *this);
int		application_move(Application *dest, Application *src);

struct Variable {
	size_t	index;
	String	name;
};

void	variable_destruct(Variable *this);

struct ASTNode {
	ASTType	type;
	union {
		Abstruction	abstruction;
		Application	application;
		Variable	variable;
	};
};

struct AST {
	ASTNode	*data;
};

void	ast_construct(AST *this);
int		ast_move(AST *dest, AST *src);
void	ast_destruct(AST *this);
int		ast_append_abstraction(AST *this, Abstruction *abstruction);
int		ast_append_application(AST *this, Application *application);
int		ast_append_variable(AST *this, String *variable);
#endif
