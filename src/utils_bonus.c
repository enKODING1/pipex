/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:10:27 by skang             #+#    #+#             */
/*   Updated: 2025/03/20 18:10:29 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_put(char *limiter, int fd)
{
	char	*str;

	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 0);
		str = get_next_line(0);
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
			exit(0);
		ft_putstr_fd(str, fd);
		free(str);
	}
}

void	here_doc(char *limiter, char **envp)
{
	int		fd[2];
	int		pid;
	char	*str;

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		here_doc_put(limiter, fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
