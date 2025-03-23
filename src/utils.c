/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:11:34 by skang             #+#    #+#             */
/*   Updated: 2025/03/23 12:29:55 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**path_list;
	char	*result;
	int		access_ok;
	int		i;

	i = 0;
	path_list = NULL;
	result = NULL;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path_list = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_list[i])
	{
		result = ft_strjoin(path_list[i], cmd);
		access_ok = access(result, X_OK);
		if (access_ok == 0)
			break ;
		free(result);
		i++;
	}
	free_matrix(path_list);
	if (access_ok == 0)
		return (result);
	return (NULL);
}

void	exec_cmd(char *cmd, char **args, char **envp, int run_flag)
{
	if (cmd == NULL && run_flag == 0)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("\n", 2);
		free_matrix(args);
		exit(127);
	}
	if (execve(cmd, args, envp) == -1)
	{
		perror("execve");
		free(cmd);
		free_matrix(args);
		exit(126);
	}
}

void	exec_direct(char *argv, char **envp)
{
	char	*cmd_suffix;
	char	*cmd;
	char	**args;
	int		direct_run;

	args = ft_split(argv, ' ');
	direct_run = 1;
	if (ft_strchr(args[0], '/'))
	{
		if (access(args[0], X_OK) == 0)
			cmd = ft_strdup(args[0]);
		else
		{
			cmd = NULL;
			direct_run = 0;
		}
	}
	else
	{
		cmd_suffix = ft_strjoin("/", args[0]);
		cmd = get_cmd_path(cmd_suffix, envp);
		free(cmd_suffix);
		direct_run = 0;
	}
	exec_cmd(cmd, args, envp, direct_run);
}

void	exec(char *argv, char **envp)
{
	if (ft_strchr(argv, '\'') || ft_strchr(argv, '\"'))
	{
		ft_putstr_fd("Command error\n", 2);
		exit(127);
	}	
	else
		exec_direct(argv, envp);
}
