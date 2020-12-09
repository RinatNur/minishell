#include "minishell.h"

char    *get_value_from_env(t_data *data, char *key)
{
	t_list		*head;

	head = data->env_list;
    while (head)
    {
        if (!ft_strncmp(head->key, key, (ft_strlen(head->key) + 1)))
		{
//        	ft_write(1, head->value);
//        	write(1, "\n", 1);
//			head = head;
            return (head->value);
		}
        head = head->next;
    }
//    head = head;
    return (0);
}
