/** Interface informations d'application **
 *
 *  Implémentation des fonctions
 *
 ******************************************/
#include "InfoView.h"
#include "ui_InfoView.h"
#include "MenuJeuGo.h"
#include <QCloseEvent>
#include <QDesktopWidget>

/** ********** Constructeur ********** **
 *
 * @param:  parent => objet parent
 *  avec <liste d'initialisation des attributs>
 *
 * **************************************/
InfoView::InfoView(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::InfoView)
{
    //lier la fenêtre et objet de classe de designe
    ui->setupUi(this);
    //centrée la fenêtre par rapport à l'écran
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
    /* connecter la fenêtre des infos et le menu de jeu */
    //rendre visible le menu à la cloture des infos
    connect(this,&InfoView::infoFerme,parent,&MenuJeuGo::show);
    //retour au menu au click de boutton retour
    connect(ui->retour,&QPushButton::clicked,this,&InfoView::close);
}

/** destructeur **/
InfoView::~InfoView()
{
    //liberer l'objet des inforamtions
    delete ui;
}

/** ************ evenement de fermeture ************ *
 *
 * @param:  QCloseEvent *event => evenement de cloture
 *
 * ***************************************************/
void InfoView::closeEvent(QCloseEvent *event){
    //indiquer la consultation des infos
    emit infoFerme();
    //accepter la cloture
    event->accept();
}
