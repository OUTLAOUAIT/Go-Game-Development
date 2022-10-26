/** ********* Interface regles de jeu :  desktop ********* **
 *
 * => classe qui presente les regles jeu
 * => declaraton :
 *               - des attributs
 *               - les fonctions membres
 *               - les signals et les slots
 *
 ************************************************************/
#ifndef REGLESVIEW_H
#define REGLESVIEW_H

#include <QMainWindow>
//Déclaration de la classe de design des règles
namespace Ui {
class ReglesView;
}

// classe Règles ( version bureau ) de jeu qui hérite de QMainWindow
class ReglesView : public QMainWindow
{
    Q_OBJECT
/** *** fonctions membres *** **/
public:
    //constructeur : classe parente
    explicit ReglesView(QWidget *parent = nullptr);
    //destructeur
    ~ReglesView();
    //événement de fermeture
    void closeEvent(QCloseEvent *event);

/** *** signals *** **/
signals:
    //indiquer la consultation des règles
    void reglesConsultes();

/** *** attributs *** **/
private:
    //objet de la classe de design des règles
    Ui::ReglesView *ui;
    //Actions de la barres des outils
    QAction *menuAct,*listeAct,*precAct,*suivAct;
};

#endif // REGLESVIEW_H
