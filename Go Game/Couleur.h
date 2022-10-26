#ifndef COULEUR_H
#define COULEUR_H
#include <iostream>
#include <vector>
using namespace std;
//effacer la console
#if defined(_WIN32) || defined(_WIN64) //cas windows
    #include<windows.h>
    #define CLEAR system("cls")
#else //cas linux
    #include<unistd.h>
    #define CLEAR system("clear")
#endif

//valeur du komi est handicap
#define KOMI 7.5
#define HANDI 0.5

//tailles des gobans
#define DIM_GOB_PET 9   //Petit
#define DIM_GOB_MOY 13  //Moyen
#define DIM_GOB_NOR 19  //Normal

//coueurs des pièces
#define NOIR 'N'
#define BLANC 'B'
#define VIDE '+'
//directions des pièces voisines
enum Direction{ HAUT=1,DROIT,BAS,GAUCHE};

//nombre max des handicap
#define MAX_HAN_PET 5 //dim = 9
#define MAX_HAN_MOY 5 //dim = 13
#define MAX_HAN_NOR 9 //dim =19

//positions des pièces handicap
/* taille 9*9 */
 static vector<vector<unsigned int>> HAN_POS_PET={ { 2 , 2 } , { 2 , 6 }  , { 6 , 2 } , { 6 , 6 }, { 4 , 4 } };
/* taille 13*13 */
 static vector<vector<unsigned int>> HAN_POS_MOY={ { 3 , 3 } , { 3 , 9 }  , { 9 , 3 } , { 9 , 9 }, { 6 , 6 } };
 /* taille 19*19 */
 static vector<vector<unsigned int>>  HAN_POS_NOR={ { 3 , 3 }  , { 3 , 15 } ,{ 15 , 3 }  , { 15 , 15 },
                                                   { 9 , 9 },{ 9 , 3 }  ,{ 9 , 15 } , { 3 , 9 }, { 15 , 9 }};


#endif // COULEUR_H
