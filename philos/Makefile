# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: himejjad <himejjad@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 04:35:49 by himejjad          #+#    #+#              #
#    Updated: 2023/05/12 05:41:37 by himejjad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosofer
SRC =  philo_parce.c philo.c philo_utils.c ft_split.c

FLAGS = -Wall -Wextra -Werror

all : ${NAME}

OBJS = ${SRC:.c=.o}

${NAME}: ${OBJS}
	@cc ${FLAGS} ${OBJS} -o ${NAME}
	@echo "all's ready"
clean :
	@rm -rf ${OBJS}
	@echo "all's clean"
fclean :clean
	@rm -rf ${OBJS} ${NAME}

re :fclean all