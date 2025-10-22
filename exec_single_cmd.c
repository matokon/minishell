/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokon <mokon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:35:53 by mokon             #+#    #+#             */
/*   Updated: 2025/10/22 10:35:53 by mokon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*join_path(const char *dir, const char *bin)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(dir, "/");
	res = ft_strjoin(tmp, bin);
	free(tmp);
	return (res);
}

static t_cmd	*child_cmd(t_cmd *head, int i)
{
	while (head && i-- > 0)
		head = head->next;
	return (head);
}

static char	**env_list_to_envp(t_env *env)
{
	int		len;
	char	**envp;
	int		i;
	char	*eq;
	char	*val;

	len = env_len(env);
	envp = (char **)safe_malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (env)
	{
		eq = ft_strjoin(env->key, "=");
		if (env->value)
			val = env->value;
		else
			val = "";
		envp[i++] = ft_strjoin(eq, val);
		free(eq);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

static void	exec_child_command(t_shell *sh, t_cmd *cmd)
{
	char	**envp;
	char	*path;

	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv[0]))
	{
		exit(call_builtin(sh, cmd->argv));
	}
	envp = env_list_to_envp(sh->env);
	if (has_slash(cmd->argv[0]))
		path = ft_strdup(cmd->argv[0]);
	else
		path = resolve_in_path(sh, cmd->argv[0]);
	if (!path)
	{
		exit_cmd_not_found(cmd->argv[0], envp);
	}
	execve(path, cmd->argv, envp);
	perror(path);
	free_split(envp);
	free(path);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

void	child(t_shell *sh, t_execctx *x, int i)
{
	t_cmd	*cmd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cmd = child_cmd(sh->cmds, i);
	if (!cmd)
		exit(0);
	wire_child_pipes(x, i);
	close_all_pipes(x);
	if ((cmd->infile && *cmd->infile)
		|| cmd->heredoc_cnt > 0
		|| cmd->in_fd != -1)
	{
		if (apply_in_redir(cmd) != 0)
			exit(1);
	}
	if (cmd->outs_len > 0 || cmd->out_fd != -1)
	{
		if (apply_out_redir(cmd) != 0)
			exit(1);
	}
	exec_child_command(sh, cmd);
}
