/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokon <mokon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:30:45 by mokon             #+#    #+#             */
/*   Updated: 2025/10/22 12:30:45 by mokon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argv;
	if (argc != 1)
		return (1);
	if (!env)
		error_exit("Error: wrong env value!\n");
	shell = safe_malloc(sizeof(t_shell));
	value_init(shell);
	create_list_env(&shell->env, env);
	read_input(shell);
	free_env_list(shell->env);
	free(shell);
	return (0);
}
