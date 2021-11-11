CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm

all: client server

client: client.o 
	${CC} -o client client.o 

client.o: client.c 
	${CC} ${CFLAGS} client.c
server: server.o 
	${CC} -o server server.o 

server.o: server.c 
	${CC} ${CFLAGS} server.c

LinkedList.o: LinkedList.c
	${CC} ${CFLAGS} LinkedList.c	


clean:
	rm -f *.o *~
