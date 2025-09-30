/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochmurzy <ochmurzy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:47:23 by ochmurzy          #+#    #+#             */
/*   Updated: 2025/09/25 18:59:49 by ochmurzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_env	*find_env(t_env *env, const char *key)
{
	while (env)
	{
		if (env->key && (ft_strcmp(env->key, key) == 0))
			return (env);
		env = env->next;
	}
	return (NULL);
}
void	update_env_val(t_env **env, const char *key, const char *new_val)
{
	t_env *node;

	if (!env)
		return ;
	node = find_env(*env, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(new_val);
	}
	else if(!node)
		add_new_env(env, key, new_val);
}

t_env	*add_new_env(t_env **env, const char *key, const char *val)
{
	t_env	*new;
	t_env	*last;
	
	if (!env)
		return (NULL);
	new = (t_env *)ft_calloc(1, sizeof(t_env));
	last = find_last(*env, offsetof(t_env, next));
	new->key = ft_strdup(key);
	if (val)
		new->value = ft_strdup(val);
	else
		new->value = NULL;
	last->next = new;
	new->next = NULL;
	return (new);
}

void	sort_env(t_env **list, int n)
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
			if (ft_strcmp(list[i]->key, list[j]->key) > 0)
			{
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
			j++;
		}
	}
}

int	env_len(t_env *list)
{
	int	i;

	i = -1;
	if (!list)
		return (0);
	while (list && ++i)
		list = list->next;
	return (i);
}