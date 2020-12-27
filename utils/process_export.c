//
// Created by Wolmer Rudy on 12/27/20.
//

#include "utils.h"

char **process_export(char *export_arg)
{
	char **result;
	int		equal_char_index;
	int i;
	char *mask;

	if (!(result = malloc(sizeof(char *) * 3)))
		exit(EXIT_FAILURE);
	equal_char_index = find_char(export_arg, '=');
	mask = get_mask(export_arg);
	if ((equal_char_index > 1 && mask[equal_char_index] != '0') || equal_char_index == 0)
	{
		write(1, "export: Not a valid identifier", 30);
		exit(1);
	}
	if (equal_char_index != -1)
	{
		if (export_arg[equal_char_index + 1] == '\0')
		{
			export_arg[equal_char_index] = '\0';
			result[0] = ft_strdup(export_arg);
			result[1] = ft_strdup("0");
			result[2] = NULL;
		}
		else
		{
			free(result);
			free(mask);
			mask = empty_str('0', ft_strlen(export_arg));
			i = equal_char_index + 1;
			while (mask[i] != '\0')
			{
				mask[i] = '1';
				i++;
			}
			result = ft_split(export_arg, '=', mask);
		}
	}
	else
	{
		result[0] = ft_strdup("0");
		result[1] = ft_strdup(export_arg);
		result[2] = NULL;
	}
	free(mask);
	return (result);
}