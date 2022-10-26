#ifndef PIECE_H
#define PIECE_H
#include "Couleur.h"

 class Piece {
	private :
		int i; //indice des lignes
		int j; //indice des colonnes
		int degLib; //degrés de liberté d'une pièce
		char couleur;// couleur d'une pièce

	public :
        //constructeur
        Piece(int l=-1,int c=-1,char couleur=VIDE);
        //mutateur indice ligne
		void setIndiceLigne(int i);
        //mutateur indice colonne
        void setIndiceCol(int j);
        //accesseur indice ligne
        int getIndiceLigne();
        //accesseur indice colonne
        int getIndiceCol();
        //mutateur degre de liberte
		void setDegLiberte(int degLib);
        //accesseur degre de liberte
        int getDegLiberte();
        //mutateur couleur de piece
        void setCouleur(char couleur);
        //accesseur couleur de piece
		char getCouleur();

};
#endif
