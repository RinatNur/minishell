#include "minishell.h"

void    ft_env(char **env, int env_len)
{
    int i = 0;

    while (i < env_len)
    {
        write(1, env[i], ft_strlen(env[i]));
        if (i < (env_len - 1))
            write(1, "\n", 1);
        i++;
    }
}

