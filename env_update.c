/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochmurzy <ochmurzy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:47:23 by ochmurzy          #+#    #+#             */
/*   Updated: 2025/08/10 21:30:59 by ochmurzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_env	*find_env(t_env *env, const char *key)
{

	while (env->next != NULL)
	{
		if (env->key && (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0))
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
	else
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
