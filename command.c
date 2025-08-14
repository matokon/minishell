#include "mini.h"

t_cmd	*command_init(t_cmd **head)
{
	t_cmd	*command;
	t_cmd	*last;

	command = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!command)
		return (NULL);
	command->next = NULL;
	if (*head == NULL)
		*head = command;
	else
	{
		last = find_last(*head, offsetof(t_cmd, next));
		last->next = command;
	}
	return (command);
}

void	add_cmd_argv(t_cmd *command, const char *arg)
{
	char	**upd_arg;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (command->argv)
		i++;
	upd_arg = (char **)malloc(sizeof(char *) * (i + 2));
	if (!upd_arg)
		return ;
	while (++j < i)
		upd_arg[j] = command->argv[j];
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
	new_out[command->outs_len].append = append;
	free(command->outs);
	command->outs = new_out;
	command->outs_len++;
}

void	handle_redirects(t_cmd *command, t_token *tokens)
{
	if (!command->argv || !tokens->next || tokens->next->type != TOKEN_WORD)
		error_exit("Error: Wrong use of redirections :(\n");
	if (tokens->type == TOKEN_REDIRECT_IN)
		command->infile = ft_strdup(tokens->next->value);
	if (tokens->type == TOKEN_REDIRECT_OUT)
		add_redir(command, tokens->value, 0);
	if (tokens->type == TOKEN_REDIRECT_APPEND)
		add_redir(command, tokens->value, 0);
}

t_cmd	*adding_command(t_token *tokens)
{
	t_cmd	*commands;
	t_cmd	*node;

	if (!tokens)
		return (NULL);
	while (tokens)
	{
		if (node == NULL)
			node = command_init(commands);
		else if (tokens->type == TOKEN_WORD)
			add_cmd_argv(node, tokens->value);
		else if (tokens->type == TOKEN_REDIRECT_IN
			|| tokens->type == TOKEN_REDIRECT_OUT
			|| tokens->type == TOKEN_REDIRECT_APPEND)
			handle_redirects(node, tokens);
		else if (tokens->type == TOKEN_HEREDOC)
		else if (tokens->type == TOKEN_PIPE)
		{
			if (node->argv == NULL || tokens->next->type != TOKEN_WORD
				|| !tokens->next)
				error_exit("Error: Wrong use of pipes :(\n");
			node = NULL;
		}
		tokens = tokens->next;
	}
	return (commands);
}
