a2: q1_functions.o helper.o test_q1.o
	gcc -Wall q1_functions.o helper.o test_q1.o -o a2

q1_functions.o: q1_functions.c q1.h
	gcc -Wall -std=c99 -c q1_functions.c
helper.o: helper.c q1.h
	gcc -Wall -std=c99 -c helper.c
test_q1.o: test_q1.c q1.h
	gcc -Wall -std=c99 -c test_q1.c

clean: 
	rm *.o