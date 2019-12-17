# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aseppala <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/21 10:09:10 by aseppala          #+#    #+#              #
#    Updated: 2019/12/17 21:22:37 by aseppala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
FLAGS = -Wall -Wextra -Werror
SRC = main.c get_next_line.c get_data.c remove_overlap.c fill_it.c
OBJ = $(SRC:.c=.o)
HDR = libft/includes

.PHONY: all clean fclean re debug

all: $(NAME)

$(NAME):
	make -C libft/ fclean && make -C libft/
	clang $(FLAGS) -I $(HDR) -c $(SRC)
	clang -o $(NAME) $(OBJ) -I $(HDR) -L libft/ -lft

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug:
	make -C libft/ fclean && make -C libft/
	clang -g $(FLAGS) -I $(HDR) -c $(SRC)
	clang -g -o $(NAME) $(OBJ) -I $(HDR) -L libft/ -lft
