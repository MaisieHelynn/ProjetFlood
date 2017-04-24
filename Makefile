CC=gcc
CFLAGS=-W -Wall -ansi
LDFLAGS=

testA: main.o Lot_A.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.c Lot_A.h
	$(CC) -o $@ -c $< $(CFLAGS)

Lot_A.o: Lot_A.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
