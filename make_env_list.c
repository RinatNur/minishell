#include "minishell.h"

char      **env_copy(t_data *data, const char **envp)
{
    char    **env;
    int     i = 0;

    while (envp[i])
        i++;
    data->env_len = i;
    env = (char **)malloc((i + 1) * sizeof(char **));
    i = 0;
    while (envp[i])
    {
        env[i] = envp[i];
        i++;
    }
    env[i] = NULL;
    data->env = env;
    return (env);
}

void        make_env_list(t_data *data, const char **env)
{
    t_env_list      *list;
    char    **env_split;
    int     i = 0;

    list = NULL;
    while (env[i])
    {
        env_split = ft_split(env[i], '=');
        ft_lstadd_back_dbl(&list, ft_lstnew_dbl(env_split[0], env_split[1]));
        free(env_split);
        i++;
    }
    data->env_list = list;
//    return (list);
}

