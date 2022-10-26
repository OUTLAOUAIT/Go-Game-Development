/** Interface principale de jeu **
 *
 *  Implémentation des fonctions
 *
 *********************************/

#include "JeuGoView.h"
#include "GobanView.h"
#include "ConstantesOS.h"
#include<QApplication>
#include<QDebug>
#include<QPixmap>
#include<QGraphicsPixmapItem>
#include<QMessageBox>
#include <QStyle>
#include<QDesktopWidget>
#include<QToolBar>
#include<QCloseEvent>

/** ***************** Constructeur ***************** **
 *
 * @param:  int dim                 => taille du goban
 *          QVector<QString> noms   => nom des joueurs
 *          QWidget *parent         => objet parent
 *
 *  avec <liste d'initialisation des attributs>
 *
 * *****************************************************/
JeuGo::JeuGo(int dim,QVector<QString> noms,QWidget *parent):
    QMainWindow(parent),dim(dim),etat(true),noms(noms)
{
    //cacher le menu de jeu
    parent->hide();
    // titre de la fenêtre
    setWindowTitle("Jeu Go - Partie Jeu");
    //précision des dimensions de la fenêtre
    int w = QApplication::desktop()->width();
    int h = QApplication::desktop()->height();
    int taille = w<h?w:h;
    VERSION==2?taille-=20:taille-=100;
    setFixedSize(taille,taille);
    //alignement des composantes
    layout()->setAlignment(this,Qt::AlignHCenter);
    //centrée la fenêtre par rapport à l'écran
    move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
    //initialisation des composantes
    initComposantes();
    //images des pièces de tour de jeu
    imgPiece[0]=new QPixmap(":/pNoir/pnoire");
    imgPiece[1]=new QPixmap(":/pBlanc/pblanc");

    //création de interface de plateau de jeu
    goban= new GobanView(dim,VERSION==2?taille:taille-120,this);
    //ajouter plateau de jeu à la fenêtre
    gridLayout->addWidget(goban,2,1,1,1);

    /** connexion des signals avec slots **/
    //changement de tour
    connect(goban,&GobanView::tourChange,this,&JeuGo::afficherTour);
    //mise a jour d'affichage des captures
    connect(goban,&GobanView::majCapture,this,&JeuGo::etatCapture);
    //fin de partie
    connect(goban,&GobanView::finPartie,this,&JeuGo::finPartie);
    //click button passage de tour
    connect(passerTour,&QPushButton::clicked,goban,&GobanView::tourPasse);
    //click button retour au menu prancipal (close event)
    connect(this,&JeuGo::retourMenu,parent,&QMainWindow::show);
    connect(retour,&QPushButton::clicked,this,&JeuGo::close);
    /* affichage des pièces initiales */
    //cas d'une partie aleatoire
    connect(this,&JeuGo::partieAletoire,goban,&GobanView::partieAleatoire);
    //cas d'une partie a handicaps
    connect(this,&JeuGo::partieHandicap,goban,&GobanView::partieHandicap);
    connect(goban,&GobanView::etatSuicide,this,&JeuGo::etatSuicide);
    /** initialisation du goaban de jeu **/
    goban->setGoban();
}

/** destructeur **/
JeuGo::~JeuGo()
{
    //libération des ressources allouées
    delete goban;
    delete imgPiece[0];
    delete imgPiece[1];
}

/** ***** Indication sur etat de suicide ***** **
 *
 * @param:  bool val => suicide ou non
 *
 * **********************************************/
void JeuGo::etatSuicide(bool val){
    //changer la visibilité de la label de suicide
    labSuic->setHidden(!val);
}

/** initialiser les composantes de la fenêtre de jeu **/
void JeuGo::initComposantes(){
    /** la widget centrale **/
    //initialisation
    centralwidget = new QWidget(this);
    //style des composantes
    centralwidget->setStyleSheet(QString::fromUtf8("QWidget{\n"
                                                   "background-color:rgb(186, 189, 182);}\n"
                                                   "QPushButton{\n"
                                                   "text-align: center;\n"
                                                   "font: 14pt Uroob;\n"
                                                   "background-color:rgb(136, 138, 133);\n"
                                                   "color:rgb(238, 238, 236);\n"
                                                   "}\n"
                                                   "QLabel{\n"
                                                   "text-align: center;\n"
                                                   "font: 14pt Uroob;\n"
                                                   "color:rgb(0, 0, 0);\n"
                                                   "}"));

    /** indications de jeu **/
    /* gestionneaire de positionnement : horizontal */
    horizontalLayout = new QHBoxLayout();

    /* indications de tour */
    //label de tour
    labelTour = new QLabel("Tour du joueur",centralwidget);
    //label de couleur du joueur
    labelTourImg = new QLabel(centralwidget);

    /* boutton de passe de tour */
    passerTour = new QPushButton(QIcon(":/icon/passer"),"Passer tour",centralwidget);
    passerTour->setIconSize(QSize(24,24));

    /* boutton de retour au menu */
    retour = new QPushButton(QIcon(":/icon/menu"),"Menu",centralwidget);
    retour->setFlat(true);
    retour->setStyleSheet("QPushButton{color: rgb(0,0,0);}");
    retour->setIconSize(QSize(32,32));
    /* état de suicide */
    labSuic =new QLabel(" Coup interdit : Suicide !",centralwidget);
    labSuic->setHidden(true);
    labSuic->setStyleSheet("QLabel{ color : red; font : bold 16pt; }");

    /* ajout des composantes d'indications au layout */
    horizontalLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    horizontalLayout->addWidget(retour);
    horizontalLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    horizontalLayout->addWidget(labelTour);
    horizontalLayout->addWidget(labelTourImg);
    horizontalLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    horizontalLayout->addWidget(passerTour);
    horizontalLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));


    /** indications de captures **/
    /* gestionneaire de positionnement : horizontal */
    horLay=new QHBoxLayout();

    /* label captures */
    labCapt=new QLabel("Captures ",centralwidget);
    iconCapt=new QLabel();
    iconCapt->setMaximumSize(32,32);
    iconCapt->setScaledContents(true);
    iconCapt->setPixmap(QPixmap(":/icon/capture"));

    /* labels joueur 1 (noir) */
    labj1=new QLabel(centralwidget);
    lab1 = new QLabel(QString(noms[0]),centralwidget);
    labj1->setPixmap(QPixmap(":/pNoir/pnoire"));

    /* labels joueur 2 */
    labj2=new QLabel(centralwidget);
    lab2 = new QLabel(QString(noms[1]),centralwidget);
    labj2->setPixmap(QPixmap(":/pBlanc/pblanc"));

    /* captures joueurs 1 */
    labcap1=new QLabel("0",centralwidget);

    /* captures joueurs 2 */
    labcap2=new QLabel("0",centralwidget);

    /* l'ajout des composantes de captures au layout */
    horLay->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    horLay->addWidget(iconCapt);
    horLay->addWidget(labCapt);
    horLay->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    horLay->addWidget(lab1);
    horLay->addWidget(labj1);
    horLay->addWidget(labcap1);
    horLay->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    horLay->addWidget(lab2);
    horLay->addWidget(labj2);
    horLay->addWidget(labcap2);
    horLay->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));

    /** gestionnaire de positionnement de la fenêtre : grille **/
    gridLayout = new QGridLayout(centralwidget);
    /*l'ajout des composantes d'indications au layout */
    //l'ajout des indications de captures
    gridLayout->addLayout(horLay, 0, 1, 1, 1);
    //l'ajout de l'indication de suicide
    gridLayout->addWidget(labSuic,1,1,1,1,Qt::AlignHCenter);
    gridLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 0, 1, 1);
    gridLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 2, 1, 1);
    //l'ajout des indications de tour
    gridLayout->addLayout(horizontalLayout, 3, 1, 1, 1);

    /** spécification de la wiget centrale de la fenêtre **/
    setCentralWidget(centralwidget);
}

/** ******* Fin de partie de jeu ******* **
 *
 * @param:  float sn => score du joueur noir
 *          float sb => score du joueur blanc
 *
 ******************************************/
void JeuGo::finPartie(float sn,float sb){
   //message indiquant que le joueur gagnant
    QString msg(sb<sn?noms[0]+" (Noir)":(sb>sn?noms[1]+" (Blanc)":"Egalite "));
    //boite de dialogue de type informative
    QMessageBox msgBox(QMessageBox::Icon::Information,"Score","Gagnant : "+msg,QMessageBox::Ok,this);
    msgBox.setStyleSheet(this->centralwidget->styleSheet());
    //affichage de la boite de dialogue
    msgBox.exec();
    etat=false;
    //fermeture de la fenêtre
    this->close();
}

/** ******* Affichage du tour de jeu ******* **
 *
 * @param:  int joueur => joueur actuel
 *
 **********************************************/
void JeuGo::afficherTour(int joueur){
    //vider la label de tour
    labelTourImg->clear();
    //afficher le couleur du joueur actuel
    labelTourImg->setPixmap(*imgPiece[joueur]);
    this->show();
}

/** **** afficher les captures des joueurs **** *
 *
 * @param:  int n => captures de joueur noir
 *          int b => captures de joueur blanc
 * ***************************************************/
void JeuGo::etatCapture(int n,int b){
    //maj des de texte des labels de captures
    labcap1->setText(QString::number(n));
    labcap2->setText(QString::number(b));
};

/** ************ evenement de fermeture ************ *
 *
 * @param:  QCloseEvent *event => evenement de cloture
 *
 * ***************************************************/
void JeuGo::closeEvent(QCloseEvent *event){
  //partie de jeu terminée
  if(!etat){
      //indiqeur le retour au menu
      emit retourMenu();
      //accepter l'événement
      event->accept();
  }
  //partie de jeu en cours de déreoulement
  else{
      //boite de dialogue de type confirmation
      QMessageBox a(QMessageBox::Warning,"Confirmation","Voulez vous terminer cette partie de jeu ?",QMessageBox::NoButton,this);
      a.setStyleSheet(this->centralwidget->styleSheet());
      /* l'ajout des buttons */
      //button d'annulation
      a.addButton(QMessageBox::Cancel);
      //button de confirmation
      a.addButton(QMessageBox::Ok);
      //affichage de boite de confirmation
      a.exec();
      /* test sur reponse choisie */
      //confirmation de fermeture
      if(a.clickedButton()==a.buttons()[0]){
          //accepter l'evenement
          event->accept();
          emit retourMenu();
      }
      //annulation de fermeture
      else {
          //ignorer l'événement
          event->ignore();
      }
  }
}

