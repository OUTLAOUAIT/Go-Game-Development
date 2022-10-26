/** ******** Interface menu de jeu ******** **
 *
 *  Implémentation des fonctions
 *
 *********************************************/

#include "MenuJeuGo.h"
#include "JeuGoView.h"
#include "InfoView.h"
#include "ParametresView.h"
#include "ReglesGo.h"
#include "ConstantesOS.h"

#include <QGuiApplication>
#include <QScreen>
#include <QDebug>

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
#include <QCloseEvent>


/** ********** Constructeur ********** **
 *
 * @param:  parent => objet parent
 * <liste d'initialisation des attributs>
 *
 * **************************************/
MenuJeuGo::MenuJeuGo(QWidget *parent) :
    QMainWindow(parent),parametres(nullptr),info(new InfoView(this)),regles(this),jeu(nullptr)
{
    //Dimensions disponibles de l'écran
    QSize a=QGuiApplication::screens()[0]->size();
    //initialisation des composantes 
    if(VERSION!=2){ //version mobile
        initComposantes(2*a.width()/5,a.height()/2);
    }else{          //version bureau
        initComposantes(a.width(),a.height());
    }
    //icon de l'application
    setWindowIcon(QIcon(":/icon/icongo"));
    //positionnement au milieu de l'ecran
    this->move((a.width()-width())/2,(a.height()-height())/2);
    /** précision des événements au click des buttons **/

    /* button jouer : affiche la fenêtre des paramètres */
    connect(buttonJouer,&QPushButton::clicked,this,&MenuJeuGo::lancerParametres);
    /* button à propos : affiche la fenêtre des informations */
    connect(buttonInfo,&QPushButton::clicked,this,&MenuJeuGo::consulterInfo);
    /* button règles : affiche la fenêtre des règles de jeu */
    connect(buttonRegles,&QPushButton::clicked,this,&MenuJeuGo::consulterRegles);
    /* button quitter : fermer la fenêtre et quitter l'application  */
    connect(buttonQuitter,&QPushButton::clicked,this,&MenuJeuGo::close);
}

/** Destructeur **/
MenuJeuGo::~MenuJeuGo()
{
    //libération des ressources allouées
    delete info;
    delete jeu;
    delete buttonJouer;
    delete buttonInfo;
    delete buttonRegles;
    delete buttonQuitter;
    delete label;
    delete widget->layout();
    delete widget;
    delete centralWidget->layout();
    delete centralWidget;

}

/** initialisation des composantes de menu **
 *
 * @param:  int larg => largeur de la fenêtre
 *          int haut => hauteur de  la fenêtre
 *
 * **************************************/
void MenuJeuGo::initComposantes(int larg,int haut){
    //titre de la fenêtre
    this->setWindowTitle("Jeu Go - Menu");
    //Redimensionner la fenêtre : une taille fixe
    setFixedSize(larg,haut);
    //alignement des composantes
    layout()->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    /** la widget centrale **/
    //initialisation
    centralWidget = new QWidget(this);
    //précision des dimensions
    centralWidget->setMinimumSize(500,DIM_LAB);
    //précision du style des composantes : en utilisant CSS (d=feuile de style en cascade )
    centralWidget->setStyleSheet(QString::fromUtf8("QWidget{\n"
                                                   "background-color:rgb(211, 215, 207);}\n"
                                                   "QPushButton{\n"
                                                   "    text-align: left;\n"
                                                   "    font: 75 italic 18pt \"Uroob\";\n"
                                                   "    background-color: rgb(136, 138, 133);\n"
                                                   "    color:rgb(0, 0, 0);\n"
                                                   "}"));

    /** widget des buttons **/
    //initialisation
    widget = new QWidget(centralWidget);
    //gestionnaire de positionnement : vertical
    widget->setLayout(new QVBoxLayout);


    /** **** les buttons de menu **** **
     *
     *  initialisation : texte et icon
     *  dimensions de l'icon
     *  dimensions minimales
     *
     ** ***************************** **/

    /* dimension des icons des buttons */
    int dimIcoBut=VERSION==2?50:40;
    QSize size(dimIcoBut,dimIcoBut);

    /* button jouer */
    buttonJouer = new QPushButton(QIcon(":/icon/jouer"),"Jouer",widget);
    buttonJouer->setIconSize(size);
    buttonJouer->setMinimumSize(120,size.height());;

    /* button règles */
    buttonRegles = new QPushButton(QIcon(":/icon/regles"),"Regles",widget);
    buttonRegles->setIconSize(size);
    buttonRegles->setMinimumSize(120,size.height());;

    /* button à propos */
    buttonInfo = new QPushButton(QIcon(":/icon/info"),"A propos",widget);
    buttonInfo->setIconSize(size);
    buttonInfo->setMinimumSize(120,size.height());;

    /* button quitter */
    buttonQuitter = new QPushButton(QIcon(":/icon/quitter"),"Quitter",widget);
    buttonQuitter->setIconSize(size);
    buttonQuitter->setMinimumSize(120,size.height());

    /** l'ajout des buttons au widget **/
    //dimension des spacers
    int e=20;
    //l'ajout d'un spacer
    widget->layout()->addItem(new QSpacerItem(e, e, QSizePolicy::Minimum, QSizePolicy::Expanding));
    //l'ajout du button jouer
    widget->layout()->addWidget(buttonJouer);
    //l'ajout d'un spacer
    if(VERSION==2)// cas de mobile
        widget->layout()->addItem(new QSpacerItem(e, e, QSizePolicy::Minimum, QSizePolicy::Expanding));
    //l'ajout du button règles
    widget->layout()->addWidget(buttonRegles);
    //l'ajout d'un spacer
    if(VERSION==2)// cas de mobile
        widget->layout()->addItem(new QSpacerItem(e, e, QSizePolicy::Minimum, QSizePolicy::Expanding));
    //l'ajout du button à propos
    widget->layout()->addWidget(buttonInfo);
    //l'ajout d'un spacer
    if(VERSION==2)// cas de mobile
        widget->layout()->addItem(new QSpacerItem(e, e, QSizePolicy::Minimum, QSizePolicy::Expanding));
    //l'ajout du button quitter
    widget->layout()->addWidget(buttonQuitter);
    //l'ajout d'un spacer
    widget->layout()->addItem(new QSpacerItem(e, e, QSizePolicy::Minimum, QSizePolicy::Expanding));

    /** label de logo **/

    //initialisation
    label = new QLabel(centralWidget);
    //dimensions fixes
    label->setFixedSize(DIM_LAB,DIM_LAB);
    //alignement du contenu
    label->setAlignment(Qt::AlignCenter);
    //corespondance entre dimensions de l'abel et le logo
    label->setScaledContents(true);
    //l'ajout du logo
    label->setPixmap(QPixmap(":/icon/aplana"));

    /** gestionnaire de positionnement de la widget centrale **/

    // version bureau

    if(VERSION==1){
        /* layout horizontal */
        centralWidget->setLayout(new QHBoxLayout());
        /* alignement centré */
        centralWidget->layout()->setAlignment(Qt::AlignHCenter);
    }

    // version mobile

    else if(VERSION==2){
        /* layout vertical */
        centralWidget->setLayout(new QVBoxLayout());
        /* alignement centré */
        centralWidget->layout()->setAlignment(Qt::AlignVCenter);
    }

    /** ajout des composantes **/
    //l'ajout d'un spacer
    centralWidget->layout()->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    //l'ajout de label du logo
    centralWidget->layout()->addWidget(label);
    //l'ajout d'un spacer
    centralWidget->layout()->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    //l'ajout de widget des buttons
    centralWidget->layout()->addWidget(widget);
    //l'ajout d'un spacer
    centralWidget->layout()->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    /** spécification de la widget centrale de la fenêtre **/
    setCentralWidget(centralWidget);

}

/** * lancer une nouvelle partie de jeu * **
 *
 * @param:  int dim => dimension du goban
 *          int type => type de la partie
 *          QVector<QString> noms => noms des joueurs
 *          int hand => nombre des pieces handicaps
 *
 * ****************************************/
void MenuJeuGo::lancerPartie(int dim,int type,QVector<QString> noms,int hand){
   //cacher le menu
   this->hide();
   // création de l'objet jeu
   delete jeu;
   jeu = new JeuGo(dim,noms,this);
   //initilaisation la partie
   switch(type){
       case 2://partie aléatoire
           emit jeu->partieAletoire();
           break;
       case 3://partie à handicaps
           emit jeu->partieHandicap(hand);
           break;
       default: break;
   }
   //affichage de la fenêtre de jeu
   jeu->show();
}

/** * lancer la fenêtre de choix des parametres * **/
void MenuJeuGo::lancerParametres(){
    this->hide();
    delete parametres;
    parametres=new ParametresView(this);
    parametres->show();
    connect(parametres,&ParametresView::nouvellePartie,this,&MenuJeuGo::lancerPartie);
    connect(parametres,&ParametresView::annulPartie,this,&MenuJeuGo::paramChoisie);

}

/** * état de choix de parametres *
 *
 * @param:  bool val => paramètres ou annulées ou non
 *
 * ****************************************/
void MenuJeuGo::paramChoisie(bool val){
    //cacher la fenêtre de paramètres
    parametres->hide();
    if(val){
        //true: retour au menu principal , false : fenêtre de jeu
        //affichage du menu
        this->show();
        //libérer l'objet de paramètres
        delete parametres;
        parametres =nullptr;
    }

}

/** * affichage de la fenètre des informations * **/
void MenuJeuGo::consulterInfo(){
    //cacher le menu
    this->hide();
    //affichage des informations
    info->show();
}

/** * affichage de  la fenêtre des règles * **/
void MenuJeuGo::consulterRegles(){
     //cacher le menu
    this->hide();
    //affichage des règles
    regles.show();
}

/** ************ événement de fermeture ************ *
 *
 * @param:  QCloseEvent *event => événement de cloture
 *
 * ***************************************************/
void MenuJeuGo::closeEvent(QCloseEvent *event){
    //boite de dialogue de type confirmation
    QMessageBox msgConf(QMessageBox::Warning,"Confirmation","Voulez vous quitter le jeu ?",QMessageBox::NoButton,this);
    //spécification du style
    msgConf.setStyleSheet(this->centralWidget->styleSheet());
    /* l'ajout des buttons */

    //button d'annulation
    msgConf.addButton(QMessageBox::Cancel);
    //button de confirmation
    msgConf.addButton(QMessageBox::Ok);
    //affichage de boite de confirmation
    msgConf.exec();
    /* test sur la réponse choisie */
    //confirmation de fermeture
    if(msgConf.clickedButton()==msgConf.buttons()[0]){
        //acceptation de l'événement
        event->accept();
    }
    //annulation de fermeture
    else {
        //ignorer l'événement
        event->ignore();
    }
}
