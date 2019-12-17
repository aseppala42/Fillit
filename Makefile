# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aseppala <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/21 10:09:10 by aseppala          #+#    #+#              #
#    Updated: 2019/12/17 16:58:28 by aseppala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	make -C libft/ fclean && make -C libft/
	clang -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
	clang -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
	clang -o $(NAME) main.o get_next_line.o -I libft/includes -L libft/ -lft

clean:
	rm -f get_next_line.o main.o

debug:
	make -C libft/ fclean && make -C libft/
	clang -g -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
	clang -g -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
	clang -g -o $(NAME) main.o get_next_line.o -I libft/includes -L libft/ -lft

debugsp:
	make -C libft/ fclean && make -C libft/
	clang -g -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
	clang -g -Wall -Wextra -Werror -I libft/includes -o main.o -c complete_spaghetti.c
	clang -g -o debugsp main.o get_next_line.o -I libft/includes -L libft/ -lft

fclean: clean
	rm -f $(NAME)

re: fclean all
