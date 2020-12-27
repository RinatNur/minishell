#include "parser/parse.h"
#include "functional/processing.h"

char *clear_quotes(char *str)
{
	char *mask;
	char *result;
	char *tmp1;
	char **tmp2;

	mask = get_mask(str);
	tmp2 = u_split(str, '\"', mask);
	tmp1 = arr_strjoin(tmp2);
	//free_2d_array(tmp2); FIXME

	tmp2 = u_split(tmp1, '\'', mask);
	free(tmp1);
	result = arr_strjoin(tmp2);
	return (result);
}

void process_envs(char **command_with_args, t_data *data)
{
	int i;
	int j;
	char *tmp1;
	char **tmp2;

	tmp1 = command_with_args[0];
	command_with_args[0] = clear_quotes(command_with_args[0]);
	free(tmp1);

	i = 1;
	while (command_with_args[i] != NULL)
	{
		j = 0;
		tmp2 = parse_env(command_with_args[i]);
		while (tmp2[j] != NULL)
		{
			if (tmp2[j][0] == '$')
			{
				tmp1 = get_value_from_env(data, tmp2[j] + 1);
				if (tmp1 == NULL)
					tmp1 = ft_strdup("");
				free(tmp2[j]);
				tmp2[j] = tmp1;
			}
			j++;
		}
		tmp1 = arr_strjoin(tmp2);
		command_with_args[i] = clear_quotes(tmp1);
		i++;
	}
}