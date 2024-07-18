NAME = so_long

CC = cc

CFLAGS = -Wall -Werror -Wextra 

MLXFLAGS = -lXext -lX11 -lm mlx/libmlx_Linux.a

SRCS = srcs/allocation.c srcs/enemy.c srcs/render.c srcs/errors.c srcs/player.c\
		srcs/game_init.c srcs/map.c srcs/map_utils.c srcs/map_utils2.c\
		srcs/render_utils.c srcs/so_long.c

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
