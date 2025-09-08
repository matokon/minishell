#include "mini.h"

t_cmd	*command_init(t_shell **shell, t_cmd **head)
{
	t_cmd	*command;
	t_cmd	*last;

	command = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!command)
		printf("Error: malloc error");
	command->next = NULL;
	(*shell)->count_cmds++;
	if (*head == NULL)
		*head = command;
	else
	{
		last = find_last(*head, offsetof(t_cmd, next));
		last->next = command;
	}
	return (command);
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
		command->infile = ft_strdup(tokens->next->value);
	if (tokens->type == TOKEN_REDIRECT_OUT)
		add_redir(command, tokens->next->value, 0);
	if (tokens->type == TOKEN_REDIRECT_APPEND)
		add_redir(command, tokens->next->value, 1);
}
static t_cmd	*handle_pipe(t_cmd *node, t_token *tokens)
{
	if (node->argv == NULL || tokens->next == NULL
		|| tokens->next->type != TOKEN_WORD)
		error_exit("Error: Wrong use of pipes :(\n");
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
		//printf("Added arg in if: %s\n", upd_arg[i]);
		while (command->argv[i])
			free(command->argv[i++]);
		free(command->argv);
	}
	//else
	//	printf("Added arg in else: %s\n", upd_arg[0]);
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
		//printf("node->argv: %d\n", shell->cmds->argv ? 1 : 0);
		if (tokens->type == TOKEN_WORD)//DOESNT WORK
			add_cmd_argv(node, tokens->value);
		else if (tokens->type == TOKEN_REDIRECT_IN
				|| tokens->type == TOKEN_REDIRECT_OUT
				|| tokens->type == TOKEN_REDIRECT_APPEND)
			handle_redirects(node, tokens);
		else if (tokens->type == TOKEN_HEREDOC)
			add_heredoc(shell->cmds, tokens);
		else if (tokens->type == TOKEN_PIPE)
			node = handle_pipe(node, tokens);
		//printf("Token type: %d,\nvalue: %s,\nnext: %p\n",
		//	tokens->type,
		//	tokens->value ? tokens->value : "(null)",
		//	(void*)tokens->next);
		tokens = tokens->next;
	}
	return (shell->cmds);
}
