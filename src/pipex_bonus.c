/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:43:36 by skang             #+#    #+#             */
/*   Updated: 2025/03/21 16:40:38 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(char *argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error(NULL);
	pid = fork();
	if (pid == -1)
		error(fd);
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

	outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (outfile == -1)
		error(NULL);
	here_doc(limiter, outfile);
	return (outfile);
}

static int	run_multi_pipe(char *infile, char *outfile)
{
	int	infile_fd;
	int	outfile_fd;

	infile_fd = open(infile, O_RDONLY);
	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (infile_fd == -1)
	{
		close(outfile_fd);
		error(NULL);
	}
	if (outfile_fd == -1)
	{
		close(infile_fd);
		error(NULL);
	}
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	return (outfile_fd);
}

static int	validate_arguments(int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc != 6)
		{
			ft_putstr_fd("Error\n", 2);
			return (0);
		}
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int	outfile;
	int	i;

	if (!validate_arguments(argc, argv))
		return (0);
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
	close(outfile);
	exec(argv[i], envp);
	return (0);
}
