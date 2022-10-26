/** ************** Interface de jeu ************ **
 *
 * => classe de l'interface principale de jeu
 * => declaraton :
 *               - des attributs
 *               - les fonctions membres
 *               - les signals et les slots
 *
 **************************************************/
#ifndef JEUGO_H
#define JEUGO_H
#include "GobanView.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

// classe Jeu qui hérite  de QMainWindow
class JeuGo : public QMainWindow
{
    Q_OBJECT

public:
    // Constructeur avec : taille du goban, noms des joueurs et classe parente
    JeuGo(int dim,QVector<QString> noms,QWidget *parent = nullptr);
    //Destructeur
    ~JeuGo();
    //Initialisations des composantes
    void initComposantes();
    //Evénement de fermeture
    void closeEvent(QCloseEvent *event);
private:
    //dimension du goban
    int dim;
    //état de jeu
    bool etat;
    //Objet de interface de plateau de jeu
    GobanView *goban;
    //Imges des pièces de jeu
    QPixmap *imgPiece[2];
   //Noms des joueurs
    QVector<QString> noms;
    //widget centrale
    QWidget *centralwidget;
    //gestionnaires de postionnement
    QGridLayout *gridLayout; /* pour la fenêtre de jeu */
    QHBoxLayout *horizontalLayout,*horLay; /*pour les indications de jeu: captures, tour de jeu */
    //Les labels des indications de jeu
    QLabel *labelTour, *labelTourImg,*labCapt,*iconCapt,*labj1,*labj2,*labcap1,*labcap2,*labSuic,*lab1,*lab2;
    //Les buttons : passer tour et retour au menu
    QPushButton *passerTour,*retour;

/** ***** slots ***** **/
public slots:
    // affichage de tour deu joueur: indice du joueur actuel
    void afficherTour(int joueur);
    // affichage des captures : nombres des captures
    void etatCapture(int n,int b);
    // affichage d'indication sur coup interdit : etat de suicide ou non
    void etatSuicide(bool val);
    // fin de partie : scores des 2 joueurs
    void finPartie(float sn,float sb);
/** ***** signals ***** **/
signals :
    /* indiquer le type de partie */
    //partie handicaps
    void partieHandicap(int n);
    //partie aléatoire
    void partieAletoire();
    /******************************/
    //passe de tour
    void passeTour(int val);
    //retour au menu
    void retourMenu();

};
#endif // JEUGO_H
