/** ********* Interface informations sur jeu ********* **
 *
 * => classe qui presente les infos liée à l'application
 * => declaraton :
 *               - des attributs
 *               - les fonctions membres
 *               - les signals et les slots
 *
 ********************************************************/

#ifndef INFOVIEW_H
#define INFOVIEW_H

#include <QMainWindow>
//déclaration de la classe de design des infos
namespace Ui {
    class InfoView;
}
// classe Informations de jeu qui hérite  de QMainWindow
class InfoView : public QMainWindow
{
    Q_OBJECT

public:
    //Constructeur de infos
    explicit InfoView(QWidget *parent = nullptr);
    //Destructeur de infos
    ~InfoView();
    //Evénement de fermeture
    void closeEvent(QCloseEvent *event);
signals:
    //fermeture de interface des infos
    void infoFerme();
private:
    //objet de la classe de designe des infos
    Ui::InfoView *ui;
};

#endif // INFOVIEW_H
