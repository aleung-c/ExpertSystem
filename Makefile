NAME=ExpertSystem

FLAGS = -Wall -Wextra -Werror
INCLUDES= -I includes/ 

CPP_DIR=src
CLASS_DIR=classes

O_DIR = .tmp/

CORE =	main.cpp 

CLASS = MainController.cpp \
		Rule.cpp \
		Fact.cpp \
		InputController.cpp \
		InputController_FileOpening.cpp \
		InputController_FillValues.cpp \
		InputController_LexerParser.cpp \
		ExceptionsHandler.cpp

SRC_CORE = $(addprefix $(CPP_DIR)/, $(CORE))
CLS_CORE = $(addprefix $(CLASS_DIR)/, $(CLASS))

### END ###

CPP_SRC= $(SRC_CORE)
CLS_SRC= $(CLS_CORE)

O_FILES = $(CPP_SRC:%.cpp=$(O_DIR)%.o)
O_CLS_FILES = $(CLS_SRC:%.cpp=$(O_DIR)%.o)
O_ALL = $(O_FILES) $(O_CLS_FILES)
LIBS = 


all: prepare $(NAME)

prepare:
	@mkdir -p $(O_DIR)
	@mkdir -p $(O_DIR)$(CPP_DIR)
	@mkdir -p $(O_DIR)$(CLASS_DIR)

$(O_DIR)%.o: %.cpp
	@printf "[\033[32;1m $(NAME) \033[0m]\t\033[31;1m$<\033[0m\\n"
	@g++ $(FLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(O_ALL)
	@g++ $(FLAGS) -o $(NAME) $(O_ALL) $(LIBS) 
	@printf "[\033[32;1m Run \033[0m]\033[31;1m $(NAME) \033[0m\\n"

clean:
	@rm -rf $(O_DIR)
	@printf "[\033[32;1m Delete \033[0m] $(O_ALL) \033[0m\\n"

fclean: clean
	@rm -f $(NAME)
	@printf "[\033[32;1m Delete \033[0m] $(NAME) \033[0m\\n"

re: fclean all
