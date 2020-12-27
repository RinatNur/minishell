
#include "utils.h"

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
	if ((equal_char_index > 1 && mask[equal_char_index] != '0') || equal_char_index == 0)
	{
		write(2, "export: Not a valid identifier", 30);
		exit(1);
	}
	if (equal_char_index != -1)
	{
		if (export_arg[equal_char_index + 1] == '\0')
		{
			export_arg[equal_char_index] = '\0';
			result[0] = u_strdup(export_arg);
			result[1] = u_strdup("0");
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
	return (result);
}

char **process_export(char **export_with_arguments)
{
	int i;
	char **result;
	char **tmp;
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
	while (export_with_arguments[i] != NULL)
	{
		tmp = process_export_arg(export_with_arguments[i]);
		result[i] = u_strdup(tmp[0]);
		result[i + 1] = u_strdup(tmp[1]);
		//FIXME free tmp;
		i = i + 2;
	}
	result[i] = NULL;
	return (result);
}
