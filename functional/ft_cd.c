#include "processing.h"

char 	*get_pwd()
{
	char *dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	return (dir);
}
void    ft_cd(t_data *data)
{
	//TODO check "CD dffdgs" with execve
    t_env      *list;
	t_env      *list2;
    char            *tmp;
    int             flag = 0;
    int 			err;
    char 			*err_text;
	char 			*test;

    list = data->env_list;
    list2 = data->env_list;
    if (!ft_strncmp("CD", data->ar[0], 3))
    	return;
    if (!data->ar[1])
    	data->ar[1] = get_value_from_env(data, "HOME");
    if (data->ar[1])
    {
    	if ((!ft_strncmp("-", data->ar[1], 2)))
    	{
			data->ar[1] = get_value_from_env(data, "OLDPWD");
			ft_write(1, data->ar[1]);
			ft_write(1, "\n");
		}
		(chdir(data->ar[1]) == -1) ? ft_error_print(MSHELL, data->ar[0], data->ar[1], strerror(errno)) : 0;
	}
	while (list)
    {
        if ((!ft_strncmp("PWD", list->key, 4)))
        {
        	(!(ft_strncmp("..", list->value, 3))) ? (list->value = (void *)get_pwd()) : 0;//change ".." to valid path
			tmp = list->value;
            list->value = data->ar[1];
            while(list2)
			{
				if ((!ft_strncmp("OLDPWD", list2->key, 7)))
				{
					list2->value = tmp;
					flag++;
					break ;
				}
				list2 = list2->next;
			}
        }
        list = list->next;
    }
}

