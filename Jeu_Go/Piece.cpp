#include "Piece.h"

	Piece::Piece(int l,int c,int deg,char couleur){
		setIndiceLigne(l);
		setIndiceCol(c);
		setDegLiberte(deg);
		setCouleur(couleur);
	}
	

	void Piece::setIndiceLigne(int i){

		this->i = i;
	}

	void Piece::setIndiceCol(int j){

		this->j = j;
	}
	
	void Piece::setDegLiberte(int degLib){

		this->degLib = degLib;
	}

	int Piece::getDegLiberte(){
		return degLib;
	}

	void Piece::setCouleur(char couleur){

		this->couleur = couleur;
	}
	char Piece::getCouleur(){
		return couleur;
	}


