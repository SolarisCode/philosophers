# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 20:18:30 by melkholy          #+#    #+#              #
#    Updated: 2023/02/16 21:01:39 by melkholy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread
CDIR = .

CFILES = ./helper.c ./philosophers.c ./routine.c ./status_time_check.c ./utils.c
OBJS = ${CFILES:.c=.o}

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -c $(CFILES)
	$(CC) $(CFLAGS) $(OBJS) -I$(CDIR) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
