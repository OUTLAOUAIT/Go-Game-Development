
#include "Joueur.h"
/** constructeur: liste d'initilisation des attributs **/
Joueur::Joueur(char coul):couleur(coul),capture(0),teritoire(0){
}
/** modifier la couleur joueur **/
void Joueur::setCouleur(char couleur)
{
    this->couleur = couleur;
}
/** récupération de la couleur du joueur **/
char Joueur::getCouleur()
{
    return couleur;
}
/** calcul de score d'un joueur **/
float Joueur::calculScore(bool handicap){
    // somme des pièces captures et celle sur goban
    float score=getCapture()+getTeritoire();
    //pour un joueur blanc
    if(couleur==BLANC){//ajout de komi
        score+=KOMI;
        //pour une partie handicap
        if(handicap)//ajout de nombre des pieces handicaps-1
            score+=HANDI;
    }
    //retourner le score totale
    return score;
}
/** modifier le nombre des pièces  capturées **/
void Joueur::setCapture(int capture){
    //incrémentation nombre par capture
    this->capture += capture;
}
/** récupérer le nombre des pièces  capturées **/
int Joueur::getCapture(){
    return this->capture;
}
/** incrémenter le nombre des pièces sur goban **/
void Joueur::incrTeritoire(int nbrPiece){
    this->teritoire+=nbrPiece;
};
/** décrémenter le nombre des pièces  sur goban**/
void Joueur::decrTeritoire(int nbrPiece){
    this->teritoire-=nbrPiece;
}
/** récuperer le nombre des pièces  sur goban **/
int Joueur::getTeritoire(){
    return this->teritoire;
}

/********************************/
/*void Joueur::choixPosition(int & i,int & j)
    {
        cout<<endl<<"Choix position (ligne,colonne) :  ";
        cin>>i;
        cin>>j;
    }*/
/********************************/

