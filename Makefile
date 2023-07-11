# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 15:08:19 by nbeaufil          #+#    #+#              #
#    Updated: 2023/07/11 14:58:31 by nbeaufil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	shell.c							\
			utils.c							\
			funct.c							\
			readline/readline.c				\
			readline/read_history.c

NAME	=	sh
OBJS	=	${SRCS:.c=.o}
DEBUG	=
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
INCLUDE	=	-I include

.c.o	:
	${CC} ${FLAGS} ${INCLUDE} ${DEBUG} -c $< -o ${<:.c=.o}

$(NAME)	:	${OBJS}
	${CC} -o ${NAME} ${INCLUDE} ${FLAGS} ${OBJS}

all	:	${NAME}

clean	:
	rm -f ${OBJS}

fclean	:	clean
	rm -f ${NAME}

re	:	fclean all

.PHONY: all clean fclean re

.SILENT:
