#ifndef CHAINE_H
#define CHAINE_H
#include <iostream>
#include <vector>
#include "Couleur.h"
#include "Goban.h"
#include "Piece.h"
#include "Joueur.h"
using namespace std;
class Chaine
{
    //chaine des pièces voisines à la pièce (srcX,srcY)
    vector< Piece* > chaine;
    //degré de libérté
    int degLiberte;
    //couleur de la pièce
    char joueur;
    //référence du Goban
    Goban & plateau;
    //coordonnes sur le goban
    int srcX,srcY;
    public:
    //constructeur
    Chaine(Goban & plateau,char joueur,int x,int y,int d=0);

    //MAJ de la chaine
    void updateChaine(int x,int y);
    //affichagee de la chaine
    void afficher();
    //pour récupérer la chaine
    vector<Piece *>& getChaine();

    //pour enlever les pièces de la chaine du goban
    int viderChaine();
    //reinitialiser la chaine
    void resetChaine();

    //calcul de degré de libérté de la chaine
    int compterDegLiberte();
    //savoir l'indice d'une pièce dans la chaine
    int getIndice(Piece *p);

    //si une chaine est connectée ou non
    bool estConnecte();
    //test si une pièce(x,y) appartient à la chaine
    bool existePiece(int x,int y);
    //tester si la pièce soure est en cas de suicide
    bool estSuicide();
    //tester si la chaine peut être capturée
    bool estCapture();
    //récupérer les chaines adjacentes a une piéce
    /*
     * val == false : chaines adverse
     * val == true : chaines dde meme couleur
     */
    static void genererChaines(int i,int j,Goban &goban,vector<Chaine> &chaines,bool val=false);

    //test pour capturer des pièces
    static bool testCapture(vector<Chaine> &chainesAdv);
};

#endif // CHAINE_H
