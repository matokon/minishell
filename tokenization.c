#include "mini.h"

static int len_of_input(char *input)
{
    int len;
    int i;

    i=-1;
    len =0;
    while(input[++i])
    {
		if (input[i] == '|')
			len += 2;
		if (input[i] == '<' || input[i] == '>')
		{
			if (input[i + 1] == '<' || input[i + 1] == '>')
			{
				i++;
				len++;
			}
			len += 2;
		}
		len++;
	}
    return len;
}
static void add_spaces(char *input, char *parsed_input, int *i, int *j)
{
    if (input[*i] == '<' || input[*i] == '>')
	{
		parsed_input[*i + *j] = ' ';
		(*j)++;
		parsed_input[*i + *j] = input[*i];
		if (input[*i + 1] == '<' || input[*i + 1] == '>')
		{
			(*i)++;
			parsed_input[*i + *j] = input[*i];
		}
		(*j)++;
		parsed_input[*i + *j] = ' ';
	}
    if (input[*i] == '|')
	{
		parsed_input[*i + *j] = ' ';
		parsed_input[*i + *j + 1] = '|';
		*j += 2;
		parsed_input[*i + *j] = ' ';
	}
}

char **split_input_to_tokens(char *input)
{
    char **table_of_tokens;
    char *parsed_input;
    int i;
    int j;

    i = -1;
    j = 0;
    parsed_input = safe_malloc(len_of_input(input) + 1);
    while(input[++i])
    {
        if(input[i] == '|' || input[i] == '>' || input[i] == '<')
        {
            add_spaces(input, parsed_input, &i, &j);
			continue ;
        }
        parsed_input[i + j] = input[i];
    }
    parsed_input[i + j] = 0;
    table_of_tokens = ft_split(parsed_input, ' ');
	free (parsed_input);
	//
	free(input);
	return (table_of_tokens);
}
