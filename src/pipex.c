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


char *get_cmd_path(char *cmd, char **envp)
{
    char **path;
    char *cmd_path;
    int i;

    i = 0;
    path = NULL;
    cmd_path = NULL;
    while(ft_strncmp(envp[i], "PATH=", 5))
        i++;
    printf("envp[%d]: %s\n", i, envp[i]);
    path = ft_split(envp[i] + 5, ':');
    i = 0;
    while(path[i])
    {
        printf("path[%d]: %s\n", i, path[i]);
        cmd_path = ft_strjoin(path[i], cmd);
        printf("cmd: %s\n", cmd_path);
        printf("status: %d\n", access(cmd_path, X_OK));
        if (access(cmd_path, X_OK) == 0)
        {
            return cmd_path;
        }
        printf("\n");
        i++;
    }

    return NULL;
}

void exec(char **argv, char **envp)
{
    char *cmd;
    char *cmd_path;

    
    cmd = ft_strjoin("/", argv[1]);
    cmd_path = get_cmd_path(cmd, envp);
    printf("cmd_path: %s\n", cmd_path);
    // 기대값 : cmd 실행경로가 포함된 명령어 
    /* 과정: envp 에서 PATH부분을 찾은 후, 
       access 함수를 통해 해당 명령어가 실행되는지 확인해가며
       실행가능이라면 해당 경로를 반환해서 cmd에 넣음
    */


    // args도 "cmd arg1 arg2" 형태로 들어온다면 분리해서
    /*
        [
            ["cmd1"],
            ["arg1"],
            ["arg2"] 
        ]
     형태로 변환해야함.
    */ 
    // execve(cmd, args, envp);
}

// 제출시 makefile 의 CC, CFLAG 원복 해놓기
int main(int argc, char **argv, char **envp)
{
    exec(argv, envp);
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