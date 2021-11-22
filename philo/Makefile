# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 20:09:13 by aalcara-          #+#    #+#              #
#    Updated: 2021/11/22 20:09:37 by aalcara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC_FILES = actions.c checker.c end_checker.c ft_atoi.c ft_bzero.c \
			ft_strcmp.c init.c philosophers.c routine.c start.c utils.c
SRC_DIR = sources
OBJ_DIR = objects
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -pthread -fsanitize=address
HEADERS = -I includes
RM = rm -fr

ALLFLAGS = $(CFLAGS) $(HEADERS)

$(NAME): $(OBJ)
	@$(CC) $(ALLFLAGS) $(OBJ) -o $(NAME)
	@echo "[$@] created!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p objects
	@$(CC) $(ALLFLAGS) -c $< -o $@
	@echo "Compiled "$<

all: $(NAME)

clean:
	@$(RM) $(OBJ_DIR)
	@echo ".o files deleted!"

fclean: clean
	@$(RM) $(NAME)
	@echo "[$(NAME)] deleted!"

re: fclean all

PHONY: all clean fclean re