/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochmurzy <ochmurzy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:04:30 by ochmurzy          #+#    #+#             */
/*   Updated: 2025/09/25 18:01:34 by ochmurzy         ###   ########.fr       */
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
	if (stack->next)
		printf("  next     = %s\n", stack->next->key);
	else
		printf(" next = ( )\n");
	printf("----------------\n");
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
//void	print_all_cmd(const t_cmd *stack)
//{
//	int i = 0;
//	int j = 0;
//	printf("---- Env ----\n");
//	while (stack)
//	{
//		printf("Node %d:\n", i++);
//		if (stack->argv)
//			printf("  argv      = %d\n", stack->argv[i]);
//		printf("  argc      = %d\n", stack->argc);
//		if (stack->infile)
//			printf("  infile    = %s\n", stack->infile);
//		while (j < stack->outs_len && stack->outs)
//		{
//			printf("  out path  = %s\n", stack->outs->path);
//			printf("  append    = %d\n", stack->outs->append);
//			j++;
//		}
//		j = 0;
//		while (j < stack->heredoc_cnt && stack->heredocs)
//		{
//			printf("  delim = %s\n", stack->heredocs->delim);
//			printf(" tmp path    = %d\n", stack->heredocs->tmp_path);
//			j++;
//		}
//		if (stack->next)
//			printf("  next     = %s\n", stack->next->argv[i]);
//		else
//			printf(" next = ( )\n");
//		stack = stack->next;
//	}
//	printf("---------------------\n");
//}

void print_cmd_struct(const t_cmd *cmd)
{
    int i;
    if (!cmd)
    {
        printf("No command struct!\n");
        return;
    }
    
	while (cmd)
	{	
		printf("---- t_cmd struct ----\n");
		printf("argc: %d\n", cmd->argc);
		printf("argv: ");
		if (cmd->argv)
		{
			for (i = 0; cmd->argv[i]; i++)
				printf("[%s] ", cmd->argv[i]);
			printf("\n");
		}
		else
			printf("(null)\n");

		printf("infile: %s\n", cmd->infile ? cmd->infile : "(null)");
		printf("in_fd: %d\n", cmd->in_fd);

		printf("outs_len: %d\n", cmd->outs_len);
		for (i = 0; i < cmd->outs_len; i++)
		{
			printf("  outs[%d]: path='%s', append=%d\n", i,
				cmd->outs[i].path ? cmd->outs[i].path : "(null)",
				cmd->outs[i].append);
		}
		printf("out_fd: %d\n", cmd->out_fd);

		printf("heredoc_cnt: %d\n", cmd->heredoc_cnt);
		for (i = 0; i < cmd->heredoc_cnt; i++)
		{
			printf("  heredocs[%d]: delim='%s', tmp_path='%s'\n", i,
				cmd->heredocs[i].delim ? cmd->heredocs[i].delim : "(null)",
				cmd->heredocs[i].tmp_path ? cmd->heredocs[i].tmp_path : "(null)");
		}
		printf("next: %p\n", (void*)cmd->next);
		cmd = cmd->next;
	}
    printf("----------------------\n");
}