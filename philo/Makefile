# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/20 17:04:36 by schoe             #+#    #+#              #
#    Updated: 2022/06/24 19:35:25 by schoe            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
SRCS = main.c ft_utils.c ft_philo_simul.c ft_proc.c
OBJS = ${SRCS:.c=.o}
RM = rm -f
INCLUDE = -I./includes
NAME = philo

all : $(NAME)

$(NAME) : ${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o philo

%.o : %.c
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${INCLUDE}

clean :
		${MAKE} -C ./libft clean
		${RM} ${OBJS}

fclean : clean
		${MAKE} -C ./libft fclean
		${RM} $(NAME)
re : 
	${MAKE} fclean 
	${MAKE} all

.PHONY: all clean fclean re
