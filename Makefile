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
MLX_FLAG :=  -lmlx -framework OpenGL -framework AppKit

RM := rm -f

LIBFT := ./libft/libft.a
LIBFT_DIR := libft

MLX_LIB_NAME := libmlx.dylib
MLX_LIB_DIR := mlx

PARSE_DIR = rt_parse/
MLX_DIR = rt_mlx/
CALCULATE_DIR = rt_calculate/
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

CALCULATE_SRCS := \
	rt_cal_utils.c \
	rt_cal_cam_ray.c \
	rt_sphere.c \

MLX_SRCS := \
	rt_mlx_display.c \
	rt_mlx_func.c \

UTILS_SRCS := \
	rt_clear_data.c \
	rt_error.c \
	rt_print.c \
	rt_rotate_vector.c \

SIMUL_SRCS := \
	rt_ambient.c \
	rt_diffuse.c \
	rt_simulation_utils.c \

all : $(NAME)

OBJS := \
	$(SRCS:%.c=%.o) \
	$(addprefix $(PARSE_DIR), $(PARSE_SRCS:.c=.o)) \
	$(addprefix $(MLX_DIR), $(MLX_SRCS:.c=.o)) \
	$(addprefix $(CALCULATE_DIR), $(CALCULATE_SRCS:.c=.o)) \
	$(addprefix $(UTILS_DIR), $(UTILS_SRCS:.c=.o)) \
	$(addprefix $(SIMUL_DIR), $(SIMUL_SRCS:.c=.o)) \

DEPS := \
	$(SRCS:%.c=%.d) \
	$(addprefix $(PARSE_DIR), $(PARSE_SRCS:.c=.d)) \
	$(addprefix $(MLX_DIR), $(MLX_SRCS:.c=.d)) \
	$(addprefix $(CALCULATE_DIR), $(CALCULATE_SRCS:.c=.d)) \
	$(addprefix $(UTILS_DIR), $(UTILS_SRCS:.c=.d)) \
	$(addprefix $(SIMUL_DIR), $(SIMUL_SRCS:.c=.d)) \

-include $(DEPS) $(BONUS_DEPS)

$(NAME) : $(LIBFT) $(MLX_LIB_NAME) $(OBJS)
	$(CC) $(CFLAG) $(MLX_FLAG) -l ft -L libft $^ -o $@

%.o : %.c
	$(CC) $(CFLAG) -Imlx -c $< -o $@

$(LIBFT) :
	make -C $(LIBFT_DIR) all

$(MLX_LIB_NAME) :
	make -C $(MLX_LIB_DIR) all
	cp ./mlx/$(MLX_LIB_NAME) ./$(MLX_LIB_NAME)


clean :
	make -C $(MLX_LIB_DIR) clean
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
	$(RM) $(DEPS)

fclean : clean
	$(RM) $(LIBFT)
	$(RM) $(MLX_LIB_NAME)
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
	$(addprefix $(CALCULATE_DIR), $(CALCULATE_SRCS)) \
	$(addprefix $(UTILS_DIR), $(UTILS_SRCS)) \
	$(addprefix $(SIMUL_DIR), $(SIMUL_SRCS)) \

.PHONY: all clean fclean re
