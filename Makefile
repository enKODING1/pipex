CC = cc -g
CFLAG = -Wall -Wextra -Werror
NAME = pipex

SOURCES = ./src/pipex.c
OBJECTS = $(SOURCES:.c=.o)

LIBFT_DIR = ./lib/libft
PIPEX_DIR = ./src
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all:$(NAME)

$(NAME): $(LIBFT_LIB) $(OBJECTS)
	$(CC) $(CFLAG) -o $(NAME) $(OBJECTS) \
	-I $(PIPEX_DIR) -I $(LIBFT_DIR) \
	-L$(LIBFT_DIR) -lft
	
$(LIBFT_LIB): 
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