##
## EPITECH PROJECT, 2022
## src
## File description:
## Makefile
##

NAME	= engine

SRC	=	main.cpp

OBJ	=	$(SRC:.cpp=.o)	

all:	$(NAME)

CXX	=	g++ -g

CXXFLAGS	=	-std=c++17

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all