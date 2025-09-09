#include "mini.h"

static void	one_cmd_free(t_cmd *cmd)// TODO NORMINETTE mokon
{
	int i;

	if (!cmd)
		return ;
	if (cmd->argv != NULL)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outs)
	{
		i = -1;
		while (++i < cmd->outs_len)
		{
			if (cmd->outs[i].path)
				free(cmd->outs[i].path);
		}
		free(cmd->outs);
	}
	if (cmd->heredocs)
		free_hrdc(cmd);
}

void	cmds_free(t_shell *shell)
{
	t_cmd	*curr;
	t_cmd	*next;

	if (!shell || !shell->cmds)
		return;
	curr = shell->cmds;
	while (curr)
	{
		next = curr->next;
		one_cmd_free(curr);
		free(curr);
		curr = next;
	}
	shell->cmds = NULL;
	shell->count_cmds = 0;
}


void	free_hrdc(t_cmd *command)
{
	int	i;

	i = command->heredoc_cnt;
	while (i--)
	{
		free(command->heredocs[i].delim);
		free(command->heredocs[i].tmp_path);
	}
	free(command->heredocs);
	command->heredocs = NULL;
	command->heredoc_cnt = 0;
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->value)
			free(head->value);
		free(head);
		head = tmp;
	}
}

void	free_env_list(t_env *env)
{
	t_env *tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}