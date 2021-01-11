# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/26 12:02:44 by jheat             #+#    #+#              #
#    Updated: 2020/05/27 14:16:04 by jheat            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

LIST  =	    ft_memcpy.c ft_strlen.c ft_strlcpy.c ft_strncmp.c ft_atoi.c\
            ft_isdigit.c ft_strdup.c ft_strjoin.c ft_split.c ft_itoa.c\
			ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_lstadd_back_env.c ft_lstnew_env.c

OBJ = $(patsubst %.c,%.o,$(LIST))

HEADER = libft.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
		ar rc $(NAME) $? 
		ranlib $(NAME)

%.o: %.c $(HEADER)
		gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
