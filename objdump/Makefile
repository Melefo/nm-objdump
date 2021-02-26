##
## EPITECH PROJECT, 2021
## B-PSU-400-NAN-4-1-nmobjdump-victor.trencic [WSL: Ubuntu]
## File description:
## Makefile
##

SRC		=	sources/main.c		\
			sources/objdump.c	\
			sources/handler.c	\
			sources/header.c

OBJ		=	$(SRC:%.c=%.o)

TEST	=	\

NAME	=	my_objdump

CC		=	gcc

INCLUDE	=	-I include/

CFLAGS	=	-W -Wall -Wextra -Wshadow $(INCLUDE)

COVERAGE=	--coverage -lcriterion

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

dbg: CFLAGS += -g
dbg: re

tests_run:
	$(CC) -o unit_tests $(TEST) $(COVERAGE) $(CFLAGS)
	./unit_tests

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) unit_tests
	$(RM) *.gc*

re: fclean all

.PHONY: re fclean clean all tests_run