a2: ./q1/q1_functions.o ./q1/helper.o ./q1/q1.o
	gcc -Wall q1_functions.o helper.o q1.o -o ./q1/a2

q1_functions.o: ./q1/q1_functions.c ./q1/q1.h
	gcc -Wall -std=c99 -c ./q1/q1_functions.c
helper.o: ./q1/helper.c ./q1/q1.h
	gcc -Wall -std=c99 -c ./q1/helper.c

q1.o: ./q1/q1.c ./q1/q1.h
	gcc -Wall -std=c99 -c ./q1/q1.c
clean: 
	rm *.o