cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell main.c parser/parse.h utils/ft_strlen.c utils/ft_lstadd_back.c utils/ft_lstadd_front.c utils/ft_lstclear.c utils/ft_lstdelone.c utils/ft_lstiter.c utils/ft_lstlast.c utils/ft_lstnew.c utils/ft_lstsize.c utils/utils.h utils/ft_strdup.c parser/parse.c utils/ft_split.c parser/parse_command.c utils/mask.c parser/command.c utils/clear_empty_list.c utils/empty_str.c gnl/get_next_line.c gnl/get_next_line_utils.c utils/process_export.c utils/find_char.c)