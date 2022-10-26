#ifndef JOUEUR_H
#define JOUEUR_H

 class Joueur {
	private :
		int score;
		char couleur;
			
	public :
		Joueur(char couleur);		
		int calculScore();

		int choixPosition();	

		void setScore(int score);

		void setCouleur(char couleur);
		char getCouleur();


};
#endif