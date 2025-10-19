/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochmurzy <ochmurzy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:41:51 by ochmurzy          #+#    #+#             */
/*   Updated: 2025/10/19 18:51:38 by ochmurzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	find_second_quote(char *input, int i, char type_of_quote)
{
	while (input[i])
	{
		if (input[i] == type_of_quote)
			return (i);
		i++;
	}
	return (-1);
}

t_token	*handle_quote(char *input, int *i, t_shell *shell)
{
	t_token	*new_token;
	char	*word;
	char	*tmp;
	char type_of_quote;
	int j;

	word = ft_strdup("");
	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	type_of_quote = input[*i];
	j = find_second_quote(input, *i + 1, type_of_quote);
	(*i)++;
	while (input[*i] && *i < j)
	{
		if (input[*i] == '$' && type_of_quote == '"')
		{
			tmp = expand_var(input, i, shell);
			word = join_free(&word, tmp);
			free(tmp);
		}
		else
		{
			word = join_char(&word, input[*i]);
			(*i)++;
		}
	}
	if (input[*i] == type_of_quote)
        (*i)++;
	new_token->type = TOKEN_WORD;
	new_token->value = word;
	return (new_token);
}