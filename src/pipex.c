// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <sched.h>
// #include <wait.h>
// #include <fcntl.h>

// int get_cmd_path(char *cmd, char **envp)
// {
    
// }

// void exec(char **argv, char **envp)
// {
//     char *cmd;
//     get_cmd_path(cmd, envp);
//     // execve(cmd, args, envp);

// }

// //  $> < file1 cmd1 | cmd2 > file2 의 결과를 동일하게 만들어야 한다.

// // < file1 cmd1 | 의 과정을 구현
// void child_process(int *fd, char **argv, char **envp)
// {
//     int infile_fd;
//     infile_fd = open(argv[1], O_RDONLY, 0777);
//     // 스트림 흐름제어
//     dup2(fd[1], STDOUT_FILENO); // 모든 출력은 pipe로
//     dup2(infile_fd, STDIN_FILENO); // 읽기는 입력으로
//     close(fd[0]);
//     exec(argv, envp);
//     close(infile_fd);
//     exit(0);
// }
// // | cmd2 > file2 의 과정을 구현
// void parent_process(int *fd, char **argv, char **envp)
// {
//     int outfile_fd;
//     outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
//     // 스트림 흐름제어
//     dup2(fd[0], STDIN_FILENO); // 모든 입력은 pipe로
//     dup2(outfile_fd, STDOUT_FILENO); // 쓰기는 출력으로  
//     close(fd[1]);
//     exec(argv, envp);
//     close(outfile_fd);
//     exit(0);
// }

// // 인자값, 에러 처리등은 아직 하지 않음.
// int main(int argc, char* argv[], char **envp) {
//     int fd[2];
//     int pid;

//     if (argc == 5)
//     {
//         pipe(fd);
//         pid = fork();

//         if(pid == 0)
//           child_process(fd, argv, envp);
//         waitpid(pid, NULL, 0);
//         parent_process(fd, argv,envp);
//         return 0;
//     }

//     printf("arguments error\n"); 
//     return 0;
// }

#include "libft.h"

int main(void)
{
    ft_putstr_fd("hello", 1);
    // printf("helloworld");
    return 0;
}