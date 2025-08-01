/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochmurzy <ochmurzy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:37:43 by ochmurzy          #+#    #+#             */
/*   Updated: 2025/08/01 19:10:32 by ochmurzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_env	*find_last(t_env *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next != NULL)
		stack = stack->next;
	return (stack);
}

void	split_env(t_env **stack, char **str)
{
	t_env	*last_node;
	t_env	*new_node;
	
	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return ;
	new_node->value = ft_strdup(str[1]);
	new_node->key = ft_strdup(str[0]);
	new_node->next = NULL;
	if (*stack == NULL)
		*stack = new_node;
	else
	{
		last_node = find_last(*stack);
		last_node->next = new_node;
	}
	free(str[0]);
	free(str[1]);
}

void	create_list_env(t_env **stack, char **env)
{
	t_env	*stack;
	char	**str;
	int	i;
	
	i = 0;
	stack = NULL;
	while (env[i])
	{
		str = ft_split(env[i], '=');
		if (!str)
			return ;
		split_env(stack, str);
		free(str);
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	t_env	*stack;
	
	(void)argc;
	(void)argv;
	stack = NULL;
	create_stack(&stack, env);
	print_stack_all(stack);
	return (0);
}