#include <stdbool.h>
#include "../string/String.h"

bool	is_white_space(char c);

void	skip_spaces(string_iterator *it) {
	while (is_white_space(**it))
		++(*it);
}
