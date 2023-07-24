# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 15:08:19 by nbeaufil          #+#    #+#              #
#    Updated: 2023/07/24 16:05:54 by nbeaufil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	readline/utils.c				\
			readline/funct.c				\
			readline/readline.c				\
			readline/read_history.c

NAME	=	libreadline.a
OBJS	=	${SRCS:.c=.o}
DEBUG	=
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
INCLUDE	=	-I readline/include

.c.o	:
	${CC} ${FLAGS} ${INCLUDE} ${DEBUG} -c $< -o ${<:.c=.o}

$(NAME)	:	${OBJS}
	ar -rcs ${NAME} ${OBJS}
	ranlib ${NAME}

all	:	${NAME}

test	:	$(NAME)
	${CC} ${FLAGS} ${INCLUDE} test.c -c -o test.o
	${CC} ${FLAGS} test.o -L. -lreadline ${INCLUDE} -o test

clean	:
	rm -f ${OBJS}
	rm -f test.o

fclean	:	clean
	rm -f ${NAME}
	rm -f test

re	:	fclean all

.PHONY: all clean fclean re

.SILENT:
