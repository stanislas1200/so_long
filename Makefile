# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 15:01:24 by sgodin            #+#    #+#              #
#    Updated: 2023/05/26 17:40:24 by sgodin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = so_long.c \
get_next_line.c \
get_next_line_utils.c \
propagation.c \
game_function.c \
file_utils.c \
file_utils2.c \
map_utils.c \
map_utils2.c \
map_utils3.c

NAME = so_long
SANITIZE = -g -fsanitize=address

OBJS = ${SRCS:.c=.o}

.c.o:
	gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}


${NAME}: ${OBJS}
	gcc -Wall -Wextra -Werror  -lmlx -framework OpenGL -framework AppKit ${OBJS} -o ${NAME}

all: ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf $(NAME)
	
re: fclean all

.PHONY: re fclean clean all .c.o 