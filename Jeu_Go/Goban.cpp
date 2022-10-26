#include <iostream>
#include "Joueur.h"
#include "Piece.h"
#include "Goban.h"

	Goban::Goban(int dim){
		
		casePleines=0;
        joueurActuel=0;
        joueurs[0]=new Joueur(NOIR);
        joueurs[1]=new Joueur(BLANC);
		setTaille(dim);
		setGoban();
	}
	Goban::~Goban(){
		free(joueurs[0]);
		free(joueurs[1]);
		printf("fin\n" );
	}
	void Goban::setTaille(int dim)
	{
		this->taille = dim;
	}

	int Goban::getTaille()
	{
		return taille;
	}

	void Goban::setGoban()
	{
		Plateau.resize(taille);
		for(int i=0;i<taille;i++){
			Plateau[i].resize(taille);
			for(int j=0;j<taille;j++){
				Plateau[i][j].setIndiceLigne(i);
				Plateau[i][j].setIndiceCol(j);
				
				/*if((i==0 || i==taille-1 )&& (j==0 || j==taille-1)){
					Plateau[i][j].setDegLiberte(2);
				}
				else if((i>0 && i<taille-1 ) && (j>0 && j<taille-1)){
					Plateau[i][j].setDegLiberte(4);
				}
				else {
					Plateau[i][j].setDegLiberte(3);
				}*/
			}
		}
	}


	void Goban::affichage(bool val)
	{	

		cout<<"    ";
		for (int j= 0; j < taille; ++j)
			{
				cout<<j+1<<"   ";
				if(j>=9)	cout<<"\b";
			}
		cout<<endl<<endl;
		
		for (int i = 0; i < taille; ++i)
		{
			cout<<i+1<<"   ";
			if(i>=9)	cout<<"\b";
			for (int j= 0; j < taille; ++j)
			{
				if(!val)
					cout<<Plateau[i][j].getDegLiberte();
				else 
					cout<<Plateau[i][j].getCouleur();
				if(j<taille-1)
					cout<<"---";
			}
			cout<<endl;
			if(i<taille-1){
				cout<<"    ";
				for (int j= 0; j < taille; ++j)
					{
						cout<<"|   ";
					}
				cout<<endl;
			}
		}		
	}

	bool Goban::caseValide(int i, int j)
	{
		if(i<taille && j<taille && i>=0 && j>=0 && Plateau[i][j].getCouleur()== VIDE) return true;
		else return false;

	}

	void Goban::tourJoueur()
	{
		if(joueurs[joueurActuel]->getCouleur()==BLANC){
			joueurActuel=0;
		}
		else if (joueurs[joueurActuel]->getCouleur()==NOIR)
		{
			joueurActuel=1;
		}
	}

	//calcul des libertes d'une piece
	int Goban::compterDegLib(int i, int j){
		int n=0;
		if( j-1 >= 0  		&&	Plateau[i][j-1].getCouleur() == VIDE )	n++;
		if( j+1 < taille 	&& 	Plateau[i][j+1].getCouleur() == VIDE )	n++;
		if( i-1 >= 0 		&& 	Plateau[i-1][j].getCouleur() == VIDE )	n++;
		if( i+1 < taille 	&& 	Plateau[i+1][j].getCouleur() == VIDE ) 	n++;
		return n;
	}

	bool Goban::testGain()
	{

	}
	bool Goban::existeListe(vector<int> v){
		for(vector<int> e:listPiece){
			if(e[0]==v[0] && e[1]==v[1])
				return true;
		}
		return false;
	}
	bool Goban::testSuicide(int i,int j){
		static int n=0;

        if ( (i>=0  && i<taille) && (j>=0 && j<taille) && !existeListe({i,j}) &&
             ( Plateau[i][j].getCouleur()==VIDE || Plateau[i][j].getCouleur()==joueurs[joueurActuel]->getCouleur() ) ){
        	listPiece.push_back( vector<int> ({i,j}) );
        	cout<<"{"<<i<<","<<j<<"}"<<Plateau[i][j].getCouleur()<<" "<<endl;
           	if ( Plateau[i][j].getCouleur()==VIDE){
                n++;
            }
        	
	           	testSuicide(i+1,j);
	           	testSuicide(i-1,j);
	           	testSuicide(i,j+1);
	           	testSuicide(i,j-1);
        }
        else{
            cout<<"["<<joueurs[joueurActuel]->getCouleur()<<"]"<<endl;
        }
        cout<<"Vides "<<n<<endl;
        if(n>=1){
        	n=0;
	        return  false;
        }
        n=0;
		return true;
	}

	void Goban::gestionPartie()
	{	
		do{
			affichage();
			int i=-1,j=-1;
			cout<<endl<<"Tour du Joueur "<<joueurs[joueurActuel]->getCouleur()<<endl;
			do{
					cout<<endl<<"Position (ligne,colonne) :  ";
					cin>>i>>j;
			}while(caseValide(--i,--j)==false);
			system("clear");
           
            listPiece.resize(0);
            int a=testSuicide(i,j);
            cout<<"("<<a<<")"<<endl;
			Plateau[i][j].setCouleur(joueurs[joueurActuel]->getCouleur());
			Plateau[i][j].setDegLiberte(compterDegLib(i,j));
			casePleines++;
			if( (j-1) >= 0  &&  Plateau[i][j-1].getCouleur() != VIDE)
				Plateau[i][j-1].setDegLiberte(compterDegLib(i,j-1));
			if( (j+1) < taille 	&& Plateau[i][j+1].getCouleur() != VIDE)
				Plateau[i][j+1].setDegLiberte(compterDegLib(i,j+1));
			if( (i-1) >= 0 	&& Plateau[i-1][j].getCouleur() != VIDE)
				Plateau[i-1][j].setDegLiberte(compterDegLib(i-1,j));
			if( (i+1) < taille 	&& Plateau[i+1][j].getCouleur() != VIDE)
				Plateau[i+1][j].setDegLiberte(compterDegLib(i+1,j));

			tourJoueur();
			
		}while(casePleines<(taille*taille));
	}

   
	
