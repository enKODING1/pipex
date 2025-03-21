/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:43:36 by skang             #+#    #+#             */
/*   Updated: 2025/03/20 18:10:23 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(char *argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec(argv, envp);
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

static int	run_here_doc(char *file, char *limiter)
{
	int	outfile;

	outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (outfile == -1)
		error();
	here_doc(limiter);
	return (outfile);
}

static int	run_multi_pipe(char *infile, char *outfile)
{
	int	infile_fd;
	int	outfile_fd;

	infile_fd = open(infile, O_RDONLY, 0777);
	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (infile_fd == -1 || outfile_fd == -1)
		error();
	dup2(infile_fd, STDIN_FILENO);
	return (outfile_fd);
}

int	main(int argc, char **argv, char **envp)
{
	int	outfile;
	int	i;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			outfile = run_here_doc(argv[argc - 1], argv[2]);
		}
		else
		{
			i = 2;
			outfile = run_multi_pipe(argv[1], argv[argc - 1]);
		}
		while (i < argc - 2)
		{
			child_process(argv[i], envp);
			i++;
		}
		dup2(outfile, STDOUT_FILENO);
		exec(argv[i], envp);
	}
	ft_putstr_fd("arguments error\n", 2);
	return (0);
}
