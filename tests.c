/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochmurzy <ochmurzy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:04:30 by ochmurzy          #+#    #+#             */
/*   Updated: 2025/08/01 19:04:55 by ochmurzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void print_stack_all(const t_env *stack)
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
			printf(" ( )");
		stack = stack->next;
	}
	printf("---------------------\n");
}