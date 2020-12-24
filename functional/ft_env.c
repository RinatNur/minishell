#include "processing.h"

void    ft_env(t_data *data)
{
    int i = 0;
    t_env      *env = data->env_list;

	if (data->ar[1] != NULL)
	{
		ft_error_print(MSHELL, data->ar[0], data->ar[1], "No such file or directory");
		return;
	}
    while (env)
    {
        if(env->value)
        {
            ft_write(1, env->key);
            ft_write(1, "=");
            ft_write(1, env->value);
        }
        if (env->next && env->value)
            write(1, "\n", 1);
        env = env->next;
    }
    ft_write(1, "\n");
}

