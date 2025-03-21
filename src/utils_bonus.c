/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:10:27 by skang             #+#    #+#             */
/*   Updated: 2025/03/21 15:48:25 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	gnl_read_eof(void)
{
	int		null_fd;
	int		old_stdin;
	char	*tmp;

	null_fd = open("/dev/null", O_RDONLY);
	if (null_fd != -1)
	{
		old_stdin = dup(0);
		dup2(null_fd, 0);
		close(null_fd);
		tmp = get_next_line(0);
		if (tmp)
			free(tmp);
		dup2(old_stdin, 0);
		close(old_stdin);
	}
}

static void	here_doc_put(char *limiter, int fd)
{
	char	*str;
	int		diff;

	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 0);
		str = get_next_line(0);
		diff = ft_strncmp(str, limiter, ft_strlen(limiter));
		if (diff == 0 && ft_strlen(str) == ft_strlen(limiter) + 1)
		{
			free(str);
			close(fd);
			gnl_read_eof();
			return ;
		}
		ft_putstr_fd(str, fd);
		free(str);
	}
}

void	here_doc(char *limiter, int fd_handler)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		error(NULL);
	pid = fork();
	if (pid == -1)
		error(NULL);
	if (pid == 0)
	{
		close(fd[0]);
		here_doc_put(limiter, fd[1]);
		close(fd[1]);
		close(fd_handler);
		exit(0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}
