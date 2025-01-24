# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 14:28:37 by mazeghou          #+#    #+#              #
#    Updated: 2025/01/24 17:24:59 by mazeghou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
BIN_DIR = bin

all: $(NAME)

$(NAME): | $(BIN_DIR)
	make -C include/libft
	gcc -Wall -Wextra -Werror -o $(BIN_DIR)/$(NAME) src/main.c include/libft/libft.a

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	make -C include/libft clean
	rm -f $(BIN_DIR)/$(NAME)

fclean: clean
	make -C include/libft fclean
	rm -rf $(BIN_DIR)

re: fclean all

.PHONY: all clean fclean re
