#include "minishell.h"

void        check_command(t_data *data, char *command, char *path, char **arr, char **env)
{
    char    *output = NULL;
    if (!ft_strncmp("pwd", command, 4))
        ft_pwd();
    else if (!ft_strncmp("echo", command, 5))
        ft_echo(data);
//    else if (!ft_strncmp("cd", command, 3))
//        output = ft_pwd();
//    else if (!ft_strncmp("export", command, 7))
//        output = ft_pwd();
//    else if (!ft_strncmp("unset", command, 6))
//        output = ft_pwd();
    else if (!ft_strncmp("env", command, 4))
        ft_env(data);
//    else if (!ft_strncmp("exit", command, 5))
//        output = ft_pwd();
    else
        ft_exec(data, path, arr, env);
//    printf("pwd = %s", output);
}

int    ft_exec(t_data *data, char *path, char **arr, char **env)
{
    int     pid, err;

    pid = fork();
    if (pid == -1)
        return (1);

//    int file = open("../test.c", O_WRONLY | O_CREAT, 0777);
//    dup2(file, STDOUT_FILENO);
//    printf("%s", pwd);
//    ft_env(env_copy, size_of_env);

//    execve in child process test
    if(pid == 0)
    {
        err = execve(path, arr, env);
        if (err == -1)
        {
            printf("FAILURE\n");
            return (err);
        }

    }
    else
    {
        int     wait_status = 0;
        wait (&wait_status);
        if (WIFEXITED(wait_status))
        {
            int status_code = WEXITSTATUS(wait_status);
            if (status_code == 0)
                printf("sucess");
            else
                printf("failure with the status code %d\n", status_code);
        }
     }
    return (0);
}
