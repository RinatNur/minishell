/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:12:02 by jheat             #+#    #+#             */
/*   Updated: 2021/01/13 18:12:05 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

static char		*print_error_is_path_not_valid(t_data *data,
								char **path_arr, char *path)
{
	ft_error_print(MSHELL, data->ar[0], NULL, ERR5);
	path = ft_strdup("");
	if (path_arr)
		free_arr(path_arr);
	return (path);
}

static char		*find_command_in_dir(DIR *dir, char *command,
									char *path_arr, int *flag)
{
	struct dirent		*tmp;
	char				*tmp_str;
	char				*path;

	path = NULL;
	tmp_str = NULL;
	while ((tmp = readdir(dir)) != NULL)
	{
		if (!ft_strncmp(command, tmp->d_name, (ft_strlen(command) + 1)))
		{
			tmp_str = ft_strjoin(path_arr, "/");
			path = ft_strjoin(tmp_str, command);
			if (tmp_str)
				free(tmp_str);
			(*flag) = 1;
			return (path);
		}
	}
	return (NULL);
}

static int		check_directory(char *path_arr, char *command,
								char **path, int *flag)
{
	DIR		*dir;

	dir = NULL;
	dir = opendir(path_arr);
	if (NULL != dir)
	{
		*path = find_command_in_dir(dir, command, path_arr, flag);
		if ((*flag) == 1)
		{
			if (dir)
				(closedir(dir)) ? exit(32) : 0;
			return (1);
		}
	}
	if (dir)
		(closedir(dir)) ? exit(32) : 0;
	return (0);
}

char			*ft_find_path(t_data *data, char *command)
{
	char		*path;
	char		**path_arr;
	int			i;
	int			flag;

	i = 0;
	flag = 0;
	path = NULL;
	path_arr = ft_split(get_value_from_env(data, "PATH"), ':');
	if (!path_arr || !path_arr[0])
		return (print_error_is_path_not_valid(data, path_arr, path));
	while (path_arr[i])
	{
		if ((check_directory(path_arr[i], command, &path, &flag)) == 1)
			break ;
		i++;
	}
	if (!flag)
		ft_error_print(MSHELL, command, NULL, ERR2);
	free_arr(path_arr);
	if (!path)
		path = ft_strdup("");
	return (path);
}
