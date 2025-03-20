/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:30:33 by skang             #+#    #+#             */
/*   Updated: 2024/12/15 21:38:55 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

size_t	gnl_strlcpy(char *dest, const char *src, size_t n);
size_t	gnl_strlen(const char *s);
char	*gnl_strcat(char *dest, char *src);
char	*gnl_strdup(const char *s);
char	*gnl_strchr(const char *s, int c);
#endif
