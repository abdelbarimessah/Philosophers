# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amessah <amessah@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/08 02:03:06 by amessah           #+#    #+#              #
#    Updated: 2022/07/18 15:04:31 by amessah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

INCLUDE = philo.h

src =  philo.c	\
	   init.c	\
	   ft_outils.c \
	   ft_outils2.c \
	   start_ph.c	\

OBJECTS = $(src:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(INCLUDES)
	$(CC) $(CFLAGS) $(OBJECTS) -o  $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all bonus