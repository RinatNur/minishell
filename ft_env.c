#include "minishell.h"

void    ft_env(t_data *data)
{
    int i = 0;
    t_env_list      *env = data->env_list;

    while (env)
    {
        if(env->value)
        {
            ft_write(1, env->key);
            ft_write(1, "=");
            ft_write(1, env->value);
        }
        if (env->next)
            write(1, "\n", 1);
        env = env->next;
    }
}

