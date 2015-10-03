# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avallete <avallete@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/17 11:43:55 by avallete          #+#    #+#              #
#    Updated: 2015/09/30 14:18:36 by avallete         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH=./src/
SRC_NAME=	ft_philo.c\
			init_functions.c
OBJ_PATH =./obj/
OBJ_NAME=$(SRC_NAME:.c=.o)
INC_PATH=./includes/
INC_NAME=libft.h\
		get_next_line.h\
		ft_printf.h\
		ft_bufferize.h\
		ft_philo.h
SRC=$(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ=$(addprefix $(OBJ_PATH), $(OBJ_NAME))
INCF=$(addprefix $(INC_PATH), $(INC_NAME))
INC=$(addprefix -I, $(INC_PATH))
LIB=-L libft/ -lftprintf
CFLAGS=-Wall -Wextra -Werror -g
CC=gcc
NAME=philo
RED=\033[0;31m
LBLUE=\033[34m
GREEN=\033[32m
CYAN=\033[0;36m
ORANGE=\033[0;33m
NC=\033[0m

all: $(NAME)

$(NAME):$(OBJ)
	@echo "${GREEN}Compile $(NAME) with $(CFLAGS)${NC}";
	@make -C libft
	@$(CC) $(CFLAGS) $(INC) $(LIB) $(OBJ) -o $(NAME);

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@echo "${ORANGE}Create bynary $(NAME) : $@ with $<${NC}";
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@echo "${RED}Delete OBJ files${NC}"
	@make -C libft clean
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "${RED}Delete $(NAME) file${NC}"
	@make -C libft fclean
	@rm -rf $(NAME)

re: fclean all clean

.PHONY: all clean fclean re
