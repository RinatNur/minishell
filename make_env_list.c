#include "minishell.h"

char      **env_copy(t_data *data, const char **envp)
{
    char    **env;
    int     i = 0;
    int     len_str;
    while (envp[i])
        i++;
    env = malloc((i + 1) * sizeof(char *));
    env[i] = NULL;
    i = 0;
    while (envp[i])
    {
        len_str = ft_strlen(envp[i]);
        env[i] = malloc(len_str + 1);
        env[i][len_str] = '\0';
        env[i] = (char *)envp[i];
        i++;
    }
//    data->env = env;
    return (env);
}

void        make_env_list(t_data *data, const char **env)
{
    t_list      *list;
    char    **env_split;
    int     i = 0;

    list = NULL;
    while (env[i])
    {
        env_split = ft_split(env[i], '=');
        ft_lstadd_back(&list, ft_lstnew(env_split[0], env_split[1]));
        free(env_split);
        i++;
    }
    data->env_list = list;
//    return (list);
}

