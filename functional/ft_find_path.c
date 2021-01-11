#include "processing.h"

char    *ft_find_path(t_data *data, char *command)
{
    char    *path;
    DIR     *dir;
    struct  dirent  *tmp;
    char    **path_arr;
    int     i = 0;
    int     flag = 0;

	path = NULL;
	dir = NULL;
	!(path_arr = ft_split(get_value_from_env(data, "PATH"), ':')) ? ft_error_print(MSHELL, data->ar[0], NULL, ERR5) : 0;
	if (!path_arr)
		return (NULL);
    while (path_arr[i])
    {
        dir = opendir(path_arr[i]);
        if (NULL != dir)
        {
            while ((tmp = readdir(dir)) != NULL)
            {
                if (!ft_strncmp(command, tmp->d_name, (ft_strlen(command) + 1)))
                {
                    path = ft_strjoin(ft_strjoin(path_arr[i], "/"), command);
                    flag = 1;
                    break ;
                }

            }
            if (flag == 1)
            {
				if(dir)
					free(dir);
				break;
			}
			i++;
        }
        else
            i++;
    	if(dir)
    		free(dir);
    }
	if (!flag)
		ft_error_print(MSHELL, command, NULL, ERR2);
	free_arr(path_arr);
	if (!path)
		path = "";
	return (path);
}