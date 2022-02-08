# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 19:33:28 by ljohnson          #+#    #+#              #
#    Updated: 2022/02/08 07:52:35 by ljohnson         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = philo

#//////////////////////////////////////////////////////////////////////////////
#		ALL FILES
#//////////////////////////////////////////////////////////////////////////////

SRCS = philosophers.c	ph_utils.c	ph_init_and_finish.c	ph_buffet.c
OBJS = $(SRCS:.c=.o)
HEAD = philosophers.h

#//////////////////////////////////////////////////////////////////////////////
#		COMMAND SHORTCUTS
#//////////////////////////////////////////////////////////////////////////////

CC = gcc
CF = -Wall -Wextra -Werror
CI = -I
CS = -g -fsanitize=address
CG = -g3

RM = rm -rf

#//////////////////////////////////////////////////////////////////////////////
#		RULES
#//////////////////////////////////////////////////////////////////////////////

all: ${NAME}

# Binary creation rules

$(NAME): $(OBJS) $(HEAD) Makefile
	$(CC) $(CF) $(OBJS) -o $(NAME)

%.o: %.c $(HEAD) Makefile
	$(CC) -c $(CF) $< -o $@


# Mandatory Rules

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all