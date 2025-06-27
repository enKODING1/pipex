/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:11:29 by skang             #+#    #+#             */
/*   Updated: 2025/06/27 23:00:40 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_input_process(int *fd, char **argv, char **envp)
{
	int	infile_fd;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
		error(fd);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	exec(argv[2], envp);
	exit(0);
}

static void	child_output_process(int *fd, char **argv, char **envp)
{
	int	outfile_fd;

	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile_fd == -1)
		error(fd);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	exec(argv[3], envp);
	exit(0);
}

static void	pipex(char **argv, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	pid1 = -1;
	pid2 = -1;
	if (pipe(fd) == -1)
		error(NULL);
	pid1 = fork();
	if (pid1 == -1)
		error(fd);
	if (pid1 == 0)
		child_input_process(fd, argv, envp);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			error(fd);
		if (pid2 == 0)
			child_output_process(fd, argv, envp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
	{
		pipex(argv, envp);
	}
	else
	{
		ft_putstr_fd("Error: Invalid arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
