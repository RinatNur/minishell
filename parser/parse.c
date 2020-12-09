
#include "parse.h"


static t_list *parse_pipeline(char *pipeline_line)
{
	t_list		*command_list;
	t_command	*command;
	char		**command_array;
	int			i;

	command_list = NULL;
	command_array = ft_split(pipeline_line, '|');
	i = 0;
	while (command_array[i] != NULL)
	{
		command = parse_command(command_array[i]);
		ft_lstadd_back(&command_list, ft_lstnew(command));
		i++;
	}
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

//char	*get_mask(char *line)
//{
//	int				i;
//	char			*result;
//	unsigned char	flag;
//	char 			control_symbol;
//
//	i = 0;
//	flag = 1;
//	if (!(result = malloc(sizeof(char) * ft_strlen(line))))
//		exit(EXIT_FAILURE);
//	while (line[i] != '\0')
//	{
//		if (flag == 1 && (line[i] == '\'' || line[i] == '\"'))
//			control_symbol = line[i];
//		if (line[i] == control_symbol)
//		{
//			flag = ~flag;
//			if (flag == 1)
//			{
//				result[i] = 0;
//				i++;
//				continue;
//			}
//		}
//		if (flag == 1)
//			result[i] = 1;
//		else
//			result[i] = 0;
//		i++;
//	}
//	return result;
//}

t_list	*parse(char *command_line)
{
	t_list	*pipeline_list;
	char	**pipeline_lines;
	char	*mask;
	int		i;

	mask = get_mask(command_line);
	pipeline_list = NULL;
	printf("%s\n", command_line);
	i = 0;
	while (i < ft_strlen(command_line))
	{
		printf("%d", mask[i]);
		i++;
	}
	printf("\n");
	//pipeline_lines = ft_split(command_line, ';');
	//fill_pipeline_list(&pipeline_list, pipeline_lines);
	//i = 0;
	//while (pipeline_lines[i] != NULL)
	//{
	//	free(pipeline_lines[i]);
	//	i++;
	//}
	//free(pipeline_lines);
	return (pipeline_list);
}

//111100001111111111000000000000000000000000000000011111111111111110000000000000111110000000