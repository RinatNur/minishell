#include "parser/parse.h"
#include "functional/processing.h"


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
			str[i] = -100;
		i++;
	}
	tmp2 = u_split(str, -100, mask);
	free(mask);
	result = arr_strjoin(tmp2);
	free_2d_array(tmp2);
	if (result == NULL)
	    result = ft_strdup("");
	return (result);
}

char *replace_env(char *str, t_data *data)
{
	char **parsed_str;
	char *env_value;
	char *result;
	int i;

	i = 0;
	parsed_str = parse_env(str);
	while (parsed_str[i] != NULL)
	{
		if (parsed_str[i][0] == '$')
		{
			if (parsed_str[i][1] == '?')
				env_value = ft_itoa(g_code);
			else if (ft_isdigit(parsed_str[i][1]))
				env_value = ft_strdup(parsed_str[i] + 2);
			else
			{
				if (!(env_value = get_value_from_env(data, parsed_str[i] + 1)))
					env_value = u_strdup("");
				else
					env_value = u_strdup(env_value);
			}
			free(parsed_str[i]);
			parsed_str[i] = env_value;
		}
		i++;
	}
	result = arr_strjoin(parsed_str);
	free_2d_array(parsed_str);
	return result;
}

void process_command_envs(char **command_with_args, t_data *data)
{
	int i;
	char *tmp1;

	i = 0;
	while (command_with_args[i] != NULL)
	{
		tmp1 = replace_env(command_with_args[i], data);
		free(command_with_args[i]);
		command_with_args[i] = clear_quotes(tmp1);
		free(tmp1);
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

