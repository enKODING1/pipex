/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:11:41 by skang             #+#    #+#             */
/*   Updated: 2025/03/20 17:38:01 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "get_next_line.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sched.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <wait.h>

/*memory*/
void	free_matrix(char **matrix);
/*exec utils*/
char	*get_cmd_path(char *cmd, char **envp);
void	exec(char *argv, char **envp);
/*here_doc*/
void	here_doc_put(char *limiter, int fd);
void	here_doc(char *limiter, int fd_handler);
/*error*/
void	error(int *fd);

#endif
