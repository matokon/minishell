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
	if (input[*i] == ' ')
		input[*i] = TEMP_SPACE_REPLACEMENT;
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
int is_builtin(const char *name)
{
    if (!name) return 0;
    return (!ft_strcmp(name, "cd")
         || !ft_strcmp(name, "echo")
         || !ft_strcmp(name, "pwd")
         || !ft_strcmp(name, "env")
         || !ft_strcmp(name, "export")
         || !ft_strcmp(name, "unset")
         || !ft_strcmp(name, "exit"));
}
