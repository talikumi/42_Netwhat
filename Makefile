# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edi-marc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/18 16:50:31 by edi-marc          #+#    #+#              #
#    Updated: 2021/02/18 17:05:27 by edi-marc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = netcalc

S_NAME = a.out

SRCS = main_netcalc.c netcalc.h netcalc_utils.c ft_atoi.c

CC = gcc

RM = /bin/rm -f

MV = /bin/mv 

FLAGS = -Wall -Werror -Wextra

FILE = *.gch $(NAME) a.out

all: clean
	@$(CC) $(FLAGS) $(SRCS)
	@$(RM) *.gch
	@$(MV) $(S_NAME) $(NAME)

clean:
	@$(RM) $(FILE)

.PHONY: all clean
