CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: main.o LinkedList.o main_functions.o
	${CC} main.o LinkedList.o main_functions.o -o result

main.o: main.c
	${CC} ${CFLAGS} main.c

LinkedList.o: LinkedList.c
	${CC} ${CFLAGS} LinkedList.c

main_functions.o: main_functions.c
	${CC} ${CFLAGS} main_functions.c

clean:
	rm -f *.o *~