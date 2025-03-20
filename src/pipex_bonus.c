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

void	here_doc(char *limiter, char **envp)
{
	int fd[2];	
	int pid;
	char *str;

	pipe(fd);
	pid = fork();

	if(pid < 0)
		exit(0);

	if(pid == 0)
	{
		close(fd[0]);
		while(1)
		{
			str = get_next_line(0);
			if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)	
			{
				exit(0);
			}
			ft_putstr_fd(str, fd[1]);
			free(str);
		}
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
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)	
		{
			i = 3;
			outfile = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			here_doc(argv[2], envp);
		}
		else
		{
			i = 2;
			infile = open(argv[1], O_RDONLY, 0777);	
			outfile = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			dup2(infile, STDIN_FILENO);
		}
		
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
