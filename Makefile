# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 15:08:19 by nbeaufil          #+#    #+#              #
#    Updated: 2023/07/05 06:14:54 by nbeaufil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	shell.c				\
			utils.c				\
			funct.c				\
			readline.c			\
			read_history.c

NAME	=	shp
OBJS	=	${SRCS:.c=.o}
DEBUG	=
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror

.c.o	:
	${CC} ${FLAGS} ${INCLUDE} ${DEBUG} -c $<

$(NAME)	:	${OBJS}
	${CC} -o ${NAME} ${FLAGS} ${OBJS}

all	:	${NAME}

clean	:
	rm -f ${OBJS}

fclean	:	clean
	rm -f ${NAME}

re	:	fclean all

.PHONY: all clean fclean re

.SILENT:
