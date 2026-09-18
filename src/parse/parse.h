#ifndef PARSE_H
# define PARSE_H

#include "token_list/TokenList.h";

typedef struct ParseState {
	const TokenList	*list_ptr;
	TokenNode		*cur;
}	ParseState;

TokenType	peek_type(ParseState *this);

#endif
