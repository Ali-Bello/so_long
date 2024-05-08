NAME = libft.a

CC = cc

CFLAGS = -Werror -Wextra -Wall

SRCS = ft_putstr_fd.c ft_strncmp.c ft_split.c ft_strlen.c\
	ft_strjoin.c ft_substr.c ft_strdup.c ft_memcpy.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $<
	ar rc $(NAME) $@

$(NAME): $(OBJS)

clean:
	rm -f $(OBJS) $(BOBJS)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
