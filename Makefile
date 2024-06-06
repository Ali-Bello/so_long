NAME = so_long

CC = gcc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3

MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

SRCS = srcs/main2.c srcs/parsing.c srcs/render.c srcs/animation.c srcs/moves.c #srcs/scaling.c srcs/Player.c

LIBFTPATH = includes/libft

LIBFT = includes/libft/libft.a

INCLUDES = includes/get_next_line

all : $(NAME)

$(NAME) : $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES)/*.c $(LIBFT) $(MLXFLAGS) -o $(NAME)

$(LIBFT) : $(LIBFTPATH)
	make -C includes/libft

clean :
	make -C includes/libft clean

fclean : clean
	rm -rf $(LIBFT)
	rm -rf $(NAME)

re : fclean all
