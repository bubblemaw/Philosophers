# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: masase <masase@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 16:49:44 by maw               #+#    #+#              #
#    Updated: 2025/05/12 19:58:33 by masase           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/main.c \
		srcs/utils.c \
		srcs/routine.c \
		srcs/create_thread_mutex.c \
		srcs/end_thread_mutex.c \
		srcs/action.c \
		srcs/action_utils.c
		

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
	