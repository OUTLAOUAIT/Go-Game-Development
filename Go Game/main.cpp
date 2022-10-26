/** ******** PFA: pplication de jeu de Go ******** **
 *
 * plateformes: - Desktop : linux (Ubuntu) et windows
 *              - Mobile : Android
 *
 * @authors:    - OHSSINE El-houssaine
 *              - OUTLAOUAIT El hassan
 *              - ZNBER Alaa
 *
 * @date :      Mars - Mai 2020
 ****************************************************/

#include "MenuJeuGo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // création de l'application
    QApplication a(argc, argv);
    // icon de l'application
    a.setWindowIcon(QIcon(":/icon/icongo"));
    //création du menu
    MenuJeuGo jeu;
    //affichage du menu
    jeu.show();
    //exécution de l'application
    return a.exec();

}
