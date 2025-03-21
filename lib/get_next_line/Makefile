CC = cc -g
CFLAGS = -Wall -Wextra -Werror
NAME = libgnl.a

SOURCES = ./get_next_line.c ./get_next_line_utils.c \
		  ./get_next_line_bonus.c ./get_next_line_utils_bonus.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $^
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re