#include "mini.h"

static int	is_valid_key(const char *s)
{
	int	i;

	if (!s || (!ft_isalpha(*s) && *s != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=' && s[i] != '+')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	if (s[i] == '+' && s[i + 1] != '=')
		return (0);
	return (1);
}

static char	*extract_key(const char *s, int *is_append, int *has_eq)
{
	int		klen;
	char	*key;

	*is_append = 0;
	*has_eq = 0;
	klen = 0;
	while (s[klen] && s[klen] != '=' && s[klen] != '+')
		klen++;
	if (s[klen] == '+')
	{
		*is_append = 1;
		if (s[klen + 1] == '=')
			*has_eq = 1;
	}
	else if (s[klen] == '=')
		*has_eq = 1;
	key = (char *)ft_calloc(klen + 1, 1);
	if (!key)
		return (NULL);
	ft_memcpy(key, s, klen);
	return (key);
}

static int	set_var(t_env **env, const char *key, const char *val, int app)
{
	t_env	*node;
	char	*joined;

	node = find_env(*env, key);
	if (!app)
	{
		if (node)
			update_env_val(env, key, val);
		else
			add_new_env(env, key, val);
		return (0);
	}
	if (!node)
		return (add_new_env(env, key, val), 0);
	if (!node->value)
		return (update_env_val(env, key, val), 0);
	joined = ft_strjoin(node->value, val ? val : "");
	if (!joined)
		return (1);
	update_env_val(env, key, joined);
	free(joined);
	return (0);
}

int	handle_arg(t_shell *sh, const char *arg)
{
	int		app;
	int		has_eq;
	char	*key;
	char	*val;

	if (!is_valid_key(arg))
		return (ft_putstr_fd("minishell: export: `", 2),
			ft_putstr_fd((char *)arg, 2),
			ft_putstr_fd("': not a valid identifier\n", 2), 1);
	key = extract_key(arg, &app, &has_eq);
	if (!key)
		return (1);
	val = NULL;
	if (has_eq)
		val = ft_strchr(arg, '=') + 1;
	if (set_var(&sh->env, key, val, app))
		return (free(key), 1);
	return (free(key), 0);
}

static void	print_escaped(const char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '\"' || s[i] == '\\')
			ft_putchar_fd('\\', 1);
		ft_putchar_fd(s[i], 1);
	}
}

static int	env_len(t_env *e)
{
	int	n;

	n = 0;
	while (e)
		n++, e = e->next;
	return (n);
}

static void	sort_env(t_env **a, int n)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = -1;
	while (++i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp(a[i]->key, a[j]->key) > 0)
				tmp = a[i], a[i] = a[j], a[j] = tmp;
			j++;
		}
	}
}

static void	print_one_export(t_env *e)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(e->key, 1);
	if (e->value)
	{
		ft_putstr_fd("=\"", 1);
		print_escaped(e->value);
		ft_putstr_fd("\"\n", 1);
	}
	else
		ft_putstr_fd("\n", 1);
}

int	print_sorted_export(t_env *env)
{
	int		n;
	int		i;
	t_env	**arr;

	n = env_len(env);
	arr = (t_env **)ft_calloc(n, sizeof(*arr));
	if (!arr)
		return (1);
	i = -1;
	while (++i < n)
		arr[i] = env, env = env->next;
	sort_env(arr, n);
	i = -1;
	while (++i < n)
		print_one_export(arr[i]);
	free(arr);
	return (0);
}


int	ft_export(t_shell *sh, char **argv)
{
	int	i;
	int	code;

	if (!argv || !argv[1])
		return (print_sorted_export(sh->env));
	code = 0;
	i = 0;
	while (argv[++i])
		if (handle_arg(sh, argv[i]) != 0)
			code = 1;
	return (code);
}
