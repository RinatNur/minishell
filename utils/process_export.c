#include "libft.h"
#include "utils.h"
#include "functional/processing.h"

static void *exit_error1(char **str2)
{
	ft_error_print(MSHELL, "export", NULL, "not a valid identifier");
	free(str2);
	return NULL;
}

static char **exit_error2(char **result, char *export_arg)
{
	int i;

	i = 0;
	while (result[0][i] != '\0')
	{
		if ((!ft_isalpha(export_arg[i])) && !ft_isdigit(export_arg[i]))
		{
			ft_error_print(MSHELL, "export", NULL, "not a valid identifier");
			free_2d_array(result);
			return (NULL);
		}
		i++;
	}
	return (result);
}

void env_with_value(char ***result, const char *export_arg, int equal_char_index)
{
	char *mask;
	int i;

	free(*result);
	mask = empty_str('0', u_strlen(export_arg));
	i = equal_char_index + 1;
	while (mask[i] != '\0')
	{
		mask[i] = '1';
		i++;
	}
	*result = u_split(export_arg, '=', mask);
	free(mask);
}

void env_without_value(char **result, char *export_arg, int equal_char_index)
{
	export_arg[equal_char_index] = '\0';
	result[0] = u_strdup(export_arg);
	result[1] = u_strdup("\0");
	result[2] = NULL;
}

char **process_export_arg(char *export_arg)
{
	char **result;
	int	equal_char_index;

	if (!(result = malloc(sizeof(char *) * 3)))
		exit(EXIT_FAILURE);
	equal_char_index = find_char(export_arg, '=');
	if (ft_isdigit(export_arg[0]))
		return (exit_error1(result));
	if (equal_char_index == 0)
		return (exit_error1(result));
	if (equal_char_index != -1)
	{
		if (export_arg[equal_char_index + 1] == '\0')
			env_without_value(result, export_arg, equal_char_index);
		else
			env_with_value(&result, export_arg, equal_char_index);
	}
	else
	{
		result[0] = u_strdup("0");
		result[1] = u_strdup(export_arg);
		result[2] = NULL;
	}
	return (exit_error2(result, export_arg));
}

void set_export_arg(char **export_with_arguments, char **result)
{
	int i;
	int j;
	char **tmp;

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
}

char **process_export(char **export_with_arguments)
{
	int i;
	char **result;

	i = 0;
	while (export_with_arguments[i] != NULL)
		i++;
	if (!(result = malloc(sizeof(char *) * (i * 2))))
		exit(EXIT_FAILURE);
	result[0] = u_strdup(export_with_arguments[0]);
	if (i == 1)
	{
		result[1] = NULL;
		return (result);
	}
	set_export_arg(export_with_arguments, result);
	return (result);
}