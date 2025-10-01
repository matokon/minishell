#include "mini.h"

static char	*ft_replace(char *s, char *var, char *val, int pos)
{
	int	s_len;
	int	var_len;

	if (!s || !var || !val)
		return (NULL);
	s_len = ft_strlen(s);
	var_len = ft_strlen(var);
	if (pos < 0 || pos >= s_len)
		return (ft_strdup(s));
	if (ft_strncmp(s + pos, var, var_len) != 0)
		return (ft_strdup(s));
	return (handle_replacement(s, val, pos, var_len));
}
static int find_first_quote(char *input, int i)
{
    while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			return (i);
		i++;
	}
	return (-1);
}
static int find_second_quote(char *input, int i, char type_of_quote)
{
    while (input[i])
        {
            if (input[i] == type_of_quote)
                return (i);
            i++;
        }
        return (-1);
}
static void	if_question_mark(char **input, int i, t_shell shell)
{
	char	*itoa;

	itoa = ft_itoa(shell.last_status);
	if ((*input)[i + 1] == '?')
		*input = ft_replace(*input, "$?", itoa, i);
	free(itoa);
	find_env(shell.env, shell.env->key);
}


char *deal_with_quotes(char *input, t_shell shell)
{
    char type_of_quote;
    int i;
    int j;

    i = 0;
    while(input[i] && (ft_strchr(input, '"') || ft_strchr(input, '\'')))
    {
        i = find_first_quote(input, i);
        if(i == -1)
            break ;
        type_of_quote = input[i];
        j = find_second_quote(input, i + 1, type_of_quote);
        if(j == -1)
            return NULL;
        while (i <= j && input[i])
		{
			if (type_of_quote != '\'' && input[i] == '$')
			{
				if_question_mark(&input, i, shell);
                j = find_second_quote(input, i + 1, type_of_quote);
				//comment
			}
			i++;
		}
    }
    return input;
}