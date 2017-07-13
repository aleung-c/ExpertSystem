NAME = ExpertSystem

SRC = ./src/main.cpp \
./src/MainController.cpp \
./src/Rule.cpp \
./src/Fact.cpp \
./src/InputController.cpp \
./src/InputController_FileOpening.cpp \
./src/InputController_LexerParser.cpp \
./src/ExceptionsHandler.cpp

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
