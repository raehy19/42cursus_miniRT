# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/19 15:37:29 by jijeong           #+#    #+#              #
#    Updated: 2023/08/16 18:57:46 by rjeong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

CC := cc

CFLAG := -Wall -Wextra -Werror -MMD -MP
MLX_FLAG := -Lmlx -lmlx -framework OpenGL -framework AppKit

RM := rm -f

LIBFT := ./libft/libft.a
LIBFT_DIR := libft

PARSE_DIR = rt_parse/
MLX_DIR = rt_mlx/
UTILS_DIR = rt_utils/
SIMUL_DIR = rt_simulation/

SRCS := \
	miniRT.c \

PARSE_SRCS := \
	rt_check_data1.c \
	rt_check_data2.c \
	rt_read_file.c \
	rt_read_getline1.c \
	rt_read_getline2.c \
	rt_set_data1.c \
	rt_set_data2.c \
	rt_set_data3.c \
	rt_set_data4.c \
	rt_set_data5.c \

MLX_SRCS := \
	rt_mlx_display.c \
	rt_mlx_func.c \

UTILS_SRCS :=	 \
	rt_clear_data.c \
	rt_error.c \
	rt_print.c \

SIMUL_SRCS :=	 \
	rt_ambient.c \
	rt_diffuse.c \
	rt_simulation_utils.c \

all : $(NAME)

OBJS := \
	$(SRCS:%.c=%.o) \
	$(addprefix $(PARSE_DIR), $(PARSE_SRCS:.c=.o)) \
	$(addprefix $(MLX_DIR), $(MLX_SRCS:.c=.o)) \
	$(addprefix $(UTILS_DIR), $(UTILS_SRCS:.c=.o)) \
	$(addprefix $(SIMUL_DIR), $(SIMUL_SRCS:.c=.o)) \

DEPS := \
	$(SRCS:%.c=%.d) \
	$(addprefix $(PARSE_DIR), $(PARSE_SRCS:.c=.d)) \
	$(addprefix $(MLX_DIR), $(MLX_SRCS:.c=.d)) \
	$(addprefix $(UTILS_DIR), $(UTILS_SRCS:.c=.d)) \
	$(addprefix $(SIMUL_DIR), $(SIMUL_SRCS:.c=.d)) \

-include $(DEPS) $(BONUS_DEPS)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAG) $(MLX_FLAG) -l ft -L libft $^ -o $@

%.o : %.c
	$(CC) $(CFLAG) -Imlx -c $< -o $@

$(LIBFT) :
	make -C $(LIBFT_DIR) all

clean :
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
	$(RM) $(DEPS)

fclean : clean
	$(RM) $(LIBFT)
	$(RM) $(RMFLAG) $(NAME)

re :
	make fclean
	make all

test : $(NAME)
	./test.sh

norm :
	norminette $(SRCS) \
	$(addprefix $(PARSE_DIR), $(PARSE_SRCS)) \
	$(addprefix $(MLX_DIR), $(MLX_SRCS)) \
	$(addprefix $(UTILS_DIR), $(UTILS_SRCS)) \
	$(addprefix $(SIMUL_DIR), $(SIMUL_SRCS)) \

.PHONY: all clean fclean re
