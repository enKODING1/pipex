/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:11:34 by skang             #+#    #+#             */
/*   Updated: 2025/03/20 15:44:35 by skang            ###   ########.fr       */
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

void	exec(char *argv, char **envp)
{
	char	*cmd_suffix;
	char	*cmd;
	char	**args;

	args = ft_split(argv, ' ');
	cmd_suffix = ft_strjoin("/", args[0]);
	cmd = get_cmd_path(cmd_suffix, envp);
	execve(cmd, args, envp);
	free(cmd_suffix);
	free_matrix(args);
}
