#include "minishell.h"

char    *get_value_from_env(t_data *data, char *key)
{
    while (data->env_list->next)
    {
        if (!ft_strncmp(data->env_list->key, key, (ft_strlen(data->env_list->key) + 1)))
            return (data->env_list->value);
        data->env_list = data->env_list->next;
    }
    return (0);
}
