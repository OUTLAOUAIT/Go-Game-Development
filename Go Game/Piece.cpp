#include "Piece.h"

/** constructeur : liste d'initilisation des attributs **/
Piece::Piece(int l,int c,char couleur):
    i(l),j(c),degLib(0),couleur(couleur){
}
/** modifier la ligne de la pièce **/
void Piece::setIndiceLigne(int i){

    this->i = i;
}
/** modifier la colonne de la pièce **/
void Piece::setIndiceCol(int j){
    this->j = j;
}
/** récupérer la ligne de la pièce **/
int Piece::getIndiceLigne(){
    return i;
}
/** récupérer la colonne de la pièce **/
int Piece::getIndiceCol(){
    return j;
}
/** modifier le degré de liberté de la pièce **/
void Piece::setDegLiberte(int degLib){
    this->degLib = degLib;
}
 /** récupérer le degré de libérté de la pièce **/
int Piece::getDegLiberte(){
    return degLib;
}

/** modifier la couleur de la pièce **/
void Piece::setCouleur(char couleur){

    this->couleur = couleur;
}
/** récupérer la couleur de la pièce **/
char Piece::getCouleur(){
    return couleur;
}


