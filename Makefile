# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: masase <masase@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 16:49:44 by maw               #+#    #+#              #
#    Updated: 2025/01/31 16:04:04 by masase           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c \
		utils.c \
		routine.c \
		

OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Werror -Wextra -pthread

RM = rm -f

$(NAME): $(OBJS)
		gcc $(FLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)
		
re: fclean all
	