#include "minishell.h"

char    *ft_find_path(t_data *data, char *command)
{
    char    *path = NULL;
    DIR     *dir;
    struct  dirent  *tmp;
    char    **path_arr;
    int     i = 0;
    int     flag = 0;

	!(path_arr = ft_split(get_value_from_env(data, "PATH"), ':')) ? ft_error("Environment variable PATH is not found", 6) : 0;
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
                break ;
            i++;
        }
        else
            i++;
    }
    return (path);
}