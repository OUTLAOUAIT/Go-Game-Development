CC = g++
CFLAGS =

Main: main.o Goban.o Joueur.o Piece.o
	$(CC) $(CFLAGS)  -o Main main.o Goban.o Joueur.o Piece.o
	
main.o: main.cpp 
	$(CC) $(CFLAGS)  -c main.cpp 

Goban.o: Goban.cpp Joueur.o Piece.o
	$(CC) $(CFLAGS) -c Goban.cpp

Joueur.o: Joueur.cpp
	$(CC) $(CFLAGS) -c Joueur.cpp

Piece.o: Piece.cpp
	$(CC) $(CFLAGS) -c Piece.cpp

.PHONY:
	all
	clean

all:
	make Main

clean:
	rm -f Main main.o Goban.o Joueur.o Piece.o
