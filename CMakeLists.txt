cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell main.c parser/parse.h parser/utils/ft_strlen.c parser/utils/ft_lstadd_back.c parser/utils/ft_lstadd_front.c parser/utils/ft_lstclear.c parser/utils/ft_lstdelone.c parser/utils/ft_lstiter.c parser/utils/ft_lstlast.c parser/utils/ft_lstnew.c parser/utils/ft_lstsize.c parser/utils/utils.h parser/utils/ft_strdup.c parser/parse.c parser/utils/ft_split.c parser/parse_command.c parser/utils/mask.c)