cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(libft)

add_executable(rinat_minishell
        libft/ft_atoi.c
        libft/ft_bzero.c
        libft/ft_calloc.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_isprint.c
        libft/ft_itoa.c
        #        libft/ft_lstadd_back.c
        #        libft/ft_lstadd_front.c
        #        libft/ft_lstlast.c
        #        libft/ft_lstnew.c
        #        libft/ft_lstsize.c
        libft/ft_memccpy.c
        libft/ft_memchr.c
        libft/ft_memcmp.c
        libft/ft_memcpy.c
        libft/ft_memmove.c
        libft/ft_memset.c
        libft/ft_putchar_fd.c
        libft/ft_putendl_fd.c
        libft/ft_putnbr_fd.c
        libft/ft_putstr_fd.c
        libft/ft_split.c
        libft/ft_strchr.c
        libft/ft_strdup.c
        libft/ft_strjoin.c
        libft/ft_strlcat.c
        libft/ft_strlcpy.c
        libft/ft_strlen.c
        libft/ft_strmapi.c
        libft/ft_strncmp.c
        libft/ft_strnstr.c
        libft/ft_strrchr.c
        libft/ft_strtrim.c
        libft/ft_substr.c
        libft/ft_tolower.c
        libft/ft_toupper.c
        libft/libft.h
        functional/ft_env.c
        functional/ft_error.c
        functional/ft_pwd.c
        functional/utils.c
        functional/ft_find_path.c
        functional/lists_func.c
        functional/make_env_list.c
        functional/ft_exec.c
        functional/ft_write.c
        functional/ft_echo.c
        functional/get_value_from_env.c
        functional/ft_export.c
        functional/ft_unset.c
        functional/ft_cd.c
        functional/ft_exit.c
        functional/ft_pipe.c
        functional/fill_list.c
        functional/ft_redirect.c
        functional/ft_check_redirects.c
        functional/processing.h
        #        functional/start.c
        main.c
        minishell.h
        parser/parse.h
        utils/ft_strlen.c
        utils/ft_lstadd_back.c
        utils/ft_lstadd_front.c
        utils/ft_lstclear.c
        utils/ft_lstdelone.c
        utils/ft_lstiter.c
        utils/ft_lstlast.c
        utils/ft_lstnew.c
        utils/ft_lstsize.c
        utils/utils.h
        utils/ft_strdup.c
        gnl/get_next_line.c
        gnl/get_next_line_utils.c
        parser/parse.c
        utils/ft_split.c
        parser/parse_command.c
        utils/mask.c
        parser/command.c
        utils/clear_empty_list.c
        utils/empty_str.c
        minishell.h
        utils/ft_strjoin.c
        utils/ft_strldup.c
        utils/strjoin_straight.c
        utils/process_export.c
        utils/find_char.c
        utils/parse_env.c process_envs.c)