#include "mini.h"

void	*safe_malloc(size_t bytes)
{
	void	*value;

	value = malloc(bytes);
	if (value == NULL)
		error_exit("Memory allocation problem!");
	return (value);
}
void swapping(char *input, int *i, char type_of_quote)
{
	//if (input[*i] == ' ')
	//	input[*i] = TEMP_SPACE_REPLACEMENT;
	if (input[*i] == type_of_quote)
		input[*i] = '\x1E';
	if (input[*i] == '|')
		input[*i] = '\x1D';
	if (input[*i] == '>')
		input[*i] = '\x1C';
	if (input[*i] == '<')
		input[*i] = '\x02';
	(*i)++;
}
int	is_builtin(const char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "pwd") == 0)
		return (1);
	if (ft_strcmp(name, "echo") == 0)
		return (1);
	if (ft_strcmp(name, "export") == 0)
		return (1);
	if (ft_strcmp(name, "unset") == 0)
		return (1);
	if (ft_strcmp(name, "env") == 0)
		return (1);
	if (ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}
