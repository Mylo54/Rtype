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

$(NAME):	$(OBJ)
	g++ -o engine $(OBJ)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all