.silent:

NAME	:= miniRT
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g #-fsanitize=address
LIBMLX	:= ./MLX42
SRCS 	:= main.c 
LIBFT	:= ./libft
GNL 	:= ./get_next_line
# BONUS	:= bonus.c

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm 
INCLUDE := -L $(LIBFT) -lft -L $(GNL) -lgnl
OBJS	:= ${SRCS:.c=.o}
# BOBJS	:= ${BONUS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@git clone https://github.com/codam-coding-college/MLX42.git 
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -sC $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@make -sC $(LIBFT)
	@make -sC $(GNL)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(INCLUDE) -o $(NAME)

bonus: $(NAME)

clean:
	@rm -rf $(OBJS) $(BOBJS)
	@cd $(LIBFT) && $(MAKE) clean
	@rm -rf MLX42

fclean: clean
	@rm -rf $(NAME)
	@cd $(GNL) && $(MAKE) fclean
	@cd $(LIBFT) && $(MAKE) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx, bonus