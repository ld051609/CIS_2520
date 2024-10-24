q2: q2.o q2_functions.o
	gcc -Wall q2.o q2_functions.o -o a2q2
q2_functions.o: q2_functions.c q2.h
	gcc -Wall -std=c99 -c q2_functions.c

q2.o: q2.c q2.h
	gcc -Wall -std=c99 -c q2.c

clean:
	rm *.o