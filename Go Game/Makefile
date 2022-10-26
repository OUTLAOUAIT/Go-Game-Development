CC = g++
CFLAGS =

Main: main.o Goban.o Joueur.o Piece.o Chaine.o
	$(CC) $(CFLAGS)  -o Main main.o Goban.o Joueur.o Piece.o Chaine.o
	
main.o: main.cpp  Goban.o Joueur.o Piece.o
	$(CC) $(CFLAGS)  -c main.cpp 

Chaine.o: Chaine.cpp Goban.o Piece.o
	$(CC) $(CFLAGS) -c Chaine.cpp

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
	rm -f Chaine.o main.o Goban.o Joueur.o Piece.o



#g++ -c main.cpp Chaine.cpp Piece.cpp Joueur.cpp Goban.cpp
#g++ -o Main main.o Chaine.o Piece.o Joueur.o Goban.o
