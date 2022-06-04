# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 11:39:33 by arendon-          #+#    #+#              #
#    Updated: 2022/06/01 18:48:11 by arendon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread
OBJS = $(patsubst %.c, %.o, $(SRCS))

SRCS = main_bonus.c read_arg.c info.c utils.c exit.c memory_philos.c \
		sit_philos.c routine_bonus.c time.c watching.c

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re
