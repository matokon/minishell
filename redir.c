/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochmurzy <ochmurzy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 20:12:50 by ochmurzy          #+#    #+#             */
/*   Updated: 2025/10/09 19:54:10 by ochmurzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	fd_for_redir(t_cmd *redir)
{
	int	fd;
	
	if ('>')
		fd = open(redir->outs[i]->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if ('>>')
		fd = open(redir->outs[i]->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redir->infile[i], O_RDONLY);
	if (fd == -1)
    	perror("error opening file");
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
