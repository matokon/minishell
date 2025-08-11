#include "mini.h"

t_cmd	*command_init(t_cmd **head)
{
	t_cmd	*command;
	t_cmd *last;

	command = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!command)
		return (NULL);
	//nw o co chodzi z tym fd i jak ja mam pozniej dopisac jakas wartosc
	//do tego. Narazie jest na -1, by oznaczyc ze jest nie otwarte
	//wiec jak nie powiesz o co chodzi to ty to robisz...
	//w ogole ty moglbys to zrobic xd
	//new_node->in_fd = -1; <-------THISS
    //new_node->out_fd = -1; <------THISS
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

t_cmd	*parsing(t_token *tokens)
{
	t_cmd	*commands;
	t_cmd	*node;
	
	if (!tokens)
		return (NULL);
	while (tokens)
	{
		if (node == NULL)
			node = create_command(commands);
		else if (tokens->type == TOKEN_WORD)	
				node->argv = ;
		else if (tokens->type == TOKEN_REDIRECT_IN)
			
		else if (tokens->type == TOKEN_REDIRECT_OUT)
		else if (tokens->type == TOKEN_REDIRECT_APPEND)
		else if (tokens->type == TOKEN_HEREDOC)
		else if (tokens->type == TOKEN_PIPE)

		tokens = tokens->next;
	}
	return (commands);
}