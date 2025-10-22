#include "mini.h"

static t_cmd	*child_cmd(t_cmd *head, int i)
{
	while (head && i-- > 0)
		head = head->next;
	return (head);
}

static char	*resolve_in_path(t_shell *sh, const char *bin)
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

static char	**env_list_to_envp(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*cur;
	char	*kv;
	char	*eq;

	i = 0;
	cur = env;
	while (cur && ++i)
		cur = cur->next;
	envp = (char **)safe_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		eq = ft_strjoin(env->key, "=");
		if (env->value)
			kv = ft_strjoin(eq, env->value);
		else
			kv = ft_strjoin(eq, "");
		free(eq);
		envp[i++] = kv;
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
		exit(call_builtin(sh, cmd->argv));
	envp = env_list_to_envp(sh->env);
	if (has_slash(cmd->argv[0]))
		path = ft_strdup(cmd->argv[0]);
	else
		path = resolve_in_path(sh, cmd->argv[0]);
	if (!path)
	{
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_split(envp);
		exit(127);
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
	apply_redirs(cmd);
	//if ((cmd->infile && *cmd->infile)
	//	|| cmd->heredoc_cnt > 0
	//	|| cmd->in_fd != -1)
	//{
	//	if (apply_in_redir(cmd) != 0)
	//		exit(1);
	//}
	//if (cmd->outs_len > 0 || cmd->out_fd != -1)
	//{
	//	if (apply_out_redir(cmd) != 0)
	//		exit(1);
	//}
	exec_child_command(sh, cmd);
}
