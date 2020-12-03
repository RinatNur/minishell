#include "minishell.h"


int     main(int ac, char **av, char **envp) {
    t_data      data;
    t_env_list  *list;
    t_env_list  *sort_l;
    t_sort_env  sort_env;
    char        *pwd;
    int         pid;
    int         size_of_env;
    char        **env;
    int         i = 0, j;
    char        *path;
    char        *command = "export";
    char*        arr[] = { command, "test", "ok",  NULL };

    list = NULL;
    data.ar = arr;
    data.cmd = command;
    env = env_copy(&data, (const char **)envp);
    make_env_list(&data, (const char **)env);
    check_command(&data, command, env);

    command = "export";
    data.ar[0] = command;
    data.ar[1] = NULL;
    check_command(&data, command, env);

    command = "unset";
    data.ar[0] = command;
    data.ar[1] = "test";
    data.ar[2] = NULL;
    check_command(&data, data.ar[1], env);

    write(1, "\n\n\n", 3);
    command = "export";
    data.ar[0] = command;
    data.ar[1] = NULL;
    check_command(&data, command, env);
    return(0);
}