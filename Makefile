# by Nat Welch

CC=gcc
CFLAGS=-Wall -g -c
LDFLAGS=-lm -lncurses
RMFLAGS=-vf

all: cur-top 

cur-top: main.o util.o 
	$(CC) ${LDFLAGS} -o $@ $^

%.o: %.c util.h
	$(CC) ${CFLAGS} $<

clean:
	@rm $(RMFLAGS) cur-top 
	@rm $(RMFLAGS) *.o *~ 
	@rm $(RMFLAGS) out* 
	@rm $(RMFLAGS) *.gch

