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

FUNC = functional

GNl = gnl

PARS = parser

SRC_FUNC =  check_command.c free_utils.c ft_cd.c ft_check_redirects.c\
            ft_echo.c ft_env.c ft_error.c ft_exec.c ft_exit.c ft_export.c\
            ft_find_path.c ft_pipe.c ft_pwd.c ft_redirect.c ft_unset.c\
            lists_func.c make_env_list.c utils.c

SRC_GNL =   get_next_line.c get_next_line_utils.c

SRC_PARS =  command.c parse.c parse_command.c parse_redirects.c validate.c

SRC =   $(addprefix $(FUNC)/,$(SRC_FUNC))\
        $(addprefix $(GNl)/,$(SRC_GNL))\
        $(addprefix $(PARS)/,$(SRC_PARS))\
        main.c process_envs.c utils_main.c

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
