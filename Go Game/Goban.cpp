
#include "Goban.h"
#include "Chaine.h"
#include <iomanip>
#include <unistd.h>
    /** constructeur du goban :
     * initiliser les différents attributs à travers une liste d'initilisation
     **/
    Goban::Goban(int dim):
        taille(dim),casePleines(0),Plateau(dim,vector<Piece> (dim,Piece())),
        joueurs({Joueur(NOIR),Joueur(BLANC)}),
        joueurActuel(0),etatJeu(false),estHandicap(false),gobanRep(2,nullptr)
    {
        //initialiser le goban
        setGoban();
        //sauvegardes des états des gobans
        gobanRep[0]=new Goban(*this);
        gobanRep[1]=new Goban(*this);
        etatCapt[0]=etatCapt[1]=false;
	}
    /** constructeur par copie du goban **/
    Goban::Goban(Goban & goban):taille(goban.getTaille()),casePleines(goban.casePleines),
        Plateau(goban.Plateau),joueurs(goban.joueurs),joueurActuel(goban.joueurActuel),etatJeu(true),estHandicap(goban.estHandicap)
    {

    }

    const Goban& Goban::getGoban(){
        return *this;
    }

    /** modifier la taille du goban **/
    void Goban::setTaille(int dim)
	{
		this->taille = dim;
	}

    /** récupérer la taille du goban **/
	int Goban::getTaille()
	{
		return taille;
	}


    vector<vector<Piece>>& Goban::getPlateau(){
        return Plateau;
    }

    /** récupérer les joueurs **/
    vector<Joueur>& Goban::getJoueurs(){
           return joueurs;
    }

    /** récupérer le joueur courant **/
    int Goban::getJoueurActuel(){
           return joueurActuel;
    }

    /** récupérer la pièce dans la position intersection (x,y) **/
    Piece* Goban::getPiece(int x,int y){
        if(!caseHorsBorne(x,y))//test de validité de l'intersection
            return &Plateau[x][y];
        return NULL;
    }

    /** tester si les coordonnées (i,j) sont dans les limites du goban **/
    bool Goban::caseHorsBorne(int i, int j ){
		if( i >= 0 && i < taille && j >= 0 && j < taille ){
			return false;
		}
		return true;
	}

    /** tester si intersection/pièce (i,j) est de la couleur coul **/
    bool Goban::caseValide(int i, int j,char coul)
    {
        if(!caseHorsBorne(i,j) && Plateau[i][j].getCouleur()== coul) return true;
        else
            return false;
    }

    /** récupérer le nombre des cases/intersections pleines **/
    int Goban::getCasesPleines(){
        return casePleines;
    }

    /** incrémenter le nombre desintersections pleines **/
    void Goban::incrCasePleine(int n){
        if(casePleines<(taille*taille))
            casePleines+=n;
    }

    /** décrémenter le nombre desintersections pleines **/
    void Goban::decrCasePleine(int n){
        if(casePleines>0)
            casePleines-=n;
    }

    /** initialiser le goban **/
    void Goban::setGoban()
    {	// parcourir les lignes
		for(int i=0;i<taille;i++){
        // parcourir les colonnes
            for(int j=0;j<taille;j++){
                // initiliser la ligne et la collone de la piece (i,j)
				Plateau[i][j].setIndiceLigne(i);
				Plateau[i][j].setIndiceCol(j);
			}
		}	
	}

    /** affichage du goban **/
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
					cout<<&Plateau[i][j];
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

    /** changement du tour de jeu **/
	void Goban::tourJoueur()
	{
		joueurActuel=(joueurActuel+1)%2;
	}

    /** calcul des libértés d'une pièce (i,j)**/
    int Goban::compterDegLib(int i, int j){
		int n=0;
        //intersecion à gauche
        if( (j-1) >= 0  	&&	Plateau[i][j-1].getCouleur() == VIDE )	n++;
        //intersecion à droite
        if( (j+1) < taille 	&& 	Plateau[i][j+1].getCouleur() == VIDE )	n++;
        //intersecion en haut
        if( (i-1) >= 0 		&& 	Plateau[i-1][j].getCouleur() == VIDE )	n++;
        //intersecion en bas
        if( (i+1) < taille 	&& 	Plateau[i+1][j].getCouleur() == VIDE ) 	n++;
        return n;
	}

    /** verifier si le joueur veut commencer une partie aléatoire **/
    bool Goban::jeuEnMilieuPartie()
    {
        srand(time(NULL));
        //test si le goban et d'une taille standard: 9,13 ou 19
        if(taille!=DIM_GOB_PET && taille!=DIM_GOB_MOY && taille!=DIM_GOB_NOR  )
            return false;
        char rep;
        do{
        
        cout << "Voulez-vous commencer en milieu de partie (o/n) : " << endl;
        cin >> rep;
        }while(rep != 'o' && rep != 'n');
        if(rep == 'n') return false;
        else return true;
    }

    /** générer des pièces aléatoires avant de commencer le jeu **/
    vector<vector<int>>* Goban::jeuAleatoire()
    {
        int i, j;
       //nombre des pièces à générer
       int nMax=(taille+1)*taille/3;
       if(nMax%2==1)
           nMax++;
       //vector des coordonnés des pièces à generer
        vector<vector<int>> *liste=new vector<vector<int>>();
        do{
            do{
                i = rand()%taille;
                j = rand()%taille;
            }while(caseHorsBorne(i,j) || !caseValide(i,j));
            vector<Chaine> chAdv;
            Chaine::genererChaines(i,j,*this,chAdv);
            //test sur capture et suicide
            if(!testSuicide(i,j)&&!Chaine::testCapture(chAdv)){
                //ajout de la pièce zu goban et la liste des coordonnées
                liste->push_back(vector<int>({i,j,joueurActuel}));
                poserPiece(i,j);
                nMax--;
            }
        } while(nMax>0);
        //sauvegardes des états des gobans
        delete gobanRep[0];
        delete gobanRep[1];
        gobanRep[0]=new Goban(*this);
        gobanRep[1]=new Goban(*this);
        etatCapt[0]=etatCapt[1]=false;

        //retourner la liste des pieces generees
        return liste;
    }

    /** test de suicide à une intersection **/
    bool Goban::testSuicide(int i, int j){
        //générer le chaine de même couleur
        Chaine chaine(*this,joueurs[joueurActuel].getCouleur(),i,j);
         //test de suicide pour la chaine générée
        return chaine.estSuicide();
    }

    /** vérifier si le joueur noir veut commencer une partie handicaps  en mode console**/
    bool Goban::gestionHandicap(){
        if(taille!=DIM_GOB_PET && taille!=DIM_GOB_MOY && taille!=DIM_GOB_NOR  )
            return false;
        char c;
        do{
            cout<<"Voulez vous jouer une partie à Handicapes? ( o / n) : ";
            cin>>c;;
            if(c=='n'||c=='N'){
                return false;
            }
        }while(c!='n' && c!='N' && c!='o' && c!='O');
        unsigned int handMax=(taille==DIM_GOB_PET?MAX_HAN_PET:(taille==DIM_GOB_MOY)?MAX_HAN_MOY:MAX_HAN_NOR),hand=0;
        //vector<vector<unsigned int>> &tab=(taille==DIM_GOB_PET?HAN_POS_PET:(taille==DIM_GOB_MOY)?HAN_POS_MOY:HAN_POS_NOR);
        //vector<Piece *> pos;

        do{
            cout<<"Choisir le nombre de pieces handicapes ( min 2 - max "<<handMax<<" ) : ";
            cin>>hand;
        }while( (hand<2) ||( hand>handMax));
        partieHandicap(hand);
        affichage();
        /*while(pos.size()!=hand){
            pos.resize(0,NULL);
            cout<<"Veuillez valider les positions des pieces handicapes : ( Oui : o / Non : n ) "<<endl;
            for(unsigned int i=0;pos.size()<hand && i<handMax;i++){
                char c='n';
                cout<<"Intersection {"<<tab[i][0]+1<<","<<tab[i][1]+1<<"} ==> ";
                cin>>c;;
                if(c=='o'||c=='O'){
                    pos.push_back(getPiece(tab[i][0],tab[i][1]));
                }
            }
        }*/

        return true;
    }

    /** initailiser le pièces handicaps **/
    vector<vector<unsigned int>>& Goban::partieHandicap(int hand){
        estHandicap=true;
        vector<vector<unsigned int>> &tab=(taille==DIM_GOB_PET?HAN_POS_PET:(taille==DIM_GOB_MOY)?HAN_POS_MOY:HAN_POS_NOR);
        for(int i=0;i<hand;i++){
           Plateau[tab[i][0]][tab[i][1]].setCouleur(NOIR);
        }
        joueurs[0].incrTeritoire(hand);
        joueurs[1].setCapture(hand-1);
        incrCasePleine(hand);
        tourJoueur();
        //sauvegardes des états des gobans
        delete gobanRep[0];
        delete gobanRep[1];
        gobanRep[0]=new Goban(*this);
        gobanRep[1]=new Goban(*this);
        etatCapt[0]=etatCapt[1]=false;
        return tab;
    }

    /** gérer une partie de jeu en mode console **/
    int Goban::gestionPartie()
    {
        if(etatJeu==false)
        {
            if(jeuEnMilieuPartie())
                jeuAleatoire();
            else 
                gestionHandicap();
        }

        CLEAR;
        int etatPasse=0;
		do{
        //sleep(3);
            //chaines des pièces adverses
          vector<Chaine> chainesAdv;
          bool etat=false;//état de suicide
          int i,j;
          //int comptvalide = 0; int comptsuicide = 0; 
           affichage();
           cout<<endl<<"Tour du Joueur "<<joueurs[joueurActuel].getCouleur()<<"\t";
          do{

                i=-1,j=-1;
                do{
                    cout<<endl << "Choix position (0 0 pour passer tour) ==> (x, y) =  ";
                    cin>>i;
                    cin>>j;
                    /*i = rand()%taille + 1;
                    j = rand()%taille + 1; 

                    cout<<endl<<"Position (x,y) = (" << i << ", " << j << ")" << endl;

                    if(comptsuicide == 20 || comptvalide == 20)
                    {
                        i = 0; j = 0;
                    }*/
                    
                    if(i==0&&j==0){
                        etatPasse++;
                        break;
                    }
                    etatPasse=0;
                    i--;j--; 
                    //comptvalide++;
                }while(caseHorsBorne(i,j) || !caseValide(i,j));

                if(etatPasse>0)
                    break;
                etat=testSuicide(i,j);
                if(etat)
                {
                    //comptsuicide++;
                    cout<<"Coup interdit : Suicide !!"<<endl;
                }
                else{
                    Chaine::genererChaines(i,j,*this,chainesAdv);
                }
            }while(etat);
           //test sur le passe de tour
            if (etatPasse==1){
              tourJoueur();
              continue;
            }
            if(etatPasse==2){
              break;
            }

            //tester si les chaines adj adverses sont des capturées
            if(Chaine::testCapture(chainesAdv)){
                for(Chaine ch:chainesAdv){
                    if(ch.estCapture()){
                        ch.viderChaine();
                     }
                }
            }
            chainesAdv.clear();
            poserPiece(i,j);
            //tourJoueur();
		}while(casePleines<(taille*taille));
        affichage();
        float sn=joueurs[0].calculScore(),sb=joueurs[1].calculScore(estHandicap);
        cout<<"=========================="<<endl;
        cout<<"Noir : "<<setprecision (4)<< sn << endl; 
        cout << "Blanc : " <<setprecision (4) << sb << endl;
        cout<<"=========================="<<endl;

        if(sn==sb)
            cout<<"Egalité"<<endl;
        else
            cout<<"Le gagnant est: "<<(sn>sb?"NOIR":"BLANC")<<endl;
        if(sn > sb) return 10;
        else return -10;
	}

    /** ajouter une pièce au goban **/
    void Goban::poserPiece(int i,int j){
        Plateau[i][j].setCouleur(joueurs[joueurActuel].getCouleur());
        Plateau[i][j].setDegLiberte(compterDegLib(i,j));
        incrCasePleine();
        joueurs[joueurActuel].incrTeritoire();
        tourJoueur();
    }

    /** suprimer/enlever une pièce du goban **/
    void Goban::supprimerPiece(int i,int j){
      Plateau[i][j].setCouleur(VIDE);
      Plateau[i][j].setDegLiberte(compterDegLib(i,j));
      decrCasePleine();
      joueurs[(joueurActuel+1)%2].decrTeritoire();
      joueurs[joueurActuel].setCapture(1);
  }

    /** récuperer la couleur adverse d'une pièce **/
    char Goban::pieceAdverse(char coul)  {
		if (coul == NOIR)
			return BLANC;
		else if(coul == BLANC)
			return NOIR;
		else
			return VIDE;

	}

    /** sauvegarde du goban pour  joueur courant **/
    void Goban::sauvGoban(){
        delete gobanRep[(joueurActuel+1)%2];
        gobanRep[(joueurActuel+1)%2]=new Goban(*this);
    }

    /** sauvegarde d'état de capture pour joueur courant **/
    void Goban::sauvEtatCapt(bool etat){
        etatCapt[joueurActuel]=etat;
    }

    /** test de répétition pour le joueur courant**/
    bool Goban::testRepetition(int x,int y){
       gobanRep[joueurActuel]->affichage();
       if(etatCapt[(joueurActuel+1)%2] && gobanRep[joueurActuel]->Plateau[x][y].getCouleur()==joueurs[joueurActuel].getCouleur())
            return true;
        return false;
    }
