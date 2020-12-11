
#include "parse.h"

static t_list *parse_pipeline(char *pipeline_line)
{
	t_list		*command_list;
	char 		*mask;
	char		**command_array;
	int			i;

	command_list = NULL;
	mask = get_mask(pipeline_line);
	command_array = ft_split(pipeline_line, '|', mask);
	i = 0;
	while (command_array[i] != NULL)
	{
		ft_lstadd_back(&command_list, ft_lstnew(parse_command(command_array[i])));
		i++;
	}
	free_2d_array((void **)command_array);
	free(mask);
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

t_list	*parse(char *command_line)
{
	t_list	*pipeline_list;
	char	**pipeline_lines;
	char	*mask;

	mask = get_mask(command_line);
	pipeline_lines = ft_split(command_line, ';', mask);

	pipeline_list = NULL;
	fill_pipeline_list(&pipeline_list, pipeline_lines);

	free_2d_array((void **)pipeline_lines);
	free(mask);

	return (pipeline_list);
}
