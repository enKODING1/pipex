#include "pipex.h"

void	child_process(int *fd, char **argv, char **envp)
{
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();

	if (pid == 0)
	{
		
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

int main(int argc, char **argv, char **envp)
{
	if(argc >= 5)	
	{
		// if (ft_strncmp(argv[1], "here_doc"))	
		
	}
	return 0;
}
