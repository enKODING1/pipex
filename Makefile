CC = cc -g
CFLAG = -Wall -Wextra -Werror
NAME = pipex
NAME_BONUS = pipex_bonus

SOURCES = ./src/pipex.c ./src/utils.c ./src/error.c
SOURCES_BONUS = ./src/pipex_bonus.c ./src/utils.c ./src/utils_bonus.c ./src/error.c
OBJECTS = $(SOURCES:.c=.o)
OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

LIBFT_DIR = ./lib/libft
GNL_DIR = ./lib/get_next_line
PIPEX_DIR = ./src
LIBFT_LIB = $(LIBFT_DIR)/libft.a
GNL_LIB = $(GNL_DIR)/libgnl.a

all:$(NAME)

bonus:$(NAME_BONUS)

$(NAME): $(LIBFT_LIB) $(OBJECTS)
	$(CC) $(CFLAG) -o $(NAME) $(OBJECTS) \
	-I $(PIPEX_DIR) -I $(LIBFT_DIR) -I $(GNL_DIR) \
	-L$(LIBFT_DIR) -lft

$(NAME_BONUS): $(LIBFT_LIB) $(GNL_LIB) $(OBJECTS_BONUS) 
	$(CC) $(CFLAG) -o $(NAME_BONUS) $(OBJECTS_BONUS) \
	-I $(PIPEX_DIR) -I $(LIBFT_DIR) -I $(GNL_DIR) \
	-L $(LIBFT_DIR) -lft \
	-L $(GNL_DIR) -lgnl 


$(LIBFT_LIB): 
	make -C $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

$(GNL_LIB):
	make -C $(GNL_DIR)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@ -I $(LIBFT_DIR) -I $(GNL_DIR)
	
clean:
	make clean -C $(LIBFT_DIR)	
	make clean -C $(GNL_DIR)
	rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(GNL_DIR)
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
