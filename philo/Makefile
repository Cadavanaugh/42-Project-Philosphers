# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/01 13:55:45 by jode-cas          #+#    #+#              #
#    Updated: 2025/12/29 21:27:55 by jode-cas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
CC = cc -Wextra -Werror -Wall -g

SRC_FOLDER = src/
SRCS = $(SRC_FOLDER)main.c \
				$(SRC_FOLDER)get_cli_inputs.c \
				$(SRC_FOLDER)init.c \
				$(SRC_FOLDER)time.c \
				$(SRC_FOLDER)philo_moves.c \
				$(SRC_FOLDER)utils.c \
				$(SRC_FOLDER)grab_fork.c \
				$(SRC_FOLDER)waiter.c \

OBJ_FOLDER = objs/
OBJS = $(patsubst $(SRC_FOLDER)%.c,$(OBJ_FOLDER)%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(SRCS) -o philo

$(OBJS): $(SRCS)
	mkdir -p objs
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re