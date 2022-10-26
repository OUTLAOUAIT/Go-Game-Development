/** ** Interface parametres de jeu ** **
 *
 *  Implémentations des fonctions
 *
 ***************************************/

#include "ParametresView.h"
#include "MenuJeuGo.h"
#include "ConstantesOS.h"
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QCloseEvent>

/** ********** Constructeur ********** **
 *
 * @param:   QWidget *parent => objet parent
 *  avec <liste d'initialisation des attributs>
 *
 * **************************************/
ParametresView::ParametresView(QMainWindow *parent) : QMainWindow(parent),dim(9),type(1),hand(2)
{
    //précision des dimensions de la fenêtre
    if(VERSION!=2){//version bureau
        this->setFixedSize(320,540);
    }
    else{//version mobile
        this->resize(QGuiApplication::screens()[0]->size());
    }
    //positionnement de la fenêtre au centre de l'écran
    this->move((QGuiApplication::screens()[0]->size().width()-this->width())/2,(QGuiApplication::screens()[0]->size().height()-this->height())/2);
    //initialisatin des composantes
    initComposantes();
    /** connexion des signals et slots **/
    /* bouttons de confirmation */
    //click button continuer
    connect(bConf,&QPushButton::clicked,this,[this]{
        //paramètre validées
        emit annulPartie(false);
        //nouvelle partie de jeu
        emit nouvellePartie(dim,type,{nomJ1->text(),nomJ2->text()},hand);

    });
    //click button annuler
    connect(bAnnul,&QPushButton::clicked,this,[this]{
        emit annulPartie(true);
    });
    /* bouttons radio de type de partie */
    //séléction type à handicaps
    connect(t3,&QRadioButton::toggled,this,[this]{
        //changer le type de partie vers partie à handicaps
        if(t3->isChecked()){
            type=3;
            //rendre le champs d'handicaps visible
            nbrHand->setHidden(false);
        }
        else{
            //rendre le champs d'handicaps invisible
            nbrHand->setHidden(true);
        }
    });
    //séléction type aléatoire
    connect(t2, &QRadioButton::toggled,this, [this] {
        //changer le type de partie vers partie aleatoire
        type=2;
    });
    //séléction type simple
    connect(t1, &QRadioButton::toggled,this,[this] {
        //changer le type de partie vers partie simple
        type=1;
    });
     /*modification de champs de nombre des pièces handicaps */
    connect(nbrHand,QOverload<int>::of(&QSpinBox::valueChanged), this,[this]{
        //affécter la valeur du champs au nombre des handicaps
        hand=nbrHand->value();
    });

    /* bouttons radio de taille de goban */
    //séléction taille 9
    connect(d1, &QRadioButton::toggled,this,[this] {
        //taille petite
        dim=9;
        //intervalle de choix des handicaps
        nbrHand->setRange(2,MAX_HAN_PET);
    });
     //séléction taille 13
    connect(d2, &QRadioButton::toggled,this,[this] {
        //taille moyenne
        dim=13;
        //intervalle de choix des handicaps
        nbrHand->setRange(2,MAX_HAN_MOY);
    });
    //séléction taille 19
    connect(d3, &QRadioButton::toggled,this,[this] {
        //taille grande
        dim=19;
        //intervalle de choix des handicaps
        nbrHand->setRange(2,MAX_HAN_NOR);
    });


}

/** destructeur **/
ParametresView::~ParametresView()
{
    /* libération des ressources allouées */
    //sections noms des joueurs
    delete labN1;
    delete labN2;
    delete nomJ1;
    delete nomJ2;
    delete nomLay;
    delete grpNom;
    //section choix de taille
    delete d1;
    delete d2;
    delete d3;
    delete dimLay;
    delete grpDim;
    delete rgbDim;

    //section chois de type
    delete t1;
    delete t2;
    delete t3;
    delete nbrHand;
    delete rgbType;
    delete typeLay;
    delete grpType;

    //bouttons  de confirmation
    delete bAnnul;
    delete bConf;
    delete bLay;

    //layouts et widget centrale
    delete lay;
    delete centrWid ;

}

/** initialisation des composantes **/
void ParametresView::initComposantes()
{
    /** widget centrale **/
    // initialisation
    centrWid = new QWidget();
    //style en cascade
    centrWid->setStyleSheet("QWidget{\n"
                            "background-color:rgb(186, 189, 182);"
                            "font: "+(QString::number(VERSION==2?18:14))+
                            "pt Uroob;}\n"
                            "QPushButton{\n"
                            "text-align: center;\n"
                            "background-color:rgb(136, 138, 133);\n"
                            "color:rgb(238, 238, 236);}\n"
                            "QLabel,QGroupBox,QRadioButton,QSpinBox,QLineEdit{\n"
                            "text-align: center;\n"
                            "color:rgb(0, 0, 0);\n"
                            "background-color:rgb(238, 238, 236);"
                            //"background-color:rgb(233, 185, 110);"
                            "}"
                            "QLineEdit,QSpinBox{background-color:rgb(255, 255, 255);}");
    this->setWindowTitle("Jeu de Go - Parametres");

    /** gestionnaires positionnement **/
    // fenêtre: grille
    lay=new QGridLayout();
    //groupe tailles et types : vertical
    dimLay=new QVBoxLayout(),typeLay=new QVBoxLayout();
    //bouttons : horizontal
    bLay=new QHBoxLayout();
    //groups noms : formulaire
    nomLay=new QFormLayout();

    /** groupes des composantes **/
    // noms
    grpNom=new QGroupBox("Noms des joueurs",centrWid);
    // les tailles
    grpDim=new QGroupBox("Taille du goban",centrWid);
    // les types
    grpType=new QGroupBox("Type de partie",centrWid);

    /** groupes de bouttons radio **/
    // les tailles
    rgbDim=new QButtonGroup(centrWid);
    // les types
    rgbType=new QButtonGroup(centrWid);

    /** les labels **/
    //indication nom joueur 1
    labN1=new QLabel("Noir");
    //indication nom joueur 2
    labN2=new QLabel("Blanc");

    /** les bouttons **/
    //boutton Annuler
    bAnnul=new QPushButton(QIcon(":/icon/quitter"),"Annuler");
    //dimensions d'icon Annuler
    bAnnul->setIconSize(QSize(24,24));
    //boutton Continuer
    bConf=new QPushButton(QIcon(":/icon/jouer"),"Continuer");
    //dimensions d'icon Continuer
    bConf->setIconSize(QSize(24,24));

    /** champs des noms **/
    //nom joueur 1 (noir)
    nomJ1=new QLineEdit("Joueur 1");
    //nom joueur 2
    nomJ2=new QLineEdit("Joueur 2");
    /** champ nombre handicaps **/
    //création
    nbrHand=new QSpinBox();
    //préfix
    nbrHand->setSuffix("  handicaps");
    //aignement
    nbrHand->setAlignment(Qt::AlignCenter);
    /** les bouttons radio **/
    //tailles du goban
    d1=new QRadioButton("   Petit - 9 * 9");
    d2=new QRadioButton("   Moyen - 13 * 13");
    d3=new QRadioButton("   Grand - 19 * 19");
    //types de partie
    t1=new QRadioButton("   Simple");
    t2=new QRadioButton("   Aléatoire");
    t3=new QRadioButton("   A handicaps");

    /** dimensions minimales des composantes **/
    QSize s(2*width()/3,30);
    t1->setMinimumSize(s);
    t2->setMinimumSize(s);
    t3->setMinimumSize(s);
    d1->setMinimumSize(s);
    d2->setMinimumSize(s);
    d3->setMinimumSize(s);
    nbrHand->setMinimumSize(s);
    nomJ1->setMinimumSize(s);
    nomJ2->setMinimumSize(s);
    labN1->setMinimumSize(s);
    labN2->setMinimumSize(s);
    bConf->setMinimumSize(s/2);
    bAnnul->setMinimumSize(s.width()/2,s.height());

    /**l'ajout des radio bouttons à groupes **/
    //groupe des tailles
    rgbDim->addButton(d1,1);
    rgbDim->addButton(d2,2);
    rgbDim->addButton(d3,3);
    //groupe des types
    rgbType->addButton(t1,1);
    rgbType->addButton(t2,2);
    rgbType->addButton(t3,3);

    /**l'ajout des composantes au groupes des composantes **/
    //groupe des noms
    nomLay->addWidget(labN1);
    nomLay->addWidget(nomJ1);
    nomLay->addWidget(labN2);
    nomLay->addWidget(nomJ2);

    //groupe des dimensions
    dimLay->addWidget(d1);
    dimLay->addWidget(d2);
    dimLay->addWidget(d3);

    //groupe des types
    typeLay->addWidget(t1);
    typeLay->addWidget(t2);
    typeLay->addWidget(t3);
    typeLay->addWidget(nbrHand);

    /**l'ajout des buttons au layout **/
    bLay->addWidget(bAnnul);
    bLay->addWidget(bConf);

    /** spécification des layouts pour les groupesdes composantes **/
    grpNom->setLayout(nomLay);
    grpDim->setLayout(dimLay);
    grpType->setLayout(typeLay);

    /**l'ajout des groupes au layout de la fenêtre **/
    centrWid->setLayout(lay);
    lay->addItem(new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding),0,1,1,1);
    lay->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding),2,0,1,1);
    lay->addWidget(grpType,2,1,1,1);
    lay->addItem(new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding),3,1,1,1);
    lay->addWidget(grpDim,4,1,1,1);
    lay->addItem(new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding),5,1,1,1);
    lay->addWidget(grpNom,6,1,1,1);
    lay->addItem(new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding),7,1,1,1);
    lay->addLayout(bLay,8,1,1,1);
    lay->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding),8,2,1,1);
    lay->addItem(new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding),9,1,1,1);
    lay->addItem(new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding),10,1,1,1);
    lay->setAlignment(Qt::AlignHCenter);

    /** spécifier la widget centrale de la fenêtre **/
    this->setCentralWidget(centrWid);

    /** séléctionner les composantes par défaut **/
    d1->setChecked(true);
    t1->setChecked(true);
    nbrHand->setRange(2,5);
    nbrHand->setHidden(true);

}

/** ************ evenement de fermeture ************ *
 *
 * @param:  QCloseEvent *event => evenement de cloture
 *
 * ***************************************************/
void ParametresView::closeEvent(QCloseEvent *event){
    //accepter la clôture
    event->accept();
    //indiquer l'annulation de partie
    emit annulPartie(true);
}
