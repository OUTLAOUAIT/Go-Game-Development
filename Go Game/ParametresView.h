/** ********** Interface de parametres ********** **
 *
 * => classe de l'interface de parametres de jeu
 * => declaraton :
 *               - des attributs
 *               - les fonctions membres
 *               - les signals et les slots
 *
 ***************************************************/

#ifndef PARAMETRESVIEW_H
#define PARAMETRESVIEW_H

#include <QMainWindow>
#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>

#include <QMessageBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>

// classe Paramètres de jeu qui hérite de QMainWindow
class ParametresView : public QMainWindow
{
    Q_OBJECT

/** les fonctions membre **/
public:
    //Constructeur avec : classe parente
    explicit ParametresView(QMainWindow *parent = nullptr);
    //Destructeur
    ~ParametresView();
    //Initialiser les composantes
    void initComposantes();
    //Evénement de fermeture
    void closeEvent(QCloseEvent *event);

/** **** Signals **** **/
signals:
    //indiquer une nouvelle partie :taille du goban,type de partie, noms des joueurs et nombre des handicaps
    void nouvellePartie(int dim,int type,QVector<QString>noms ,int hand);
    //indiquer l'annulation de commencement de partie
    void annulPartie(bool val);

/** **** les attributs **** **/
private:
    // taille du goban, type de partie, nombre des handicaps
    int dim,type,hand;
    // widget centrale
    QWidget *centrWid ;
    /* gestionnaires de positionnement */
    QGridLayout *lay;             /* Pour la fenetre */
    QVBoxLayout *dimLay,*typeLay; /* pour les types et les tailles */
    QHBoxLayout *bLay;            /* pour les buttons */
    QFormLayout *nomLay;          /* pour les noms*/
    /***********************************/
    // groupes des composantes
    QGroupBox *grpNom, *grpDim,*grpType;
    // groupes des buttons radio
    QButtonGroup *rgbDim,*rgbType;
    //Labels pour les noms(indications couleurs)
    QLabel *labN1,*labN2;
    //les buttons
    QPushButton *bAnnul,*bConf;
    //champs de saisie des noms
    QLineEdit *nomJ1,*nomJ2;
    //cjamps de choix des handicaps
    QSpinBox *nbrHand;
    // les radios buttons
    QRadioButton *d1,*d2,*d3,*t1,*t2,*t3;

};

#endif // PARAMETRESVIEW_H
