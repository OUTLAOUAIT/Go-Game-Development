#ifndef PIECE_H
#define PIECE_H
using namespace std;
#define NOIR 'N'
#define BLANC 'B'
#define VIDE '+'


 class Piece {
	private :
		int i; //indice des lignes
		int j; //indice des colonnes
		int degLib; //degrés de liberté d'une pièce
		char couleur;// couleur d'une piece

	public :
		Piece(int l=-1,int c=-1,int deg=5,char couleur=VIDE);
		void setIndiceLigne(int i);
		void setIndiceCol(int j);
		void setDegLiberte(int degLib);
		int getDegLiberte();
		void setCouleur(char couleur);
		char getCouleur();

};
#endif