# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scuter <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 16:36:48 by vvandenb          #+#    #+#              #
#    Updated: 2022/03/28 01:16:12 by scuter           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a
HEADERS = libft.h
SRCS = 			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c	\
				ft_memset.c	ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c		\
				ft_toupper.c ft_tolower.c ft_strchr.c 	ft_strrchr.c ft_strncmp.c ft_memchr.c	\
				ft_memcmp.c	ft_strnstr.c	ft_atoi.c	ft_strcmp.c								\
				ft_calloc.c	ft_strdup.c															\
				ft_substr.c	ft_strjoin.c	ft_strtrim.c	ft_split.c							\
				ft_itoa.c	ft_strmapi.c	ft_striteri.c	ft_putchar_fd.c						\
				ft_putstr_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c
SRCS_BONUS = 	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
ifdef BONUS
	OBJS=$(SRCS:c=o) $(SRCS_BONUS:c=o)
else
	OBJS=$(SRCS:c=o)
endif

.PHONY: all
all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEADERS)
	@echo Compiling libft...
	@ar rcs $(NAME) $(OBJS)
	@echo Compiled libft...

.PHONY: bonus
bonus:
	@make BONUS=1 all

.PHONY: clean
clean:
	@rm -f $(SRCS:c=o) $(SRCS_BONUS:c=o)

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)

.PHONY: re
re: fclean all
