/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochmurzy <ochmurzy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:37:43 by ochmurzy          #+#    #+#             */
/*   Updated: 2025/08/10 21:29:53 by ochmurzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	*find_last(void *stack, size_t offset)
{
	if (!stack)
		return (NULL);
	while (*(void **)(stack + offset) != NULL)
	{
		stack = *(void **)(stack + offset);
		return (void *)stack;
	}
	return (stack);
}

void	split_env(t_env **stack, char **str)
{
	t_env	*last_node;
	t_env	*new_node;
	
	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return ;
	if (str[0])
		new_node->key = ft_strdup(str[0]);
	else
		new_node->key = NULL;
	if (str[1])
		new_node->value = ft_strdup(str[1]);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	if (*stack == NULL)
		*stack = new_node;
	else
	{
		last_node = find_last(*stack, offsetof(t_env, next));
		last_node->next = new_node;
	}
	free(str[0]);
	free(str[1]);
}

void	create_list_env(t_env **stack, char **env)
{
	//zeby to dzialalo trzeba zainicjalizowac liste tzn: t_env lista = NULL;~Oliwia
	char	**str;
	int	i;
	
	i = -1;
	while (env[++i])
	{
		str = ft_split(env[i], '=');
		if (!str)
			return ;
		split_env(stack, str);
		free(str);
	}
}
