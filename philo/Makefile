# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/01 13:55:45 by jode-cas          #+#    #+#              #
#    Updated: 2025/12/11 18:30:01 by jode-cas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
CC = cc -Wextra -Werror -Wall
SRCS = main.c \
				safe_functions.c \
				get_cli_inputs.c \
				init.c
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(SRCS) -o main

$(OBJS): $(SRCS)
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re