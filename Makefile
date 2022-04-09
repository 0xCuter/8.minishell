# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 08:53:40 by vvandenb          #+#    #+#              #
#    Updated: 2022/04/09 15:52:39 by vvandenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror	\
		-I $(HEADERS_DIR) -I $(LIBFT_DIR) -I /Users/$(USER)/.brew/opt/readline/include
ifdef DEBUG
	CFLAGS += -g
endif
ifdef FSAN
	CFLAGS += -g -fsanitize=address
endif

SRCS_DIR = srcs/
HEADERS_DIR = includes/
HEADERS = $(HEADERS_DIR)minishell.h
NAME = minishell
SRCS =	$(SRCS_DIR)main.c $(SRCS_DIR)signals.c	\
		$(SRCS_DIR)utils.c $(SRCS_DIR)str_utils.c $(SRCS_DIR)tab_utils.c	\
		$(SRCS_DIR)init.c $(SRCS_DIR)syntax.c $(SRCS_DIR)replace_input.c $(SRCS_DIR)init_cmds.c	\
		$(SRCS_DIR)exec/exec.c $(SRCS_DIR)exec/exec_builtin.c $(SRCS_DIR)exec/exec_cmd.c $(SRCS_DIR)exec/exec_utils.c \
		$(SRCS_DIR)init_redirs.c $(SRCS_DIR)init_redirs_utils.c $(SRCS_DIR)envs_utils.c	\
		$(SRCS_DIR)builtins/echo.c $(SRCS_DIR)builtins/exit.c $(SRCS_DIR)builtins/pwd.c $(SRCS_DIR)builtins/cd.c	\
		$(SRCS_DIR)builtins/env.c $(SRCS_DIR)builtins/unset.c $(SRCS_DIR)builtins/export.c
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
# @$(CC) $(OBJS) -o $@ $(CFLAGS) $(LIBFT_FLAGS) -l readline
	@$(CC) $(OBJS) -o $@ $(CFLAGS) $(LIBFT_FLAGS) -l readline -L /Users/$(USER)/.brew/opt/readline/lib
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
