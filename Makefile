# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/19 15:37:29 by jijeong           #+#    #+#              #
#    Updated: 2023/07/03 13:43:18 by jijeong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAG = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -fr
SRCS = miniRT.c
OBJS = $(SRCS:%.c=%.o)

$(NAME) : $(OBJS)
	make -C libft
	$(CC) $(CFLAG) $^ -l ft -L libft -o $@

%.o : %.c
	$(CC) $(CFLAG) -c $^ -o $@


all : $(NAME)


clean :
	make -C libft clean
	$(RM) $(RMFLAG) $(OBJS)


fclean :
	make clean
	make -C libft fclean
	$(RM) $(RMFLAG) $(NAME)


re :
	make fclean
	make all

test : $(NAME)
	./test.sh

.PHONY: all clean fclean re
