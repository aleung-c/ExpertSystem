NAME = ExpertSystem

SRC = ./src/main.cpp \
./src/MainController.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -Wall -Werror -Wextra


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CC) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
