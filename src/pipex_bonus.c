#include "pipex.h"

void	child_process(char *argv, char **envp)
{
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();

	if (pid < 0)
		exit(0);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exec(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int main(int argc, char **argv, char **envp)
{
	int infile;
	int outfile;
	int i;

	if(argc >= 5)	
	{
		// if (ft_strncmp(argv[1], "here_doc"))	
		infile = open(argv[1], O_RDONLY, 0777);	
		outfile = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(infile, STDIN_FILENO);
		i = 2;
	}

	while (i < argc - 2)
	{
		child_process(argv[i], envp);	
		i++;
	}
	dup2(outfile, STDOUT_FILENO);
	exec(argv[i], envp);
	return 0;
}
