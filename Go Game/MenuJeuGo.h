/** ******** Interface menu de jeu ******** **
 *
 * => classe qui represente le menu de jeu
 * => declaraton :
 *               - des attributs
 *               - les fonctions membres
 *               - les signals et les slots
 *
 *********************************************/

#ifndef MENUJEUGO_H
#define MENUJEUGO_H

#include<QPushButton>
#include"JeuGoView.h"
#include"InfoView.h"
#include"ReglesGo.h"
#include"ParametresView.h"

#include <QLabel>
#include <QMainWindow>

// classe Menu de jeu qui herite  de QMainWindow
class MenuJeuGo : public QMainWindow
{
    Q_OBJECT
/** les fonctions membre **/
public:
    //Constructeur de menu avec: classe parente
    explicit MenuJeuGo(QWidget *parent = nullptr);
    //Destructeur de menu
    ~MenuJeuGo();
    //initilaiser les composantes de menu avec : dimensions de la fenetre
    void initComposantes(int larg,int haut);
    //Evenement de fermeture
    void closeEvent(QCloseEvent *event);

/** **** Signals **** **/
public slots:
    //Afficher la fenêtre des paramètres
    void lancerParametres();
    //lancer une partie de jeu avec:  taille du goban,type de partie, noms des joueurs et nombre des handicaps
    void lancerPartie(int dim,int type,QVector<QString> noms,int hand=0);
    //Consulter les informations de l'application
    void consulterInfo();
    //Consulter les règles de jeu
    void consulterRegles();
    //état de choix des paramètres
    void paramChoisie(bool val);


/** **** les attributs **** **/
private:
    //Les buttons de menu
    QPushButton *buttonJouer,*buttonInfo,*buttonRegles,*buttonQuitter;
    //Label du logo
    QLabel *label;
    //Les widgets: widget centrale et widgets des buttons
    QWidget *centralWidget,*widget;
    //objet de la classe paramètres
    ParametresView *parametres;
    //objet de la classe des informations
    InfoView *info;
    //objet de la classe de règles
    ReglesGo regles;
    //objet de la classe de jeu
    JeuGo *jeu;

};

#endif // MENUJEUGO_H
