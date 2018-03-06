asgn: asgn.c container.c flexarray.c htable.c mylib.c rbt.c mylib.h htable.h 
	gcc -coverage -W -Wall -O2 -ansi -pedantic -lm *.c -o asgn
