#include <iostream>
#include "Joueur.h"
#include "Piece.h"


	Joueur::Joueur(char couleur){
		setScore(0);
		setCouleur(couleur);
	}

	
	int Joueur::calculScore()
	{	
	}

	int Joueur::choixPosition()
	{

	}



	void Joueur::setScore(int score)
	{
		this->score = score;
	}

	void Joueur::setCouleur(char couleur)
	{
		this->couleur = couleur;
	}
	char Joueur::getCouleur()
	{
		return couleur;
	}

