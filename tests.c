/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochmurzy <ochmurzy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:04:30 by ochmurzy          #+#    #+#             */
/*   Updated: 2025/08/26 21:14:42 by ochmurzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void print_all_env(const t_env *stack)
{
	int i = 0;

	printf("---- Env ----\n");
	while (stack)
	{
		printf("Node %d:\n", i++);
		printf("  key      = %s\n", stack->key);
		printf("  value    = %s\n", stack->value);
		if (stack->next)
			printf("  next     = %s\n", stack->next->key);
		else
			printf(" next = ( )\n");
		stack = stack->next;
	}
	printf("---------------------\n");
}

void print_env(t_env *stack, const char *key)
{
	t_env	*node;

	node = find_env(stack, key);
	printf("---- Env: %s\n", key);
	if (node->key)
		printf("  key      = %s\n", node->key);
	else
		printf(" ( )");
	if (node->value)
		printf("  value    = %s\n", node->value);
	else
		printf(" ( )");
	printf("----------------\n");
}
void	print_one_env(t_env *stack)
{
	printf("---- Env ----\n");
	printf("  key      = %s\n", stack->key);
	printf("  value    = %s\n", stack->value);
	if (stack->next)
		printf("  next     = %s\n", stack->next->key);
	else
		printf(" next = ( )\n");
	printf("---------------------\n");
}

void print_all_tokens(const t_token *stack)
{
	int i = 0;

	printf("---- Tokens ----\n");
	while (stack)
	{
		printf("Node %d:\n", i++);
		printf("  type      = %u\n", stack->type);
		printf("  value    = %s\n", stack->value);
		if (stack->next)
			printf("  next     = %u\n", stack->next->type);
		else
			printf("(_)");
		stack = stack->next;
	}
	printf("---------------------\n");
}
