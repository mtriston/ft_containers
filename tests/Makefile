NAME = test

INCLUDE = ../

CC = clang++

CFLAGS = -Wall -Wextra -Werror

HEADER = test.hpp

SRC = test.cpp vector_test.cpp stack_test.cpp queue_test.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ)
%.o : %.cpp
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
