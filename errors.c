#include "mini.h"

void	error_exit(const char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

void	input_error_check(const char *input)
{
	if (!logical_operators_check(input))
		error_exit("Error: Not supported command\n");
}

bool	logical_operators_check(const char *input)
{
	size_t	i;

	i = -1;
	while (input[++i])
	{
		if ((input[i] == '&' && input[i + 1] == '&')
			|| (input[i] == '|' && input[i + 1] == '|'))
			return (false);
		if (input[i] == '\\' || input[i] == ';')
			return (false);
	}
	return (true);
}
