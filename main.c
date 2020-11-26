#include "minishell.h"

int     main(int ar, char **av, char **envp)
{
    int i = 0, j;
    char *pwd;
    char   **env_copy;
    int     pid;
    int size_of_env;


    while (envp[i])
        i++;
    env_copy = (char **)malloc((i+1) * sizeof(char **));
//    env_copy = envp;
    i = 0;
    while (envp[i])
    {
        env_copy[i] = envp[i];
        i++;
    }
    env_copy[i] = NULL;
    size_of_env = i;
//    env_copy[i] = NULL;

    char* arr[3];
//    arr[0] = "-e";
//    arr[1] = "Makefile";
//    arr[1] = "-l";
    arr[0] = NULL;
//        write(1, "HELLO\n", 6);
    int err = execve("/bin/sh", arr, NULL);
    if (err == -1)
        {
            printf("FAILURE\n");
            printf("errno = %d\n", errno);
            return (err);
        }

//    pid = fork();
//    if (pid == -1)
//        return (1);
//
//    i = 0;
////    pwd = ft_pwd();
////    int file = open("../test", O_WRONLY | O_CREAT, 0777);
////    dup2(file, STDOUT_FILENO);
////    printf("%s", pwd);
////    ft_env(env_copy, size_of_env);
//    if(pid == 0)
//    {
//        char* arr[] = { NULL };
////        write(1, "HELLO\n", 6);
//        int err = execve("ls", arr, env_copy);
//        if (err == -1)
//        {
//            printf("FAILURE\n");
//            return (err);
//        }
//
//    }
//    else
//    {
//        int     wait_status = 0;
//        wait (&wait_status);
//        if (WIFEXITED(wait_status))
//        {
//            int status_code = WEXITSTATUS(wait_status);
////            if (status_code == 0)
//////                printf("sucess");
////            else
////                printf("failure with the status code %d\n", status_code);
//        }
////        printf("SUCSESS");
//    }

}
