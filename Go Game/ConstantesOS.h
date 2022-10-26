/** ******** fichier constatntes ******** **
 *
 *  Definitions de quelque constante selon platforme
 *
 *********************************************/
#ifndef CONSTANTES_H
#define CONSTANTES_H
#ifdef Q_OS_ANDROID
    #define VERSION 2
    #define LARG 480
    #define HAUT 720
    #define DIM_LAB 400
#else
    #define VERSION 1
    #define LARG 500
    #define HAUT 300
    #define DIM_LAB 280
#endif

#endif // CONSTANTES_H
