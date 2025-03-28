# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natgomali <marvin@42.fr>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 16:09:21 by natgomali         #+#    #+#              #
#    Updated: 2025/03/28 14:05:59 by namalier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJDIR 			= obj

SRCS 			=	srcs/main.c srcs/parsing.c srcs/utils.c srcs/utils_philo.c\
					srcs/init_philo.c srcs/routine.c srcs/forks.c \
					srcs/clean_exit.c srcs/utils_philo2.c \

OBJS 			=	$(patsubst %.c,${OBJDIR}/%.o,$(notdir ${SRCS}))

NAME			=	philo

CFLAGS			=	-Wall -Werror -Wextra -g3

${NAME}			:	${OBJDIR} ${OBJS}
					@cc ${OBJS} ${CFLAGS} -o ${NAME} -lpthread
					@echo "\e[38;5;82mCompilation Philo OK\033[92m"

$(OBJDIR)		:
				@mkdir -p $@

%.o: srcs/%.c
	@cc ${CFLAGS} -c $< -o $@

${OBJDIR}/%.o	: srcs/%.c
				@cc ${CFLAGS} -c $< -o $@

clean			:
				@rm -rf ${OBJDIR} includes/Libft/objs
				@echo "\e[38;5;82mclean OK\033[92m"

fclean			:	clean
				@rm -rf ${NAME}
				@echo "\e[38;5;82mfclean OK\033[92m"

re				: fclean all

all				: 	${NAME}

.PHONY			: all clean fclean re

