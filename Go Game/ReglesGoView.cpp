/** Interface regles de jeu : version mobile **
 *
 *  Implémentation des fonctions
 *
 ******************************************/

#include "ReglesGoView.h"
#include "ui_ReglesGoView.h"
#include "MenuJeuGo.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QCloseEvent>

/** ********** Constructeur ********** **
 *
 * @param:   QWidget *parent => objet parent
 *  avec <liste d'initialisation des attributs>
 *
 * **************************************/
ReglesGoView::ReglesGoView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReglesGoView)
{
    //lier la fenêtre et objet de classe de designe
    ui->setupUi(this);
    //centrer la fenêtre par rapport a l'écran
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
    //fixer les dimensions de la fenêtre
    this->setFixedSize(size());
    /* connecter la fenêtre des infos et le menu de jeu */
    //rendre visible le menu à la clôture des règles
    connect(this,&ReglesGoView::reglesConsultes,parent,&MenuJeuGo::show);
    //retour au menu au click de boutton retour
    connect(ui->retour,&QPushButton::clicked,this,&ReglesGoView::close);

}

/** destructeur **/
ReglesGoView::~ReglesGoView()
{
    //liberer l'objet des inforamtions
    delete ui;
}

/** ************ evenement de fermeture ************ *
 *
 * @param:  QCloseEvent *event => evenement de cloture
 *
 * ***************************************************/

void ReglesGoView::closeEvent(QCloseEvent *event){
    //indiquer la consultation des règles
    emit reglesConsultes();
    //accepter la clôture
    event->accept();
}

