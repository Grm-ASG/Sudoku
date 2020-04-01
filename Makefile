NAME = sudoku

CC = gcc
FLAGS = -Wall -Werror -Wextra
PATH_SRC = ./srcs/
SOURCE = $(PATH_SRC)*.c
HEADER = ./includes/
PATH_OBJ = ./objects/
OBJECTS = $(PATH_OBJ)*.o
OPTIONS = -c -I $(HEADER)

all:
	@mkdir $(PATH_OBJ)
	@$(CC) $(FLAGS) $(OPTIONS) $(SOURCE)
	@mv *.o $(PATH_OBJ)
	@$(CC) $(OBJECTS) -o $(NAME)

clean:
	@/bin/rm -rf $(PATH_OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
