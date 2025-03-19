#include "pipex.h"

//  $> < file1 cmd1 | cmd2 > file2 의 결과를 동일하게 만들어야 한다.

// < file1 cmd1 | 의 과정을 구현
// void child_process(int *fd, char **argv, char **envp)
// {
//     int infile_fd;
//     infile_fd = open(argv[1], O_RDONLY, 0777);
//     // 스트림 흐름제어
//     dup2(fd[1], STDOUT_FILENO); // 모든 출력은 pipe로
//     dup2(infile_fd, STDIN_FILENO); // 읽기는 입력으로
//     close(fd[0]); //     exec(argv, envp); //     close(infile_fd);
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


char *get_cmd_path(char *cmd, char **envp)
{
    char **path_list;
    char *result;
    int access_ok;
    int i;

    i = 0;
    path_list = NULL;
    result = NULL;
    while(ft_strncmp(envp[i], "PATH=", 5))
        i++;
    path_list = ft_split(envp[i] + 5, ':');
    i = 0;
    while(path_list[i])
    {
        result = ft_strjoin(path_list[i], cmd);
        access_ok = access(result, X_OK);
        if (access_ok == 0)
            break;
        free(result);
        i++;
    }
    free_matrix(path_list);
    if (access_ok == 0)
        return result;
    return NULL;
}

void exec(char *argv, char **envp)
{
    char *cmd_suffix;
    char *cmd;
    char **args;
    
    args = ft_split(argv, ' ');

    cmd_suffix = ft_strjoin("/", args[0]);
    cmd = get_cmd_path(cmd_suffix, envp);
    execve(cmd, args, envp);
    free(cmd_suffix);
    free_matrix(args);
}

// 제출시 makefile 의 CC, CFLAG 원복 해놓기
int main(int argc, char **argv, char **envp)
{
    exec(argv[2], envp);
    return 0; 
}

// 인자값, 에러 처리등은 아직 하지 않음.
// int main(int argc, char* argv[], char **envp) {
//     // int fd[2];
//     // int pid;

//     // if (argc == 5)
//     // {
//     //     pipe(fd);
//     //     pid = fork();

//     //     if(pid == 0)
//     //       child_process(fd, argv, envp);
//     //     waitpid(pid, NULL, 0);
//     //     parent_process(fd, argv,envp);
//     //     return 0;
//     // }

//     // printf("arguments error\n"); 
//     return 0;
// }