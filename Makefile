# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maw <maw@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 16:49:44 by maw               #+#    #+#              #
#    Updated: 2025/05/09 16:00:22 by maw              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c \
		utils.c \
		routine.c \
		create_thread.c \
		action.c
		

OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Werror -Wextra -pthread -g

RM = rm -f

$(NAME): $(OBJS)
		gcc $(FLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)
		
re: fclean all
	