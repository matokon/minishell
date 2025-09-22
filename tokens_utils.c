#include "mini.h"

t_token *append_operator(char *input, int i)
{
	t_token *new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (input[i] == '|')
	{
		new_token->type = TOKEN_PIPE;
		new_token->value = ft_strdup("|");
	}
	else if (input[i] == '>' || input[i] == '<')
		helper_redir(input, i, new_token);
	else
	{
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

void	helper_redir(char *input, int i, t_token *new_token)
{
	if (input[i + 1] == '>')
	{
		new_token->type = TOKEN_REDIRECT_APPEND;
		new_token->value = ft_strdup(">>");
	}
	else
	{
		new_token->type = TOKEN_REDIRECT_OUT;
		new_token->value = ft_strdup(">");
	}
	if (input[i + 1] == '<')
	{
		new_token->type = TOKEN_HEREDOC;
		new_token->value = ft_strdup("<<");
	}
	else
	{
		new_token->type = TOKEN_REDIRECT_IN;
		new_token->value = ft_strdup("<");
	}
}

t_token *expand_quotes(char *input, int i)
{
	t_token *new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (input[i] == '\'')
	{

	}
	else if (input[i] == '\"')

	new_token->next = NULL;
	return (new_token);
}

//Template
//t_token *append_x()
//{
//	t_token *new_token;

//	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
//	if (!new_token)
//		return (NULL);
//	// ustawić typ i wartość tokena
//	new_token->next = NULL;
//	return (new_token);
//}