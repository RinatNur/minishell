#include "processing.h"
int 	check_is_PATH(t_env *list)
{
	int 	i;

	i = 0;
	while (list->prev)
		list = list->prev;
	while (list)
	{
		if (!(ft_strncmp("PATH", list->key, 5)))
			return (1);
		list = list->next;
	}
	return (0);
}

void    ft_env(t_data *data)
{
    t_env      *env;

    env = data->env_list;
	if (data->ar[1] != NULL || !(check_is_PATH(data->env_list)))
	{
		ft_error_print(MSHELL, data->ar[0], data->ar[1], ERR1);
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
        if (env->value)
            ft_write(1, "\n");
        env = env->next;
    }
}

