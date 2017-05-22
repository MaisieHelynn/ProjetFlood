CC=gcc
CFLAGS=-W -Wall -ansi
LDFLAGS=
UNAME= $(shell uname)

ifeq ($(UNAME), Darwin)
	Comp = SDLMain.m -I/Library/Frameworks/SDL.framework/Headers -framework SDL -framework Cocoa
	Fichier = ipi2_interface.c
endif
ifeq ($(UNAME), Linux)
	Comp = -lSDL
	Fichier = ipi2_interface_linux.c
endif


all: Floodit

Floodit: main.o solveur_omega.o ipi2_interface.o Lot_A.o Lot_B.o
	$(CC) -o $@ $^ $(Comp) $(LDFLAGS)

testA: main.o Lot_A.o
	$(CC) -o $@ $^ $(LDFLAGS)

testB: main.o Lot_A.o Lot_B.o
	$(CC) -o $@ $^ $(LDFLAGS)

testSolveurOpti: solveur_omega.o Lot_A.o Lot_B.o
	$(CC) -o $@ $^ $(LDFLAGS)

ipi2_interface.o: $(Fichier) Lot_A.h Lot_B.h
	$(CC) -o $@ -c $< $(CFLAGS)

solveur_alpha.o: solveur_alpha.c Lot_A.h Lot_B.h
	$(CC) -o $@ -c $< $(CFLAGS)

solveur_omega.o: solveur_omega.c Lot_A.h Lot_B.h
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.c Lot_A.h Lot_B.h ipi2_interface.h
	$(CC) -o $@ -c $< $(CFLAGS)

Lot_A.o: Lot_A.c
	$(CC) -o $@ -c $< $(CFLAGS)

Lot_B.o: Lot_B.c Lot_A.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

cleanall: clean
	rm -rf testA
	rm -rf testB
	rm -rf testSolveur
	rm -rf testSolveurOpti
	rm -rf testunitaire
	rm -rf Floodit

