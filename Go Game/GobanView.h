/** ****** Interface de plateau de jeu ****** **
 *
 * => classe qui presente le goban de jeu
 * => declaraton :
 *               - des attributs
 *               - les fonctions membres
 *               - les signals et les slots
 *
 ************************************************/

#ifndef GOBANVIEW_H
#define GOBANVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "Goban.h"

// classe Informations de jeu qui hérite  de QGraphicsView
class GobanView : public QGraphicsView
{
    Q_OBJECT

/** les fonctions membres **/
public:
    //constructeur: dimension, largeur et objet parent
    explicit GobanView(int dim,int larg,QWidget *parent = nullptr);
    //destructeur
    ~GobanView();
    //initilaiser le plateau
    void setGoban();
    //conversion d'intersection en position
    int* intersToPos(int x,int y);
    //conversion de position en intersection
    int* posToInters(int posX,int posY);
    //modifier l'état de jeu
    void setEtat(bool value);
    //événement de mouvement de souris
    void mouseMoveEvent(QMouseEvent *event);
    //événement de click de souris
    void mousePressEvent(QMouseEvent* event);

/** les attributs **/
private:
    //le goban de jeu
    Goban * goban;
    //la scene graphique
    QGraphicsScene *scene;
    //les images des pièces
    QVector< QString> pieceImg;
    //les pièces de jeu
    QVector<QVector<QGraphicsPixmapItem *>> pieces;
    //les pièces d'indications
    QGraphicsPixmapItem *item[2];
    //dimension du goban
    int dim;
    //marge du plateau, espace entre intersections ,dimension de pièces
    int marge,esp,pix;
    //nombre de passe
    int passe;
    //état de partie de jeu, état de pièce d'indication
    bool etat,indPiece;

/** les slots **/
public slots:
    // afficher une pièce sur le plateau
    void afficherPiece(int x,int y,int i);
    // supprimer une pièce du plateau
    void supprimerPiece(int x,int y);
    // passer le tour
    void tourPasse();
    // initialiser une partie à handicaps
    void partieHandicap(int n);
    // initialiser une partie aléatoire
    void partieAleatoire();

/** les signals **/
signals:
    //indique le changement de tour
    void tourChange(int joueur);
    //indique la fin de partie
    void finPartie(float sn,float sb);
    //indique le changement de captures
    void majCapture(int n,int b);
    //indiquer l'état de suicide
    void etatSuicide(bool val);
};
#endif // GABANVIEW_H
