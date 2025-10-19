#include "mini.h"

//static char	*get_var_name(char *s)
//{
//	int	i;

//	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
//		return (NULL);
//	i = 0;
//	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
//		i++;
//	return (ft_substr(s, 0, i));
//}

//static void	handle_dollar(char **input, int i, t_shell *shell)
//{
//	char	*expanded;
//	char	*var_name;

//	if ((*input)[i + 1] == '?')
//	{
//		expanded = ft_itoa(shell->last_status);
//		*input = ft_replace(*input, "$?", expanded, i);
//		free(expanded);
//		return ;
//	}
//	var_name = get_var_name(*input + i + 1); // à implémenter : récupère "USER" depuis "$USER"
//	expanded = get_var_value(var_name, shell); // à implémenter : getenv-like
//	*input = ft_replace(*input, ft_strjoin("$", var_name), expanded ? expanded : "", i);
//	free(var_name);
//}

//static void	if_question_mark(char **input, int i, t_shell shell)
//{
//	char	*itoa;
//	//char	*tmp;

//	if ((*input)[i + 1] == '?')
//	{
//		itoa = ft_itoa(shell.last_status);
//		*input = ft_replace(*input, "$?", itoa, i);
//		free(itoa);
//		return ;
//	}
//}

//char	*deal_with_quotes(char *input, t_shell shell)
//{
//	char	type_of_quote;
//	int		i;
//	int		j;

//	i = 0;
//	while (input[i] && (ft_strchr(input, '"') || ft_strchr(input, '\'')))
//	{
//		i = find_first_quote(input, i);
//		if (i == -1)
//			break ;
//		type_of_quote = input[i];
//		j = find_second_quote(input, i + 1, type_of_quote);
//		if (j == -1)
//			return (printf("Error: Unmatched quote\n"), NULL);
//		i++;
//		while (i <= j && input[i])
//		{
//			if (type_of_quote != '\'' && input[i] == '$')
//			{
//				if_question_mark(&input, i, shell);
//				j = find_second_quote(input, i + 1, type_of_quote);
//			}
//			else if (type_of_quote == '\'')
//			{
//			}
//			else
//				i++;
//		}
//		i = j + 1;
//	}
//	return (input);
//}
//////////////////////////////////////////////////

//static char	*expand_env_vars(char *str, t_shell shell)
//{
//	int		i;
//	char	*result;
//	char	*var_name;
//	char	*var_value;

//	i = 0;
//	result = ft_strdup("");
//	if (!result)
//		return (NULL);
//	while (str[i])
//	{
//		if (str[i] == '$' && str[i + 1])
//		{
//			if (str[i + 1] == '?')
//			{
//				var_value = ft_itoa(shell.last_status);
//				i += 2;
//			}
//			else
//			{
//				var_name = get_var_name(str + i + 1);
//				var_value = ft_strdup(get_var_value(var_name, &shell));
//				free(var_name);
//				i += ft_strlen(var_name) + 1;
//			}
//			result = join_free(&result, var_value);
//			free(var_value);
//		}
//		else
//			result = join_char(&result, str[i++]);
//	}
//	free(str);
//	return (result);
//}
//static char	*replace_segment(char *input, int start, int end, char *middle)
//{
//	char	*before;
//	char	*after;
//	char	*tmp;
//	char	*new_input;

//	before = ft_substr(input, 0, start);
//	if (!before)
//		return (NULL);
//	after = ft_strdup(input + end + 1);
//	if (!after)
//		return (free(before), NULL);
//	tmp = ft_strjoin(before, middle);
//	if (!tmp)
//		return (free(before), free(after), NULL);
//	new_input = ft_strjoin(tmp, after);
//	free(before);
//	free(after);
//	free(tmp);
//	free(middle);
//	free(input);
//	return (new_input);
//}

//char	*deal_with_quotes(char *input, t_shell shell)
//{
//	char	type_of_quote;
//	int		i;
//	int		j;

//	i = 0;
//	while (input[i])
//	{
//		i = find_first_quote(input, i);
//		if (i == -1)
//			break;
//		type_of_quote = input[i];
//		j = find_second_quote(input, i + 1, type_of_quote);
//		if (j == -1)
//			return (printf("Error: Unmatched quote\n"), NULL);

//		// Extract the content between quotes
//		char *between = ft_substr(input, i + 1, j - i - 1);

//		if (type_of_quote == '"')
//			between = expand_env_vars(between, shell); // expand $VAR and $?

//		// Replace quoted segment in input by its processed version
//		input = replace_segment(input, i, j, between);

//		i += ft_strlen(between); // move past the new inserted segment
//	}
//	return (input);
//}

static char	*remove_quotes(char *s, int start, int end)
{
	int		len_src;
	int		len_new;
	char	*out;
	int		len_mid;

	len_src = ft_strlen(s);
	len_mid = end - start - 1;
	if (len_mid < 0)
		return (ft_strdup(s));
	len_new = len_src - 2;
	out = safe_malloc(len_new + 1);
	if (start > 0)
		ft_memcpy(out, s, start);
	if (len_mid > 0)
		ft_memcpy(out + start, s + start + 1, len_mid);
	if (s[end + 1])
		ft_memcpy(out + start + len_mid, s + end + 1,
			len_src - (end + 1));
	out[len_new] = '\0';
	return (out);
}

//static int	find_first_quote(char *input, int i)
//{
//	while (input[i])
//	{
//		if (input[i] == '"' || input[i] == '\'')
//			return (i);
//		i++;
//	}
//	return (-1);
//}

//static int	find_second_quote(char *input, int i, char type_of_quote)
//{
//	while (input[i])
//	{
//		if (input[i] == type_of_quote)
//			return (i);
//		i++;
//	}
//	return (-1);
//}

static char	*ft_replace(char *s, char *var, char *val, int pos)
{
	int	s_len;
	int	var_len;

	if (!s || !var || !val)
		return (NULL);
	s_len = ft_strlen(s);
	var_len = ft_strlen(var);
	if (pos < 0 || pos >= s_len)
		return (ft_strdup(s));
	if (ft_strncmp(s + pos, var, var_len) != 0)
		return (ft_strdup(s));
	return (handle_replacement(s, val, pos, var_len));
}

static void	if_question_mark(char **input, int i, t_shell shell)
{
	char	*itoa;

	itoa = ft_itoa(shell.last_status);
	if ((*input)[i + 1] == '?')
		*input = ft_replace(*input, "$?", itoa, i);
	free(itoa);
}

//char *deal_with_quotes(char *input, t_shell shell)
//{
//	char type_of_quote;
//	int i; 
//	int j;
//	i = 0;
//	while (input[i] && (ft_strchr(input, '"') || ft_strchr(input, '\'')))
//	{
//		i = find_first_quote(input, i);
//		if (i == -1)
//			break ;
//		type_of_quote = input[i];
//		j = find_second_quote(input, i + 1, type_of_quote);
//		if (j == -1)
//			return (printf("Error: Unmatched quote\n"), NULL);
//		i++;
//		while (i <= j && input[i])
//		{
//			if (type_of_quote != '\'' && input[i] == '$')
//			{
//				printf("adadas");
//				if_question_mark(&input, i, shell);
//				j = find_second_quote(input, i + 1, type_of_quote);
//			}
//			else if (type_of_quote != '"' && input[i] == '$')
//				input = remove_quotes(input, i, j);
//			i++;
//		}
//		i = j + 1;
//	}
//	return (input);
//}