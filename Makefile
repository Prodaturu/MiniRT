.silent:

NAME	:= miniRT
CC		:= cc 
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
# LIBMLX	:= ./MLX42
SRCS 	:= main.c \
			./garbage_collector/garbage_collector.c \
			./garbage_collector/garbage_remover.c \
			./parser/parser.c \
			./parser/ambient/ambient.c \
			./parser/camera/camera.c \
			./parser/light/light.c \
			./parser/cylinder/cylinder.c \
			./parser/plane/plane.c \
			./parser/sphere/sphere.c \
			./parser/utils/ft_atod.c \
			./parser/utils/parse_utils.c \
			./parser/utils/ft_free.c \
			./scene/build_scene.c \
			./scene/vector_arithmetic.c \
			./scene/scene_utils.c
# ./mlx/create_img.c
LIBFT	:= ./libft
GNL 	:= ./gnl42
HEADERS_FILES := ./include/garbage_collector.h \
			./include/minirt.h \
			./include/parser.h \
			./include/render_structs.h

HEADERS	:= -I ./include 
# -I $(LIBMLX)/include
# LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm 
INCLUDE := -L $(LIBFT) -lft -L $(GNL) -lgnl
OBJS	:= ${SRCS:.c=.o}
# BOBJS	:= ${BONUS:.c=.o}

all: $(NAME)
# all: libmlx $(NAME)

# libmlx:
# 	git clone https://github.com/codam-coding-college/MLX42.git 
# 	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -sC $(LIBMLX)/build -j4

%.o: %.c $(HEADERS_FILES)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@make -sC $(LIBFT)
	@make -sC $(GNL)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(INCLUDE) -o $(NAME) -lm
# @cmake $(LIBMLX) -B $(LIBMLX)/build && make -sC $(LIBMLX)/build -j4

bonus: $(NAME)

clean:
	@rm -rf $(OBJS) $(BOBJS)
	@cd $(LIBFT) && $(MAKE) clean
	@cd $(GNL) && $(MAKE) clean

fclean: clean
	@rm -rf $(NAME)
	@cd $(GNL) && $(MAKE) fclean
	@cd $(LIBFT) && $(MAKE) fclean
# @rm -rf MLX42

re: clean all

.PHONY: all, clean, fclean, re, libmlx, bonus