C = filler.c utils.c get_next_line/get_next_line.c get_next_line/get_next_line.h
OBJECTS = *.o
INCLUDES = ./includes
NAME = dlian.filler

all: $(NAME)

$(NAME):
	gcc -Wextra -Wall -Werror -c $(C) -I $(INCLUDES)
	gcc -Wextra -Wall -Werror -o $(NAME) $(OBJECTS) -L. -lft

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all