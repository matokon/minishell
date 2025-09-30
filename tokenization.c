#include "mini.h"

//static int len_of_input(char *input)
//{
//    int len;
//    int i;

//    i = -1;
//    len = 0;
//    while(input[++i])
//    {
//		if (input[i] == '|')
//			len += 2;
//		if (input[i] == '<' || input[i] == '>')
//		{
//			if (input[i + 1] == '<' || input[i + 1] == '>')
//			{
//				i++;
//				len++;
//			}
//			len += 2;
//		}
//		len++;
//	}
//    return len;
//}
//static void add_spaces(char *input, char *parsed_input, int *i, int *j)
//{
//    if (input[*i] == '<' || input[*i] == '>')
//	{
//		parsed_input[*i + *j] = ' ';
//		(*j)++;
//		parsed_input[*i + *j] = input[*i];
//		if (input[*i + 1] == '<' || input[*i + 1] == '>')
//		{
//			(*i)++;
//			parsed_input[*i + *j] = input[*i];
//		}
//		(*j)++;
//		parsed_input[*i + *j] = ' ';
//	}
//    if (input[*i] == '|')
//	{
//		parsed_input[*i + *j] = ' ';
//		parsed_input[*i + *j + 1] = '|';
//		*j += 2;
//		parsed_input[*i + *j] = ' ';
//	}
//}

//char **split_input_to_tokens(char *input)
//{
//    char **table_of_tokens;
//    char *parsed_input;
//    int i;
//    int j;

//    i = -1;
//    j = 0;
//    parsed_input = safe_malloc(len_of_input(input) + 1);
//    while(input[++i])
//    {
//        if(input[i] == '|' || input[i] == '>' || input[i] == '<')
//        {
//            add_spaces(input, parsed_input, &i, &j);
//			continue ;
//        }
//        parsed_input[i + j] = input[i];
//    }
//    parsed_input[i + j] = 0;
//    table_of_tokens = ft_split(parsed_input, ' ');
//	free(parsed_input);
//	free(input);
//	return (table_of_tokens);
//}

//t_token	*token_list(char **tab_of_tokens)
//{
//	t_token *head = NULL;
//	t_token *cur = NULL;
//	t_token *last_node;
//	int	i;

//	i = -1;
//	while (tab_of_tokens[++i])
//	{
//		cur = (t_token *)ft_calloc(1, sizeof(t_token));
//		if (!cur)
//			return (NULL);
//		cur->type = type_def(tab_of_tokens[i]);
//		cur->value = ft_strdup(tab_of_tokens[i]);
//		cur->next = NULL;
//		if (!head)
//			head = cur;
//		else
//		{
//			last_node = find_last(head, offsetof(t_token, next));
//			last_node->next = cur;
//		}
//	}
//	free_arr(tab_of_tokens);
//	return (head);
//}

//t_token_type	type_def(char *token)
//{
//	int	i;

//	i = 0;
//	if (!token)
//		return (-1);
//	if (token[i] == '|')
//		return (TOKEN_PIPE);
//	else if (token[i] == '>')
//		return (TOKEN_REDIRECT_OUT);
//	else if (token[i] == '<')
//		return (TOKEN_REDIRECT_IN);
//	else if (token[i] == '>' && token[i + 1] == '>')
//		return (TOKEN_REDIRECT_APPEND);
//	else if (token[i] == '<')
//		return (TOKEN_HEREDOC);
//	else
//		return (TOKEN_WORD);
	
//}

t_token	*lexer(char *input, t_shell *shell)
{
	t_token *list;
	t_token *curr;
	int	i;

	list = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == ' ' || input[i] == '\t')
		{	
			i++;
			continue;
		}
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			curr = append_operator(input, &i);
		//else if (input[i] == '\'' || input[i] == '\"')		TODO
		//	curr = expand_quotes();								TODO
		else
			curr = append_word(input, &i, shell);
		if (!curr)
			return (NULL);
		append_to_list(&list, curr);
	}
	return (list);
}

void	append_to_list(t_token **head, t_token *new_token)
{
	t_token *last;

	if (!*head)
		*head = new_token;
	else
	{
		last = find_last(*head, offsetof(t_token, next));
		last->next = new_token;
	}
}