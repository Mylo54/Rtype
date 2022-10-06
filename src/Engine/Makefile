##
## EPITECH PROJECT, 2022
## src
## File description:
## Makefile
##

NAME	= engine

SRC	=	main.cpp		\
		PlayerPrefs.cpp	\
		Entity.cpp		\
		Registry.cpp

OBJ	=	$(SRC:.cpp=.o)	

all:	$(NAME)

CXX	=	g++ -g

CXXFLAGS	=	-std=c++17

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) -lsfml-graphics

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all