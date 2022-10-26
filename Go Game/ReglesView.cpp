/** Interface regles de jeu : version desktop **
 *
 *  Implémentation des fonctions
 *
 ******************************************/

#include "ReglesView.h"
#include "ui_ReglesView.h"
#include <QCloseEvent>
#include <QDesktopWidget>

/** ********** Constructeur ********** **
 *
 * @param:   QWidget *parent => objet parent
 *  avec <liste d'initialisation des attributs>
 *
 * **************************************/
ReglesView::ReglesView(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::ReglesView)
{
    //lier la fenêtre et objet de classe de designe

    ui->setupUi(this);
    //fixer les dimensions de la fenetre
    int width = this->frameGeometry().width();
    int height = this->frameGeometry().height();
    QDesktopWidget wid;
    int largEcran = wid.screen()->width();
    int hautEcran = wid.screen()->height();
    this->setGeometry((largEcran/2)-(width/2),(hautEcran/2)-(height/2),width,height);

    /* connecter la fenêtre des infos et le menu de jeu */
    //rendre visible le menu à la cloture des règles
    connect(this,&ReglesView::reglesConsultes,parent,&QMainWindow::show);

    /** afficher la page principale des règles **/
    ui->stackedWidget->setCurrentIndex(0);

    /** connexion des buttons de la page principale avec les slots **/
    //boutton joueur et matériel
    connect(ui->regJoueur,&QCommandLinkButton::clicked,this,[this]{
        ui->stackedWidget->setCurrentIndex(1);
    });
    //boutton déroulement de jeu
    connect(ui->regDebut,&QCommandLinkButton::clicked,this,[this]{
        ui->stackedWidget->setCurrentIndex(2);
    });
    //boutton statut des pières
    connect(ui->regStat,&QCommandLinkButton::clicked,this,[this]{
        ui->stackedWidget->setCurrentIndex(3);
    });
    //boutton coups intérdits
    connect(ui->regCoup,&QCommandLinkButton::clicked,this,[this]{
        ui->stackedWidget->setCurrentIndex(4);
    });
    //boutton fin de partie
    connect(ui->regFin,&QCommandLinkButton::clicked,this,[this]{
        ui->stackedWidget->setCurrentIndex(5);
    });

    /** actions de la barre d'outils **/
    menuAct=new QAction(QIcon(":/icon/menu"),"Menu pincipal");
    listeAct =new QAction(QIcon(":/icon/regles"),"Liste des règles");
    precAct=new QAction(QIcon(":/icon/prec"),"Page précédente");
    suivAct=new QAction(QIcon(":/icon/suiv"),"Page suivante");

    /** spécification des slots **/
    //retour au menu au click de boutton menu
    connect(menuAct,&QAction::triggered,this,[this,parent]{
        this->close();
        parent->show();
    });
    //afficher la page principale des règles
    connect(listeAct,&QAction::triggered,this,[this]{
        ui->stackedWidget->setCurrentIndex(0);
    });
    //passer à la page précédente
    connect(precAct,&QAction::triggered,this,[this]{
        int i=ui->stackedWidget->currentIndex();
        if(i>0)
            ui->stackedWidget->setCurrentIndex(i-1);
    });
    //passer à la page suivante
    connect(suivAct,&QAction::triggered,this,[this]{
        int i=ui->stackedWidget->currentIndex();
        if(i<6)
            ui->stackedWidget->setCurrentIndex(i+1);
    });

    /** ajout des actions à la barre des outils **/
    ui->toolBar->addAction(menuAct);
    ui->toolBar->addAction(listeAct);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(precAct);
    ui->toolBar->addAction(suivAct);
}

/** destructeur **/
ReglesView::~ReglesView()
{
    //libérer les ressorces allouées
    delete ui;
    delete menuAct;
    delete listeAct;
    delete precAct;
    delete suivAct;
}

/** ************ evenement de fermeture ************ *
 *
 * @param:  QCloseEvent *event => evenement de cloture
 *
 * ***************************************************/
void ReglesView::closeEvent(QCloseEvent *event){
    //indiquer la consultation des règles
    emit reglesConsultes();
    //accépter la cloture
    event->accept();
}
