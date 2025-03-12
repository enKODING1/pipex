#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <wait.h>
#include <fcntl.h>

int main(int argc, char* argv[], char **envp) {
    int fd[2];
    int pid;

    pipe(fd);
    pid = fork();

    if(pid == 0)
    {
        int infile_fd;
        char *arg[] = {
            NULL
        };
        infile_fd = open(argv[1], O_RDONLY, 0777);
        dup2(fd[1], STDOUT_FILENO);
        dup2(infile_fd, STDIN_FILENO);
        close(fd[0]);  
        execve(argv[2], arg, envp);
        exit(1);
    }

    waitpid(pid, NULL, 0);
    int outfile_fd;
    char *arg[] = {
            NULL
        };
    outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    dup2(fd[0], STDIN_FILENO);
    dup2(outfile_fd, STDOUT_FILENO);
    close(fd[1]);
    execve(argv[3], arg, envp);
    return 0;
}
