/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokon <mokon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:36:56 by mokon             #+#    #+#             */
/*   Updated: 2025/10/22 10:36:56 by mokon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	apply_in_redir(t_cmd *cmd)
{
	int	tmp;

	if (cmd->in_fd >= 0)
	{
		tmp = cmd->in_fd;
		if (dup2(tmp, STDIN_FILENO) < 0)
		{
			close(tmp);
			cmd->in_fd = -1;
			return (1);
		}
		close(tmp);
		cmd->in_fd = -1;
	}
	return (0);
}

int	apply_out_redir(t_cmd *cmd)
{
	int	tmp;

	if (cmd->out_fd >= 0)
	{
		tmp = cmd->out_fd;
		if (dup2(tmp, STDOUT_FILENO) < 0)
		{
			close(tmp);
			cmd->out_fd = -1;
			return (1);
		}
		close(tmp);
		cmd->out_fd = -1;
	}
	return (0);
}

int	has_slash(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		if (s[i++] == '/')
			return (1);
	return (0);
}

char	*resolve_in_path(t_shell *sh, const char *bin)
{
	t_env	*e;
	char	**paths;
	char	*full;
	int		i;

	e = find_env(sh->env, "PATH");
	if (!e || !e->value || !*e->value)
		return (NULL);
	paths = ft_split(e->value, ':');
	i = 0;
	while (paths && paths[i])
	{
		full = join_path(paths[i], bin);
		if (access(full, X_OK) == 0)
			return (free_split(paths), full);
		free(full);
		i++;
	}
	free_split(paths);
	return (NULL);
}

void	exit_cmd_not_found(char *name, char **envp)
{
	ft_putstr_fd(name, 2);
	ft_putendl_fd(": command not found", 2);
	free_split(envp);
	exit(127);
}
