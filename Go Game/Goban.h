#ifndef GOBAN_H
#define GOBAN_H

#include "Couleur.h"
#include "Piece.h"
#include "Joueur.h"


class Goban {
	private :
		// dimension du plateau du jeu (Goban) : Taille * Taille
		int taille;
		// nombre des intersections pleines dans le Goban
		int casePleines;
		// les intersections du plateau de jeu
        vector< vector<Piece> > Plateau;
		// les joueurs
        vector< Joueur > joueurs;
		// indice du joueur ayant la main pour jouer 
		int joueurActuel;
        //état de jeu : nouvelle partie ou partie a continuer
           bool etatJeu;
        //une partie à handicap
           bool estHandicap;
        //pour prevenir la répétition
         vector<Goban*> gobanRep; /* état du goban au coup précédent */
         bool etatCapt[2];  /* état de capture au coup précédent */
	public :
		//constructeur du goban de jeu avec taille
		Goban(int dim);
        //constructeur du goban par copie
        Goban( Goban & goban);
        //initialistaion des données des pièces du goban
		void setGoban();
        //accesseur du goban
        const Goban& getGoban();
		//mitateur de la taille du goban
		void setTaille(int dim);
        //accesseur da la taille du goban
		int getTaille();
        //récupérer le plateau des pieces
        vector<vector<Piece>>& getPlateau();
        //récupérer les joueurs
        vector<Joueur>& getJoueurs();
        //savoir le joueur actuel
        int getJoueurActuel();
         //savoir le nombre des cases pleines
        int getCasesPleines();
        //modifier le nombres des cases pleines
            //incrémenter
        void incrCasePleine(int n=1);
            //decrémenter
        void decrCasePleine(int n=1);

        //affichage du plateau
        void affichage(bool val=true);

        //initialisation d'une partie à handicaps
        bool gestionHandicap();
        vector<vector<unsigned int>>& partieHandicap(int hand);
        //gestion de jeu
        int gestionPartie();

        //test sur les cases hors plateau
        bool caseHorsBorne(int i, int j );
        //test sur la validité d'une intersection par rapport à une couleur
        bool caseValide(int i, int j,char coul=VIDE);

        //calcul des libértés d'une pièce
        int compterDegLib(int i, int j);
        //savoir si on désire une partie en milieu de jeu
        bool jeuEnMilieuPartie();
        //générer une partie aléatoire
        vector<vector<int>>* jeuAleatoire();
        //récupérer une pièce du plateau
        Piece * getPiece(int x,int y);
        //savoir la couleur adverse d'une piece
        static char pieceAdverse(char coul);

        //test sur le suicide => coup intérdit
        bool testSuicide(int i,int j);

		//changer le tour de jeu
		void tourJoueur();
        //ajouter une pièce sur le goban
        void poserPiece(int i,int j);
        //supprimer la pièce
        void supprimerPiece(int i,int j);
        //getter est handicap
        bool getHandicap(){
            return estHandicap;
        }
        // sauvegarde du goban pour  joueur actuel
        void sauvGoban();
        // sauvegarde d'état de capture pour joueur actuel
        void sauvEtatCapt(bool etat);
        // test de répétition pour le joueur actuel
        bool testRepetition(int x, int y);

        /*****************************/
        //test si une pièce existe dans une liste*/
        /*bool existeListe(const Piece * p);*/
        //test si une chaine est connecte
        /*void chaineConnectee(int i,int j,char coul,vector<Piece*> &chaine);*/
        //vider une chaine
        /*void viderChaine();*/
        /****************************/
};
#endif
