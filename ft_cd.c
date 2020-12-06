#include "minishell.h"

void    ft_cd(t_data *data)
{
    t_list      *list;
	t_list      *list2;
    char            *tmp;
    int             flag = 0;

    list = data->env_list;
    list2 = data->env_list;
    if (data->ar[1])
        (chdir(data->ar[1]) == -1) ? ft_error("Chdir can't change the directory", 5) : 0;
    while (list)
    {
        if ((!ft_strncmp("PWD", list->key, 4)))
        {
            tmp = list->value;
            list->value = data->ar[1];
            while(list2)
			{
				if ((!ft_strncmp("OLDPWD", list->key, 7)))
				{
					list->key = tmp;
					flag++;
					break ;
				}
				list2 = list2->next;
			}
        }
        if (!flag && !list->next)
		{
            ft_lstadd_back(&data->env_list, ft_lstnew("OLDPWD", tmp));
        	break ;
		}
        list = list->next;
    }
    print_list(data->env_list);
}

