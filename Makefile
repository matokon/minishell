# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ochmurzy <ochmurzy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 17:23:16 by ochmurzy          #+#    #+#              #
#    Updated: 2025/07/31 18:18:29 by ochmurzy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME := minishell

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -g

# Directories
LIBFT_DIR = libft

INCLUDES := -I$(LIBFT_DIR)

# Libraries
LIBFT_LIB := $(LIBFT_DIR)/libft.a

# Source and object files
SRC := 

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT_LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
