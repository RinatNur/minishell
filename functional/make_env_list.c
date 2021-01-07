#include "processing.h"

void 	free_env_list(t_env *list)
{
	while (list->prev)
		list = list->prev;
	while (list)
	{
		free(list->key);
		list->key = NULL;
		free(list->value);
		list->value = NULL;
		list = list->next;
	}
	free(list);
	list = NULL;
}

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
		ft_lstadd_back_env(&list, ft_lstnew_env(env_split[0], env_split[1]));
        i++;
//        free_arr(env_split);
    }
	ft_lstadd_back_env(&list, ft_lstnew_env("OLDPWD", NULL));
    data->env_list = list;
//    free(env_split[0]);
//    free(env_split[1]);
//    free(env_split);
//    print_list(data->env_list);
}

