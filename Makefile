# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 15:08:19 by nbeaufil          #+#    #+#              #
#    Updated: 2023/06/30 13:03:48 by nbeaufil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	readline.c		\
			shell.c			\
			utils.c			\
			funct.c

NAME	=	shp
OBJS	=	${SRCS:.c=.o}
DEBUG	=
FLAGS	=	-Wall -Wextra -Werror

.c.o	:
	gcc ${FLAGS} ${INCLUDE} ${DEBUG} -c $<

$(NAME)	:	${OBJS}
	gcc -o ${NAME} ${FLAGS} ${OBJS}

all	:	${NAME}

clean	:
	rm -f ${OBJS}

fclean	:	clean
	rm -f ${NAME}

re	:	fclean all

.PHONY: all clean fclean re

.SILENT:
