#include "processing.h"

char    *ft_find_path(t_data *data, char *command)
{
    char    *path;
    DIR     *dir;
    struct  dirent  *tmp;
    char    **path_arr;
    int     i = 0;
    int     flag = 0;
	char	*tmp_str;

	tmp_str = NULL;
	path = NULL;
	dir = NULL;
	path_arr = ft_split(get_value_from_env(data, "PATH"), ':');
	if (!path_arr || !path_arr[0])
	{
		ft_error_print(MSHELL, data->ar[0], NULL, ERR5);
		path = ft_strdup("");
		if (path_arr)
			free_arr(path_arr);
		return (path);
	}
    while (path_arr[i])
    {
        dir = opendir(path_arr[i]);
        if (NULL != dir)
        {
            while ((tmp = readdir(dir)) != NULL)
            {
                if (!ft_strncmp(command, tmp->d_name, (ft_strlen(command) + 1)))
                {
                	tmp_str = ft_strjoin(path_arr[i], "/");
                    path = ft_strjoin(tmp_str, command);
                    if(tmp_str)
                    	free(tmp_str);
                    flag = 1;
                    break ;
                }
            }
            if (flag == 1)
            {
				if (dir)
					(closedir(dir)) ? exit(32) : 0;
				break;
			}
			i++;
        }
        else
            i++;
        if (dir)
        	(closedir(dir)) ? exit(32) : 0;
    }

	if (!flag)
		ft_error_print(MSHELL, command, NULL, ERR2);
	free_arr(path_arr);
	if (!path)
		path = ft_strdup("");
	return (path);
}