#include "processing.h"

void    ft_unset(t_data *data)
{
    t_env      *list;
    int             i = 1;
    size_t          len;

    list = data->env_list;
    while(data->ar[i])
	{
    	len = ft_strlen(data->ar[i]) + 1;
		while (list)
		{
			if (!ft_strncmp(data->ar[i], list->key, len))
			{
				cut_list(data, data->ar[i]);
				break ;
			}
			list = list->next;
		}
		i++;
	}
}

