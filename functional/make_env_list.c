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
		ft_lstadd_back_env(&list, ft_lstnew_env(ft_strdup(env_split[0]), ft_strdup(env_split[1])));
		free_arr(env_split);
        i++;
    }
	ft_lstadd_back_env(&list, ft_lstnew_env("OLDPWD", NULL));
    data->env_list = list;
}

