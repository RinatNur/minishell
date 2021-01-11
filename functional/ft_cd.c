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
    t_env		*list;
	t_env		*list2;
    char		*tmp;
	char		*pwd_tmp = NULL;
    int			flag = 0;


	list = data->env_list;
    list2 = data->env_list;
    if (!ft_strncmp("CD", data->ar[0], 3))
    	return;
	if (!data->ar[1])
	{
		free(data->ar[0]);
		free(data->ar);
		data->ar = malloc(sizeof(char *) * 3);
		data->ar[0] = ft_strdup("cd");
		data->ar[1] = get_value_from_env(data, "HOME");
		data->ar[2] = NULL;
	}
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
			(ft_strncmp("..", list->value, 3)) ? (pwd_tmp = get_pwd()) : 0;// if data.ar[1] = ".." find valid path
			tmp = list->value;
			list->value = pwd_tmp ? pwd_tmp : data->ar[1];// if data.ar[1] = ".." change it to valid path
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

