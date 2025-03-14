CC = cc -g
CFLAG = -Wall -Wextra -Werror
NAME = pipex

SOURCES = ./src/pipex.c
OBJECTS = $(SOURCES:.c=.o)

LIBFT_DIR = ./lib/libft
PIPEX_DIR = ./src
LIBFT_LIB = ./lib/libft

all:$(NAME)

$(NAME): $(LIBFT_DIR) $(OBJECTS)
	$(CC) $(CFLAG) $(OBJECTS) -o $(NAME) \
	-I $(PIPEX_DIR) -I $(LIBFT_DIR) \
	-L$(LIBFT_LIB) -lft
	
$(LIBFT_DIR): 
	make -C $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@ -I $(LIBFT_DIR) 
	
clean:
	make clean -C $(LIBFT_DIR)	
	rm -f $(OBJECTS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re