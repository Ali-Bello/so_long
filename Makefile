NAME = so_long

CC = cc

CFLAGS = -Wall -Werror -Wextra 

MLXFLAGS = -lXext -lX11 -lm mlx/libmlx_Linux.a

SRCS = new/allocation.c new/enemy.c new/render.c new/errors.c new/player.c\
		new/game_init.c new/map.c new/map_utils.c new/map_utils2.c\
		new/render_utils.c new/so_long.c

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