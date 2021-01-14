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

NAME = utils.a

LIST  =	    arr_strjoin.c clear_empty_list.c empty_str.c find_char.c\
            ft_isalpha.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c\
            ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstnew.c ft_lstsize.c\
            ft_split.c ft_strdup.c ft_strjoin.c ft_strldup.c ft_strlen.c\
            mask.c parse_env.c process_export.c

OBJ = $(patsubst %.c,%.o,$(LIST))

HEADER = utils.h

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
