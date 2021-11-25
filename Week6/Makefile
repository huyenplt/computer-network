CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm

all:  server client

client: client.o
	${CC} -o client client.o 

client.o: client.c 
	${CC} ${CFLAGS} client.c

server: server.o LinkedList.o
	${CC} server.o LinkedList.o -o server

server.o: server.c 
	${CC} ${CFLAGS} server.c

LinkedList.o: LinkedList.c
	${CC} ${CFLAGS} LinkedList.c	

clean:
	rm -f *.o *~
