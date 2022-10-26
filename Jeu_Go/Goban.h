#ifndef GOBAN_H
#define GOBAN_H

#include <vector>
#include "Joueur.h"
#include "Piece.h"



class Goban {
	private :
		// dimension du plateau du jeu (Goban) : Taille * Taille
		int taille;
		// les intersections du plateau de jeu
		vector <vector<Piece>> Plateau;
		// nombre des intersections pleines dans le Goban
		int casePleines;
		// les joueurs
		Joueur *joueurs[2];
		// indice du joueur aynat la main pour jouer 
		int joueurActuel;
		//liste des ieces à capturer		
        vector<vector<int>> listPiece;
	public :
		//constructeur du goban de jeu avec taille
		Goban(int dim);
		//destructeur
		virtual ~Goban();
		//modification des attributs du goban
		void setGoban();
		//mitateur de la taille du goban
		void setTaille(int NLig);
		//accesseur da lataille du goban
		int getTaille();
		//affichage du plateau
		void affichage(bool val=true);

		//calcul des libertes d'une piece
		int compterDegLib(int i, int j);
		
		//test sur la validite d'une intersection
		bool caseValide(int i, int j);
		//changer le tour de jeu
		void tourJoueur();
		//test pour capturer des pieces
		bool testGain();
		//test ôur le suicide => coup interdit
		bool testSuicide(int i,int j);
		//gestion d'une partie de jeu
		void gestionPartie();
		bool existeListe(vector<int> v);
};
#endif
