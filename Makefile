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
PARSDIR = rt_parse
MLXDIR = rt_mlx
UTILDIR = rt_utils
PARSSRCS =	$(PARSDIR)/rt_check_data1.c		\
			$(PARSDIR)/rt_check_data2.c		\
			$(PARSDIR)/rt_read_file.c		\
			$(PARSDIR)/rt_read_getline1.c	\
			$(PARSDIR)/rt_read_getline2.c	\
			$(PARSDIR)/rt_set_data1.c		\
			$(PARSDIR)/rt_set_data2.c		\
			$(PARSDIR)/rt_set_data3.c		\
			$(PARSDIR)/rt_set_data4.c		\
			$(PARSDIR)/rt_set_data5.c
MLXSRCS =	$(MLXDIR)/rt_mlx_display.c	\
			$(MLXDIR)/rt_mlx_func.c
UTILSRCS =	$(UTILDIR)/rt_clear_data.c	\
			$(UTILDIR)/rt_error.c		\
			$(UTILDIR)/rt_print.c
SRCS =	miniRT.c	\
		$(PARSSRCS)	\
		$(UTILSRCS)	\
		$(MLXSRCS)
OBJS = $(SRCS:%.c=%.o)

$(NAME) : $(OBJS)
	make -C libft
	$(CC) $(CFLAG) $(LMXFLAG) -l ft -L libft $^ -o $@

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

norm : $(SRCS)
	norminette $^

.PHONY: all clean fclean re
