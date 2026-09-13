#ifndef AST_H
# define AST_H

typedef enum {
	AST_ABSTRACT,
	AST_APPLICATE,
	AST_IDENTIFIER,
}	AstType;

typedef enum { VAL_CLOSURE, VAL_VAR } ValType;

struct Value;
struct Env;

typedef struct AST {
	AstType	type;
	union {
		struct { char *param; struct AST *body; } abs; // AST_ABS
		struct { struct AST * func; struct AST *arg; } app; // AST_APP
		char	*name; // AST_IDENTIFIER
	};
}	AST;

typedef struct Value {
	ValType		type;
	union {
		struct { // VAL_CLOSURE
			char		*param;
			AST			*body;
			struct Env	*env;
		};
		char			*var_name; // VAL_VAR
	};
} Value;

typedef struct Env {
	char		*name;
	Value		*val;
	struct Env	*next;
} Env;

typedef struct {
	char *p; // 現在読んでいる位置
} Parser;

#endif
