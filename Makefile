NAME = a.out
RM	=		rm -f
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -Wshadow -pedantic -g
SOURCES = 	main.cpp					\

CXX = c++
OBJ = $(SOURCES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

va: all
	valgrind --leak-check=full ./a.out

.PHONY: all clean fclean re