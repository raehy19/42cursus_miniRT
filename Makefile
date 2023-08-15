# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/19 15:37:29 by jijeong           #+#    #+#              #
#    Updated: 2023/08/08 14:58:26 by jijeong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAG = -Wall -Wextra -Werror
LMXFLAG= -l mlx  -framework OpenGL -framework AppKit
RM = rm
RMFLAGS = -fr
SRCS = miniRT.c
OBJS = $(SRCS:%.c=%.o)

$(NAME) : $(OBJS)
	make -C libft
	$(CC) $(CFLAG) $^ $(LMXFLAG) -l ft -L libft -o $@

%.o : %.c
	$(CC) $(CFLAG) -Imlx -c $^ -o $@


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
