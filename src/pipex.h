# ifndef PIPEX_H
# define PIPEX_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <wait.h>
#include <fcntl.h>
#include "libft.h"

/*memory*/
void free_matrix(char **matrix);
/*exec utils*/
char *get_cmd_path(char *cmd, char **envp);
void exec(char *argv, char **envp);

#endif