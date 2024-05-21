NAME = so_long

CC = gcc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

SRCS = srcs/main.c srcs/parsing.c srcs/map.c srcs/moves.c srcs/scaling.c srcs/animation.c

LIBFTPATH = includes/libft

LIBFT = includes/libft/libft.a

INCLUDES = includes/get_next_line

all : $(NAME)

$(NAME) : $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(SRCS) $(INCLUDES)/*.c $(LIBFT) -o $(NAME)

$(LIBFT) : $(LIBFTPATH)
	make -C includes/libft

clean :
	make -C includes/libft clean

fclean : clean
	rm -rf $(LIBFT)
	rm -rf $(NAME)

re : fclean all
