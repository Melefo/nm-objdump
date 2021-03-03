##
## EPITECH PROJECT, 2021
## B-PSU-400-NAN-4-1-nmobjdump-victor.trencic [WSL: Ubuntu]
## File description:
## Makefile
##

MV	=	mv

all: nm objdump

nm:
	make -C nm/
	$(MV) nm/my_nm .

objdump:
	make -C objdump/
	$(MV) objdump/my_objdump .

tests_run:
	make tests_run -C nm/
	make tests_run -C objdump/

clean:
	make clean -C nm/
	make clean -C objdump/

fclean:
	make fclean -C nm/
	make fclean -C objdump/
	$(RM) my_*

re:
	make re -C nm/
	make re -C objdump/
	$(MV) nm/my_nm .
	$(MV) objdump/my_objdump .

.PHONY: re fclean clean all tests_run nm objdump