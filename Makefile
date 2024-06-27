.silent:

NAME	:= miniRT
CC		:= cc -fsanitize=address
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
LIBMLX	:= ./MLX42
SRCS 	:= main.c 
LIBFT	:= ./libft
GNL 	:= ./gnl42
# BONUS	:= bonus.c

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm 
INCLUDE := -L $(LIBFT) -lft -L $(GNL) -lgnl
OBJS	:= ${SRCS:.c=.o}
# BOBJS	:= ${BONUS:.c=.o}

all: $(NAME)

# libmlx:
# 	@git clone https://github.com/codam-coding-college/MLX42.git 

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@make -sC $(LIBFT)
	@make -sC $(GNL)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -sC $(LIBMLX)/build -j4
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(INCLUDE) -o $(NAME)

bonus: $(NAME)

clean:
	@rm -rf $(OBJS) $(BOBJS)
	@cd $(LIBFT) && $(MAKE) clean
	@cd $(GNL) && $(MAKE) clean

fclean: clean
	@rm -rf $(NAME)
	@cd $(GNL) && $(MAKE) fclean
	@cd $(LIBFT) && $(MAKE) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx, bonus