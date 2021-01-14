# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jheat <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 16:00:23 by jheat             #+#    #+#              #
#    Updated: 2021/01/14 16:00:25 by jheat            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =   main.c process_envs.c\
        functional/check_command.c\
        functional/free_utils.c\
        functional/ft_cd.c\
        functional/ft_check_redirects.c\
        functional/ft_echo.c\
        functional/ft_env.c\
        functional/ft_error.c\
        functional/ft_exec.c\
        functional/ft_exit.c\
        functional/ft_export.c\
        functional/ft_find_path.c\
        functional/ft_pipe.c\
        functional/ft_pwd.c\
        functional/ft_redirect.c\
        functional/ft_unset.c\
        functional/lists_func.c\
        functional/make_env_list.c\
        functional/utils.c\
        gnl/get_next_line.c\
        gnl/get_next_line_utils.c\
        parser/command.c\
        parser/parse.c\
        parser/parse_command.c\
        parser/parse_redirects.c

OBJ = $(patsubst %.c,%.o,$(SRC))

HEADER =    minishell.h ./functional/processing.h ./gnl/get_next_line.h\
            ./parser/parse.h

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@make -C utils
	@cp libft/libft.a ./
	@cp utils/utils.a ./
	@gcc $(FLAGS) libft.a utils.a $(SRC) -o $(NAME)

bonus: all

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

clean:
	@make -C libft clean
	@make -C utils clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	@make -C utils fclean
	@rm -f libft.a
	@rm -f utils.a
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
