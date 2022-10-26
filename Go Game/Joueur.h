#ifndef JOUEUR_H
#define JOUEUR_H
#include"Couleur.h"
class Joueur {
	private :
        char couleur;//couleur des pièces
        float capture;//nombre des pièces capturée
        int teritoire;//nombre des pièces sur goban
			
	public :
        //constructeur
        Joueur(char coul);

        //calcul du score
        float calculScore(bool handicap=false);

        //mutateur capturés
        void setCapture(int captures);
        //accesseur capturés
        int getCapture();

        //mutateurs teritoires
        ////incrémenter
        void incrTeritoire(int nbrPiece=1);
        ////décrémenter
        void decrTeritoire(int nbrPiece=1);

        //accesseur téritoires
        int getTeritoire();

        //mutateur couleur
		void setCouleur(char couleur);
        //accesseur couleur
		char getCouleur();


        /********************************/
        //choix de position d'intersection
        /*void choixPosition(int & i,int & j);*/
        /********************************/
};
#endif
