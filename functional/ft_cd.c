#include "processing.h"

void    ft_cd(t_data *data)
{
    t_env      *list;
	t_env      *list2;
    char            *tmp;
    int             flag = 0;
    int 			err;
    char 			*err_text;

    list = data->env_list;
    list2 = data->env_list;
    if (data->ar[1])
        (chdir(data->ar[1]) == -1) ? ft_error_print(MSHELL, data->ar[0], data->ar[1], strerror(errno)) : 0;
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
			ft_lstadd_back_env(&data->env_list, ft_lstnew_env("OLDPWD", tmp));
        	break ;
		}
        list = list->next;
    }
//    print_list(data->env_list);
}

