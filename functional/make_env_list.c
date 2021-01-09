#include "processing.h"

void        make_env_list(t_data *data, const char **env)
{
    t_env      *list;
    char    **env_split;
    int     i = 0;
    env_split = NULL;
    list = NULL;
    while (env[i])
    {
        env_split = ft_split(env[i], '=');
        if (!ft_strncmp("OLDPWD", env_split[0], 7))
        {
            if (env_split[1] != NULL)
                free(env_split[1]);
            env_split[1] = NULL;
        }
        if (env_split[1] == NULL)
            ft_lstadd_back_env(&list, ft_lstnew_env(ft_strdup(env_split[0]), NULL));
        else
            ft_lstadd_back_env(&list, ft_lstnew_env(ft_strdup(env_split[0]), ft_strdup(env_split[1])));
        free_arr(env_split);
        i++;
    }
    data->env_list = list;
}

