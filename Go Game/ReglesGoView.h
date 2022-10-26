/** ********* Interface regles de jeu :  mobile ********* **
 *
 * => classe qui presente les regles jeu
 * => declaraton :
 *               - des attributs
 *               - les fonctions membres
 *               - les signals et les slots
 *
 ***********************************************************/
#ifndef REGLESGOVIEW_H
#define REGLESGOVIEW_H

#include <QMainWindow>

//Déclaration de la classe de design des règles
namespace Ui {
class ReglesGoView;
}
// classe Règles ( version mobile ) de jeu qui hérite de QMainWindow
class ReglesGoView : public QMainWindow
{
    Q_OBJECT

/** *** fonctions membres *** **/
public:
    //constructeur : classe parente
    explicit ReglesGoView(QWidget *parent = nullptr);
    //destructeur
    ~ReglesGoView();
    //événement de fermeture
    void closeEvent(QCloseEvent *event);

/** *** signals *** **/
signals:
    //indiquer la consultation des règles
    void reglesConsultes();

/** *** attributs *** **/
private:
    //objet de la classe de design des règles
    Ui::ReglesGoView *ui;
};


#endif // REGLESGOVIEW_H
