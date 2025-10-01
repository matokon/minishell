/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochmurzy <ochmurzy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 21:30:40 by ochmurzy          #+#    #+#             */
/*   Updated: 2025/10/01 19:06:09 by ochmurzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
//TO DO

//static void	expand_hrdc()
//{
//	t_heredoc *new_hrdc;

//	if (/*jesli jest w pojedynczysz cudzyslowach*/)
//		new_hrdc[command->heredoc_cnt].expand = 0;
//	else if (/*jesli jest w "" cudzyslowach*/)
//		new_hrdc[command->heredoc_cnt].expand = 1;
//}

static int	handle_status(int status, char *path)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(path);
		return (130);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (WEXITSTATUS(status));
	return (0);
}

static int	hrdc_path(char **new_path)
{
	static int	i = 0;
	char	*path;
	char	*num;
	int		fd;

	num = ft_itoa(i++);
	path =ft_strjoin("/tmp/.hrdc_", num);
	if (!path)
		return (-1);
	free(num);
	fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0600);
	if (fd >= 0)
	{
		*new_path = path;
		free(path);
		return (fd); 
	}
	else
	{	
		free(path);
		return (-1);
	}
}

int	read_stdin(const t_heredoc *hd)
{
	int fd;

	fd = open(hd->tmp_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	read_to_file(t_heredoc *new_hrdc)
{
	int	fd;
	pid_t	pid;
	int     status;
	
	fd = hrdc_path(&new_hrdc->tmp_path);
	if (fd < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
//		expand_hrdc();
		add_to_file(new_hrdc, fd);
	}
	close(fd);
	if (waitpid(pid, &status, 0) < 0)
		return (-1);
	return (handle_status(status, new_hrdc->tmp_path));
}

void	add_to_file(t_heredoc *new_hrdc, int fd)
{
	char	*line;
	size_t	len;
	while (1)
	{
		line = readline(">");
		if (!line || ft_strncmp(line, new_hrdc->delim, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		len = ft_strlen(line);
		if (write(fd, line, len) != (ssize_t)len || write(fd, "\n", 1) != 1)
		{
			close(fd);
			free(line);
			error_exit("heredock failure\n");
		}
		free(line);
	}
	exit(0);
}

void	add_heredoc(t_cmd *command, t_token *delim)
{
	t_heredoc *new_hrdc;

	if (!delim || !delim->next || !delim->next->value)
	return ;
	new_hrdc = (t_heredoc *)malloc(sizeof(t_heredoc) * (command->heredoc_cnt + 1));
	if (!new_hrdc)
		return ;
	if (command->heredoc_cnt > 0)
		ft_memcpy(new_hrdc, command->heredocs, sizeof(t_heredoc) * command->heredoc_cnt);
	new_hrdc[command->heredoc_cnt].delim = ft_strdup(delim->next->value);
	read_to_file(new_hrdc);
	command->heredocs = new_hrdc;
	command->heredoc_cnt++;
}
