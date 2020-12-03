#include "minishell.h"

void        check_command(t_data *data, char *ar,  char **env)
{
    char    *output = NULL;
    if (!ft_strncmp("pwd", data->ar[0], 4))
        ft_pwd();
    else if (!ft_strncmp("echo", data->ar[0], 5))
        ft_echo(data);
//    else if (!ft_strncmp("cd", data->ar[0], 3))
//        output = ft_pwd();
    else if (!ft_strncmp("export", data->ar[0], 7))
        ft_export(data);
    else if (!ft_strncmp("unset", data->ar[0], 6))
        ft_unset(data, ar);
    else if (!ft_strncmp("env", data->ar[0], 4))
        ft_env(data);
//    else if (!ft_strncmp("exit", data->ar[0], 5))
//        output = ft_pwd();
//    else
//        ft_exec(data, path, data->ar[0]r, env);
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
