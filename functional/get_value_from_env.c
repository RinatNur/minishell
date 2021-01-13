#include "processing.h"

char    *get_value_from_env(t_data *data, char *key)
{
	t_env		*list;

	list = data->env_list;
    while (list)
    {
        if (!ft_strncmp(list->key, key, (ft_strlen(list->key) + 1)))
            return (list->value); // FIXME должна возвращать замаллоченное значение
		list = list->next;
    }
    return (NULL);
}
