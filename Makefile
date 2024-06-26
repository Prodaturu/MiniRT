.silent:

NAME	:= miniRT
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g #-fsanitize=address
LIBMLX	:= ./MLX42
SRCS 	:= main.c 
LIBFT	:= ./libft
# BONUS	:= bonus.c

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm 
INCLUDE := -L $(LIBFT) -lft
OBJS	:= ${SRCS:.c=.o}
# BOBJS	:= ${BONUS:.c=.o}

all: libmlx $(NAME)

libmlx:
	git clone https://github.com/codam-coding-college/MLX42.git 
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -sC $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(INCLUDE) -o $(NAME)

bonus: $(NAME)

clean:
	@rm -rf $(OBJS) $(BOBJS)
	@cd $(LIBFT) && $(MAKE) clean
	@rm -rf MLX42

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, bonus