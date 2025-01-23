# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 15:30:46 by osslakri          #+#    #+#              #
#    Updated: 2024/12/03 12:57:03 by osslakri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc 

CFLAGS = -Wall -Wextra -Werror
INC_DIR = ./includes

SRCS =	init_data.c\
		main.c\
		routine.c\
		utils.c\
		ft_print.c

HEADER = philo.h

OBJ_DIR = objectFile
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "🔗 Linking $(NAME)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: %.c $(HEADER) Makefile
	@mkdir -p $(dir $@)
	@echo "🔨 Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "🗑️  Removing $(NAME)..."
	@rm -f $(NAME)

re: fclean all

.PHONY: clean