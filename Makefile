# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scuter <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 08:53:40 by vvandenb          #+#    #+#              #
#    Updated: 2022/03/24 00:18:25 by scuter           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror	\
		-I $(HEADERS_DIR) -I $(LIBFT_DIR)
ifdef DEBUG
	CFLAGS += -g
endif
ifdef FSAN
	CFLAGS += -fsanitize=address
endif

SRCS_DIR = srcs/
HEADERS_DIR = includes/
HEADERS = $(HEADERS_DIR)minishell.h
NAME = minishell
SRCS = $(SRCS_DIR)main.c $(SRCS_DIR)signals.c $(SRCS_DIR)parser.c $(SRCS_DIR)command.c $(SRCS_DIR)utils.c	\
		$(SRCS_DIR)builtins/echo.c $(SRCS_DIR)builtins/exit.c $(SRCS_DIR)builtins/pwd.c $(SRCS_DIR)builtins/cd.c
OBJS = $(SRCS:c=o)

#LIBFT
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_FLAGS = -lft -L$(LIBFT_DIR)

all: $(NAME)

%.o: %.c $(HEADERS) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): FORCE
	@make BONUS=1 -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	@echo Compiling...
	@$(CC) $(OBJS) -o $@ $(CFLAGS) $(LIBFT_FLAGS) -l readline
	@echo Compiled!

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)
	@echo Cleaned!

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo Fcleaned!

re: fclean all

FORCE:

.PHONY: FORCE clean fclean re
