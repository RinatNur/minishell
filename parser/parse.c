
#include "parse.h"
#include "functional/processing.h"

static t_list *parse_pipeline(char *pipeline_line)
{
	t_list		*command_list;
	char 		*mask;
	char		**command_array;
	int			i;

	command_list = NULL;
	mask = get_mask(pipeline_line);
	command_array = u_split(pipeline_line, '|', mask);
	i = 0;
	while (command_array[i] != NULL)
	{
		ft_lstadd_back(&command_list, ft_lstnew(parse_command(command_array[i])));
		i++;
	}
	free(mask);
	free_2d_array(command_array);
	return (command_list);
}

static void	fill_pipeline_list(t_list **pipeline_list, char **pipeline_lines)
{
	int 	i;
	t_list	*pipeline;
	t_list	*command_list;

	i = 0;
	while (pipeline_lines[i] != NULL)
	{
		command_list = parse_pipeline(pipeline_lines[i]);
		pipeline = ft_lstnew(command_list);
		ft_lstadd_back(pipeline_list, pipeline);
		i++;
	}
}

int      is_empty(const char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int		find_unexpected_token1(char *str)
{
	int i;
	char *mask;

	i = 0;
	mask = get_mask(str);
	while (str[i] != '\0')
	{
		if ((str[i] == '|' && str[i + 1] == '|') &&
			(mask[i] == '0' && mask[i + 1] == '0'))
		{
			ft_error("Syntax error near unexpected token: |", 2);
			free(mask);
			return (1);
		}
		i++;
	}
	free(mask);
	return (0);
}

int		find_unexpected_token2(char *str)
{
	int i;
	char *mask;

	i = 0;
	mask = get_mask(str);
	while (str[i] != '\0')
	{
		if ((str[i] == ';' && str[i + 1] == ';') &&
			(mask[i] == '0' && mask[i + 1] == '0'))
		{
			ft_error("Syntax error near unexpected token: ;", 2);
			free(mask);
			return (1);
		}
		i++;
	}
	free(mask);
	return (0);
}

int		find_unexpected_token3(char **pipeline_lines)
{
	int i;

	i = 0;
	while (pipeline_lines[i] != NULL)
	{
		if (is_empty(pipeline_lines[i]) && pipeline_lines[i + 1] != NULL)
		{
			ft_error("Syntax error near unexpected token: ;", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int		validate(char *command_line, char *mask, char **pipeline_lines)
{
	char **arr;
	char *clear_command_line;

	arr = u_split(command_line, ' ', mask);
	clear_command_line = arr_strjoin(arr);
	if (find_unexpected_token1(clear_command_line)
	|| find_unexpected_token2(clear_command_line)
	|| find_unexpected_token3(pipeline_lines))
	{
		free_2d_array(arr);
		free(clear_command_line);
		return (0);
	}
	free_2d_array(arr);
	free(clear_command_line);
	return (1);
}

t_list	*parse_pipeline_list(char *command_line)
{
	t_list	*pipeline_list;
	char	**pipeline_lines;
	char	*mask;


	mask = get_mask(command_line);
	pipeline_lines = u_split(command_line, ';', mask);
	if (!validate(command_line, mask, pipeline_lines))
	{
		free_2d_array(pipeline_lines);
		free(mask);
		return (NULL);
	}
	pipeline_list = NULL;
	fill_pipeline_list(&pipeline_list, pipeline_lines);

	free_2d_array(pipeline_lines);
	free(mask);

	return (pipeline_list);
}

void		free_pipeline_list(t_list *pipeline_list) //FIXME
{
	t_list *pipeline;
	t_list *command_list;

	pipeline = pipeline_list;
	while (pipeline != NULL)
	{
		command_list = pipeline->content;
		ft_lstclear(&command_list, (void (*)(void *))command_destructor);
		pipeline = pipeline->next;
	}
	empty_lst_clear(&pipeline_list);
}
