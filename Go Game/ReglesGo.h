/** ********** Ficchier d'inclusion de regles ********** **
 *
 * Inclure la classe de l'interface des regles selon
 * la platforme: Mobile ou Desktop
 *
 ***************************************************/
#ifndef REGLESGO_H
#define REGLESGO_H
#ifdef Q_OS_ANDROID // Si on est on est dans l'application mobile
    #include "ReglesGoView.h"       //Interface des règles mobile
    typedef ReglesGoView ReglesGo;  //redéfinition du type
#else               // Si on est on est dans l'application desktop
    #include "ReglesView.h"         //Interface des règles desktop
    typedef ReglesView ReglesGo;    //redéfinition du type
#endif

#endif // REGLESGO_H
