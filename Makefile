.silent:

NAME := miniRT
CC := cc
CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -O3 -g
LIBMLX := ./MLX42
HEADERS := -I ./include -I $(LIBMLX)/include
UNAME_S := $(shell uname -s)
LIBS := $(LIBMLX)/build/libmlx42.a $(LIBMLX)/build/_deps/glfw-build/src/libglfw3.a -ldl -pthread -lm
ifeq ($(UNAME_S),Darwin)
LIBS += -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
endif
SRCS := \
	main.c \
	parser/parser.c \
	parser/resolution/resolution.c \
	parser/ambient/ambient.c \
	parser/camera/camera.c \
	parser/light/light.c \
	parser/sphere/sphere.c \
	parser/plane/plane.c \
	parser/cylinder/cylinder.c \
	parser/square/square.c \
	parser/triangle/triangle.c \
	parser/utils/ft_atod.c \
	parser/utils/parse_utils.c \
	parser/utils/ft_free.c \
	scene/build_scene.c \
	scene/vector_arithmetic.c \
	scene/scene_utils.c \
	scene/objects.c \
	mlx/create_img.c \
	raytrace/raytrace_utils.c \
	raytrace/ray_color.c \
	raytrace/object_filler.c \
	raytrace/post_parse.c
OBJS := $(SRCS:.c=.o)

all: libmlx $(NAME)

libmlx:
	if [ ! -d "$(LIBMLX)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	else \
		echo "$(LIBMLX) already exists, pulling latest changes instead."; \
		cd $(LIBMLX) && git pull; \
	fi
	cmake $(LIBMLX) -B $(LIBMLX)/build
	$(MAKE) -sC $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJS)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx
