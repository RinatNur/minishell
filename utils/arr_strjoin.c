//
// Created by Wolmer Rudy on 12/20/20.
//

#include "utils.h"

char *arr_strjoin(char **line)
{
	int		i;
	char	*result;
	char	*tmp;

	i = 1;
	if (line[0] == NULL)
		return (u_strdup(""));
	result = u_strdup(line[0]);
	while (line[i] != NULL)
	{
		tmp = u_strjoin(result, line[i]);
		free(result);
		result = tmp;
		i++;
	}
	return (result);
}