# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 15:01:24 by sgodin            #+#    #+#              #
#    Updated: 2023/04/29 14:20:54 by sgodin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = so_long.c get_next_line.c get_next_line_utils.c propagation.c

NAME = so_long

OBJS = ${SRCS:.c=.o}

.c.o:
	gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	gcc -Wall -Wextra -Werror -g -fsanitize=address -lmlx -framework OpenGL -framework AppKit ${OBJS} -o ${NAME}

all: ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf $(NAME)
	
re: fclean all

.PHONY: re fclean clean all .c.o 