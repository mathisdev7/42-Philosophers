# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 14:28:37 by mazeghou          #+#    #+#              #
#    Updated: 2025/01/24 20:35:07 by mazeghou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
BIN_DIR = bin
SRC_DIR = src
UTILS_DIR = src/utils

CC = cc
CFLAGS =

SRCS = $(SRC_DIR)/main.c $(UTILS_DIR)/main.c $(UTILS_DIR)/ft.c

all: $(NAME)

$(NAME): | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(NAME) $(SRCS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(BIN_DIR)/$(NAME)

fclean: clean
	rm -rf $(BIN_DIR)

re: fclean all

.PHONY: all clean fclean re
