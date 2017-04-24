CC=gcc
CFLAGS=-W -Wall -ansi
LDFLAGS=

all: testA test

test:
	gcc testunitaire.c  Lot_A.c  -o testunitaire -I /usr/local/Cellar/cunit/2.1-3/include/ -lCUnit -L /usr/local/Cellar/cunit/2.1-3/lib/

testA: main.o Lot_A.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.c Lot_A.h
	$(CC) -o $@ -c $< $(CFLAGS)

Lot_A.o: Lot_A.c
	$(CC) -o $@ -c $< $(CFLAGS)
	

clean:
	rm -rf *.o

cleanall: clean
	rm -rf testA
	rm -rf testunitaire
