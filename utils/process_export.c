#include "../libft/libft.h"
#include "utils.h"
#include "../functional/processing.h"

char **process_export_arg(char *export_arg)
{
	char **result;
	int       equal_char_index;
	int i;
	char *mask;


	if (!(result = malloc(sizeof(char *) * 3)))
		exit(EXIT_FAILURE);
	equal_char_index = find_char(export_arg, '=');
	mask = get_mask(export_arg);
	if (ft_isdigit(export_arg[0]))
	{
		ft_error_print(MSHELL, "export", NULL, "not a valid identifier");
		free(mask);
		free(result);
		return NULL;
	}
	if (equal_char_index == 0)
	{
		ft_error_print(MSHELL, "export", NULL, "not a valid identifier");
		free(mask);
		free(result);
		return NULL;
	}

	if (equal_char_index != -1)
	{
		if (export_arg[equal_char_index + 1] == '\0')
		{
			export_arg[equal_char_index] = '\0';
			result[0] = u_strdup(export_arg);
			result[1] = u_strdup("\0");
			result[2] = NULL;
		}
		else
		{
			free(result);
			free(mask);
			mask = empty_str('0', u_strlen(export_arg));
			i = equal_char_index + 1;
			while (mask[i] != '\0')
			{
				mask[i] = '1';
				i++;
			}
			result = u_split(export_arg, '=', mask);
		}
	}
	else
	{
		result[0] = u_strdup("0");
		result[1] = u_strdup(export_arg);
		result[2] = NULL;
	}
	free(mask);

	i = 0;
	while (result[0][i] != '\0')
	{
		if ((!ft_isalpha(export_arg[i])) && !ft_isdigit(export_arg[i]))
		{
			ft_error_print(MSHELL, "export", NULL, "not a valid identifier");
			free_2d_array(result);
			return NULL;
		}
		i++;
	}

	return (result);
}
char **process_export(char **export_with_arguments)
{
	int i;
	char **result;
	char **tmp;
	int j;
	i = 0;
	while (export_with_arguments[i] != NULL)
		i++;
	if (!(result = malloc(sizeof(char *) * (i * 2) )))
		exit(EXIT_FAILURE);
	result[0] = u_strdup(export_with_arguments[0]);
	if (i == 1)
	{
		result[1] = NULL;
		return (result);
	}
	i = 1;
	j = 1;
	while (export_with_arguments[j] != NULL)
	{
		tmp = process_export_arg(export_with_arguments[j]);
		if (tmp == NULL)
		{
			j++;
			continue;
		}
		result[i] = u_strdup(tmp[0]);
		result[i + 1] = u_strdup(tmp[1]);
		free_2d_array(tmp);
		i = i + 2;
		j++;
	}
	result[i] = NULL;
	return (result);
}