#include "minishell.h"

int     main(int ar, char **av, char **env)
{
    int i = 0, j;
    char *pwd;
    char        **env_copy = env;
    while (env_copy[i])
        i++;
    int size_of_env = i;
    int pid = fork();
    if (pid == -1)
        return (1);
    i = 0;
    pwd = ft_pwd();
    int file = open("../test", O_WRONLY | O_CREAT, 0777);
    dup2(file, STDOUT_FILENO);
//    printf("%s", pwd);
//    ft_env(env_copy, size_of_env);
    write(1, "HELLO\n", 6);
    if(pid == 0)
    {
        int err = execlp("ls", "ls", "-la", NULL);
        if (err == -1)
            return (err);
//            printf("FAILURE\n");

    }
    else
    {
        int     wait_status = 0;
        wait (&wait_status);
        if (WIFEXITED(wait_status))
        {
            int status_code = WEXITSTATUS(wait_status);
//            if (status_code == 0)
////                printf("sucess");
//            else
//                printf("failure with the status code %d\n", status_code);
        }
//        printf("SUCSESS");
    }

}
