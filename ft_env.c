#include "minishell.h"

void    ft_env(t_data *data)
{
    int i = 0;
    char    **env = data->env;

    while (i < data->env_len)
    {
        write(1, env[i], ft_strlen(env[i]));
        if (i < (data->env_len - 1))
            write(1, "\n", 1);
        i++;
    }
}

