/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:10:27 by skang             #+#    #+#             */
/*   Updated: 2025/03/21 14:03:39 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_put(char *limiter, int fd)
{
	char	*str;
	int		null_fd;
	char	*tmp;

	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 0);
		str = get_next_line(0);
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
		{
			free(str);
			close(fd);
			// get_next_line의 static 변수 정리를 위한 코드
			null_fd = open("/dev/null", O_RDONLY);
			if (null_fd != -1)
			{
				int old_stdin = dup(0); // 원래 stdin 저장
				dup2(null_fd, 0);       // stdin을 /dev/null로 변경
				close(null_fd);
				// EOF를 읽게 하여 get_next_line의 static 변수 정리 유도
				tmp = get_next_line(0);
				if (tmp)
					free(tmp);
				// 원래 stdin 복원
				dup2(old_stdin, 0);
				close(old_stdin);
			}
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
