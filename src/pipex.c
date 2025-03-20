/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:11:29 by skang             #+#    #+#             */
/*   Updated: 2025/03/20 15:44:26 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int *fd, char **argv, char **envp)
{
	int	infile_fd;

	infile_fd = open(argv[1], O_RDONLY, 0777);
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
	close(fd[0]);
	close(infile_fd);
	exec(argv[2], envp);
	exit(0);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	int	outfile_fd;

	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(fd[1]);
	exec(argv[3], envp);
	close(outfile_fd);
	exit(0);
}

int	main(int argc, char *argv[], char **envp)
{
	int	fd[2];
	int	pid;

	if (argc == 5)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
			child_process(fd, argv, envp);
		waitpid(pid, NULL, 0);
		parent_process(fd, argv, envp);
		return (0);
	}
	perror("arguments error\n");
	return (0);
}
