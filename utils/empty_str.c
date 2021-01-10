#include "utils.h"

char *empty_str(char c, int len)
{
	char	*result;
	int		i;

	if (!(result = malloc(sizeof(char) * len + 1)))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		result[i] = c;
		i++;
	}
	result[i] = 0;
	return (result);
}
