##
## EPITECH PROJECT, 2021
## B-PSU-400-NAN-4-1-nmobjdump-victor.trencic [WSL: Ubuntu]
## File description:
## Makefile
##

MAIN	=	sources/main.c

MOBJ	=	$(MAIN:%.c=%.o)

SRC		=	sources/nm.c		\
			sources/handler.c	\
			sources/symbols.c	\
			sources/list.c		\
			sources/symbols32.c	\
			sources/list32.c	\

OBJ		=	$(SRC:%.c=%.o)

TEST	=	tests/tests_handler.c	\
			tests/tests_list.c		\
			tests/tests_list32.c	\
			tests/tests_nm.c

NAME	=	my_nm

CC		=	gcc

INCLUDE	=	-I include/

CFLAGS	=	-W -Wall -Wextra -Wshadow $(INCLUDE)

COVERAGE=	--coverage -lcriterion

all: $(NAME)

$(NAME): $(MOBJ) $(OBJ)
	$(CC) -o $(NAME) $(MOBJ) $(OBJ) $(CFLAGS)

dbg: CFLAGS += -g
dbg: re

tests_run:
	$(CC) -o unit_tests $(SRC) $(TEST) $(COVERAGE) $(CFLAGS)
	./unit_tests

clean:
	$(RM) $(OBJ)
	$(RM) $(MOBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) unit_tests
	$(RM) *.gc*

re: fclean all

.PHONY: re fclean clean all tests_run dbg