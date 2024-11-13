
	
a3q1: a3q1_functions.o a3q1_main.o 
	gcc -Wall a3q1_functions.o a3q1_main.o -o a3q1

a3q1_functions.o: a3q1_functions.c a3q1_header.h
	gcc -Wall -std=c99 -c a3q1_functions.c


a3q1_main.o: a3q1_main.c a3q1_header.h
	gcc -Wall -std=c99 -c a3q1_main.c


clean: 
	rm *.o a3q1 