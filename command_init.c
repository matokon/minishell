#include "mini.h"

static void	init_cmd_defaults(t_cmd *cmd)
{
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->infile = NULL;
	cmd->in_fd = -1;
	cmd->last_in_type = 0;
	cmd->last_heredoc_idx = -1;
	cmd->outs = NULL;
	cmd->outs_len = 0;
	cmd->out_fd = -1;
	cmd->heredocs = NULL;
	cmd->heredoc_cnt = 0;
	cmd->next = NULL;
}

t_cmd	*command_init(t_shell **sh, t_cmd **head)
{
	t_cmd	*cmd;
	t_cmd	*last;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd_defaults(cmd);
	if (sh && *sh)
		(*sh)->count_cmds++;
	if (!head)
		return (cmd);
	if (!*head)
		*head = cmd;
	else
	{
		last = (t_cmd *)find_last(*head, offsetof(t_cmd, next));
		((t_cmd *)last)->next = cmd;
	}
	return (cmd);
}

static void	add_redir(t_cmd *command, const char *path, int append)
{
	t_outredir	*new_out;

	new_out = (t_outredir *)malloc(sizeof(t_outredir) * (command->outs_len + 1));
	if (!new_out)
		return ;
	if (command->outs_len > 0)
		ft_memcpy(new_out, command->outs, sizeof(t_outredir)
			* command->outs_len);
	new_out[command->outs_len].path = ft_strdup(path);
	if (!new_out[command->outs_len].path)
	{
		free(new_out);
		return ;
	}
	new_out[command->outs_len].append = append;
	free(command->outs);
	command->outs = new_out;
	command->outs_len++;
}

void	handle_redirects(t_cmd *command, t_token *tokens)
{
	if (!command->argv || !tokens->next || tokens->next->type != TOKEN_WORD)
		printf("Error: Wrong use of redirections :(\n");
	if (tokens->type == TOKEN_REDIRECT_IN)
	{
		if (command->infile)
			free(command->infile);
		command->infile = ft_strdup(tokens->next->value);
		command->last_in_type = 1;
	}
	else if (tokens->type == TOKEN_REDIRECT_OUT)
		add_redir(command, tokens->next->value, 0);
	else if (tokens->type == TOKEN_REDIRECT_APPEND)
		add_redir(command, tokens->next->value, 1);
}
static t_cmd	*handle_pipe(t_cmd *node, t_token *tokens)
{
	if (node->argv == NULL || tokens->next == NULL
		|| tokens->next->type != TOKEN_WORD)
		printf("Error: Wrong use of pipes :(\n");
	return (NULL);
}

void	add_cmd_argv(t_cmd *command, const char *arg)
{
	char	**upd_arg;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (command->argv)
	{
		while (command->argv[i])
		i++;
	}
	upd_arg = (char **)malloc(sizeof(char *) * (i + 2));
	if (!upd_arg)
		error_exit("Error: malloc error");
	while (++j < i)
		upd_arg[j] = ft_strdup(command->argv[j]);
	upd_arg[i] = ft_strdup(arg);
	upd_arg[i + 1] = NULL;
	if (command->argv)
	{
		i = 0;
		while (command->argv[i])
			free(command->argv[i++]);
		free(command->argv);
	}
	command->argv = upd_arg;
}

t_cmd *adding_command(t_token *tokens, t_shell *shell)
{
	t_cmd *node;

	if (!tokens)
		return NULL;
	node = NULL;
	while (tokens)
	{
		if (node == NULL)
			node = command_init(&shell, &shell->cmds);
		if (!node)
			return NULL;
		shell->cmds->argc++;
		if (tokens->type == TOKEN_WORD)
			add_cmd_argv(node, tokens->value);
		else if (tokens->type == TOKEN_REDIRECT_IN
				|| tokens->type == TOKEN_REDIRECT_OUT
				|| tokens->type == TOKEN_REDIRECT_APPEND)
			handle_redirects(node, tokens);
		else if (tokens->type == TOKEN_HEREDOC)
			add_heredoc(shell->cmds, tokens);
		else if (tokens->type == TOKEN_PIPE)
			node = handle_pipe(node, tokens);
		tokens = tokens->next;
	}
	return (shell->cmds);
}
