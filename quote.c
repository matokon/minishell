#include "mini.h"

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
            break ;
        while (i <= j && input[i])
		{
			if (type_of_quote != '\'' && input[i] == '$')
			{
				// TODO: 1. Obsłuż specjalną zmienną $? i rozwiń inne zmienne środowiskowe

                // TODO: 2. Przelicz pozycję zamykającego cudzysłowu po ewentualnych modyfikacjach stringa

			}
            //swap spacji itp.
		}
    }
    return input;
}