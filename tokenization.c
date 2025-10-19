/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochmurzy <ochmurzy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:14:06 by ochmurzy          #+#    #+#             */
/*   Updated: 2025/10/19 20:55:54 by ochmurzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_token	*lexer(char *input, t_shell *shell)
{
	t_token	*list;
	t_token	*curr;
	int		i;

	list = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == ' ' || input[i] == '\t')
		{
			i++;
			continue ;
		}
		else if (input[i] == '\'' || input[i] == '"')
			curr = handle_quote(input, &i, shell);
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			curr = append_operator(input, &i);
		else
			curr = append_word(input, &i, shell);
		if (!curr)
			return (NULL);
		append_to_list(&list, curr);
	}
	return (list);
}

void	append_to_list(t_token **head, t_token *new_token)
{
	t_token	*last;

	if (!*head)
		*head = new_token;
	else
	{
		last = find_last(*head, offsetof(t_token, next));
		last->next = new_token;
	}
}
