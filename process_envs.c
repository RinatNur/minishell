#include "parser/parse.h"
#include "functional/processing.h"
#include "libft/libft.h"

char *clear_quotes(char *str)
{
	char *mask;
	char *result;
	char **tmp2;
	int i;

	mask = get_mask(str);
	i = 0;
	while (mask[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '\"') && mask[i] == '0')
			str[i] = -100; //костыль, конечно, но вряд ли в шеле будут использовать символы с отрицательным значением
		i++;
	}
	tmp2 = u_split(str, -100, mask);
	result = arr_strjoin(tmp2);
	return (result);
}

char *replace_env(char *str, t_data *data)
{
	char **parsed_str;
	char *env_value;
	int i;

	i = 0;
	parsed_str = parse_env(str);
	while (parsed_str[i] != NULL)
	{
		if (parsed_str[i][0] == '$')
		{
			if (parsed_str[i][1] == '?')
				env_value = ft_itoa(g_code);
			else
				env_value = get_value_from_env(data, parsed_str[i] + 1);
			if (env_value == NULL)
				env_value = ft_strdup("");
			free(parsed_str[i]);
			parsed_str[i] = env_value;
		}
		i++;
	}
	return arr_strjoin(parsed_str);
}

void process_command_envs(char **command_with_args, t_data *data)
{
	int i;
	char *tmp1;

	tmp1 = command_with_args[0];
	command_with_args[0] = clear_quotes(command_with_args[0]);
	free(tmp1);

	i = 1;
	while (command_with_args[i] != NULL)
	{
		tmp1 = replace_env(command_with_args[i], data);
		command_with_args[i] = clear_quotes(tmp1);
		i++;
	}
}

void process_redirect_envs(t_list *redirect_list, t_data *data)
{
	t_redirect *redirect;
	char *tmp;

	while (redirect_list != NULL)
	{
		redirect = (t_redirect *)(redirect_list->content);
		tmp = replace_env(redirect->filename, data);
		free(redirect->filename);
		redirect->filename = clear_quotes(tmp);
		free(tmp);
		redirect_list = redirect_list->next;
	}
}

