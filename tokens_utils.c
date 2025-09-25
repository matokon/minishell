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

t_token *expand_var(char *input, int i, t_env *env)
{
	t_token *new_token;
	t_env *expand;
	char *var_name;
	int j;

	j = 0;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		var_name[j++] = input[i++];
	var_name[j] = '\0';
	var_name = (char *)malloc(sizeof(char) * j + 1);
	if (!var_name)
		return (NULL);
	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	expand = find_env(env, var_name);
	if (expand)
		new_token->value = ft_strdup(expand->value);
	else
		new_token->value = ft_strdup("");
	free(var_name);
	new_token->type = TOKEN_WORD;
	new_token->next = NULL;
	return (new_token);
}

t_token *expand_var(char *input, int i, t_env *env)
{
	t_token *new_token;
	t_env *expand;
	char *var_name;
	int j;

	i++;
	j = 0;
	expand = find_env(env, var_name);
	if (expand)
		new_token->value = ft_strdup(expand->value);
	else
		new_token->value = ft_strdup("");
	new_token->type = TOKEN_WORD;
	new_token->next = NULL;
	return (new_token);
}

t_token	*append_word(char *input, int i)
{
	t_token *new_token;
	char	*word;
	int j;
	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		word[j++] = input[i++];
	new_token->type = TOKEN_WORD;
	new_token->next = NULL;
	return (new_token);
}