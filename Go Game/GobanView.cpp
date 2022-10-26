/** *** Interface Plateau de jeu *** **
 *
 *  Implémentation des fonctions
 *
 **************************************/

#include "GobanView.h"
#include "Chaine.h"
#include "ConstantesOS.h"
#include<QDebug>
#include<QMouseEvent>
#include<QGraphicsPixmapItem>
#include<QPixmap>
#include<QMessageBox>
#include<QToolTip>
#include <QLabel>

/** **************** Constructeur **************** **
 *  avec <liste d'initialisation des attributs>
 *
 * @param:  int dim         => taille du goban
 *          int larg        => larh=geur du plateau
 *          QWidget *parent => objet parent
 *
 ***************************************************/
GobanView::GobanView(int dim,int larg,QWidget *parent) :
 QGraphicsView(parent),goban(NULL),
  pieceImg(2),pieces(),dim(dim),marge(dim==DIM_GOB_PET?60:dim==DIM_GOB_MOY?50:40),passe(0)
{
    //Couleur du plateau
    setBackgroundBrush(QBrush(QColor(255, 179, 102), Qt::SolidPattern));
    //Cadre du plateau
    setFrameStyle(3);
    //activer la detection des événements de souris
    setMouseTracking(true);
    //préciser l'espace entre les intersections
    esp=(larg-2*marge)/(dim-1);
    //largeur de plateau
    larg=esp*(dim-1)+2*marge;
    //fixer les dimensions de plateau
    setFixedSize(larg,larg);
    //désactiver les barres de défilement
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ajout de la scene graphique
    scene=new QGraphicsScene(0,0,larg,larg,this);
    setScene(scene);
}
/** destructeur **/
GobanView::~GobanView()
{
    delete scene;
    delete goban;

}

/** initialiser les composantes du plateau **/
void GobanView::setGoban(){
    //vider la scene
    scene->clear();
    //crayon de dessin
    QPen stylo;
    stylo.setWidth(2);
    //Font de texte
    QFont font("Newyork" ,dim==DIM_GOB_PET?11:dim==DIM_GOB_MOY?9:7);

    //dessin du plateau
    for (int i=1,pas=marge;i<=dim;i++){
        /** les labels d'indication **/
        //colonne => lettre
        QLabel *numItem= new QLabel({(char)('A'+i-1),'\0'});//haut
        QLabel *numItem2= new QLabel(numItem->text());      //bas
        // lignes => numero
        QLabel *numItem1= new QLabel(QString::number(i));   //gauche
        QLabel *numItem3= new QLabel(numItem1->text());     //droite
        //ajuster l'alignement de texte
        numItem->setAlignment(Qt::AlignCenter);
        numItem2->setAlignment(Qt::AlignCenter);
        numItem1->setAlignment(Qt::AlignCenter);
        numItem3->setAlignment(Qt::AlignCenter);
        //spécifier le font de texte des labels
        numItem->setFont(font);
        numItem2->setFont(font);
        numItem1->setFont(font);
        numItem3->setFont(font);
        //attribuer la couleur du fond des labels
        numItem->setStyleSheet("QLabel{background-color:rgb(255, 179, 102);}");
        numItem2->setStyleSheet("QLabel{background-color:rgb(255, 179, 102);}");
        numItem1->setStyleSheet("QLabel{background-color:rgb(255, 179, 102);}");
        numItem3->setStyleSheet("QLabel{background-color:rgb(255, 179, 102);}");

        //précision de positions des labels
        int t=dim==DIM_GOB_PET?18:dim==DIM_GOB_MOY?16:14;
        numItem->setGeometry(pas-t/2,10,t,t);
        numItem2->setGeometry(pas-t/2,height()-(marge/2 ),t,t);
        numItem1->setGeometry(marge/5,pas-t/2,t,t);
        numItem3->setGeometry(width()-(marge/2),pas-t/2,t,t);

        //ajout des labels à la scene
        scene->addWidget(numItem);
        scene->addWidget(numItem2);
        scene->addWidget(numItem1);
        scene->addWidget(numItem3);

        //dessin des lignes du goban
        scene->addLine(pas,marge,pas,width()-marge,stylo);//horizontal
        scene->addLine(marge,pas,height()-marge,pas,stylo);//vertical
        pas+=esp;
    }
    //spécifier les mages des pièces selon la taille du goban
    switch(dim){
    //petit goban
    case DIM_GOB_PET:
        pieceImg[0]=":/pNoir/pnoire9";
        pieceImg[1]=":/pBlanc/pblanc9";
        break;
    //moyen goban
    case DIM_GOB_MOY:
        pieceImg[0]=":/pNoir/pnoire13";
        pieceImg[1]=":/pBlanc/pblanc13";
        break;
    //grand goban
    case DIM_GOB_NOR:
        pieceImg[0]=":/pNoir/pnoire19";
        pieceImg[1]=":/pBlanc/pblanc19";
        break;
    }
    /** dessin des hoshis **/
    //dimensions des hoshis
    QSize dimHoshi(8,8);
    //intersections des hoshis
    vector<vector<unsigned int>> &hoshi=dim==DIM_GOB_PET?HAN_POS_PET:dim==DIM_GOB_MOY?HAN_POS_MOY:HAN_POS_NOR;
    for(vector<unsigned int> &v:hoshi){
        //positions des pièces handicaps
        int *pos=intersToPos(v[0],v[1]);
        //ajout de circle représentant le hoshi
        scene->addEllipse( pos[0]-dimHoshi.width()/2,pos[1]-dimHoshi.height()/2, dimHoshi.width(), dimHoshi.height(), stylo, QBrush(Qt::black) );
        //libérer la varialble de position
        delete [] pos;
    }
    //la diemension de la pièce de jeu
    pix=(dim==DIM_GOB_PET?20:(dim==DIM_GOB_MOY?15:10));
    //initialisation de la liste  des pièces
    pieces.resize(dim);
    for(int i=0;i<dim;i++)
        pieces[i].resize(dim);
    //création de goban de jeu
    goban = new Goban(dim);
    //initaulisations des pièces d'indications
    item[0]=new  QGraphicsPixmapItem(QPixmap(pieceImg[0]));
    item[1]=new  QGraphicsPixmapItem(QPixmap(pieceImg[1]));
    //modification de l'opacité
    item[0]->setOpacity(0.5);
    item[1]->setOpacity(0.5);
    //état d'indication
    indPiece=false;
    //affichage du plateau
    this->show();
    //indiquer le changement de tour
    emit tourChange(goban->getJoueurActuel());
}

/** ******** passe de tour ***** **/
void GobanView::tourPasse(){
    //incrémenter le nombre de passes
    passe++;
    //changer le tour
    goban->tourJoueur();
    //indiquer le changement du tour
    emit tourChange(goban->getJoueurActuel());
    //condition d'arrêt de jeu : 2 passes consécutifs
    if(passe==2){
        //calcul de score des joueurs
        float sn=goban->getJoueurs()[0].calculScore();
        float sb=goban->getJoueurs()[1].calculScore(goban->getHandicap());
        //indiquer la fin de partie
        emit finPartie(sn,sb);
    }
}

/** ***** initialiser une partie a handicaps****** **
 *
 *@param: int n : nombre des pieces handicaps
 *
 ****************************************************/
void GobanView::partieHandicap(int n){
    //les positions des pièces handicaps
    vector<vector<unsigned int>> &tab= goban->partieHandicap(n);
    //affichage des pièces handicaps
    for(int i=0;i<n;i++){
        int *p=intersToPos(tab[i][0],tab[i][1]);
        afficherPiece(p[0],p[1],0);
        delete [] p;
    }
    //indiquer le changement de tour
    emit tourChange(goban->getJoueurActuel());
}

/** ******* initialiser une partie aléatoire ******* **/
void GobanView::partieAleatoire(){
    //les positions des pièces aléatoires
    vector<vector<int>> *liste=goban->jeuAleatoire();
    //affichage des pieces aléatoires
    for (vector<int> pos:*liste) {
        int *a=intersToPos(pos[0],pos[1]);
        afficherPiece(a[0],a[1],pos[2]);
        delete [] a;
    }
    //libérer la variable liste
    delete liste;
    //indiquer le changement de tour
    emit tourChange(goban->getJoueurActuel());
}

/** ******* gestion de mouvement de souris ******* **
 *
 * @param:  QMouseEvent* event : evenement de souris
 *
 ****************************************************/
void GobanView::mouseMoveEvent(QMouseEvent* event) {
    //position de click souris
    int x=event->pos().x(),y=event->pos().y();
    //test e validité de l'intérsection
    if(x>=(marge-10) && x<=(width()-marge+10) && y>=(marge-10) && y<=(height()-marge+10) &&
            ((x-marge)%esp<=10||(x-marge)%esp>=esp-10) && ((y-marge)%esp<=10||(y-marge)%esp>=esp-10)){
        //ajuster la position
        x=(x-marge)%esp<=10?x-(x-marge)%esp:x+esp-(x-marge)%esp;
        y=(y-marge)%esp<=10?y-(y-marge)%esp:y+esp-(y-marge)%esp;
        //récuperer l'intersection
        int *inter=posToInters(x,y);
        //afficher la pièce d'indication
        if(pieces[inter[0]][inter[1]]==nullptr && !indPiece){
            scene->addItem( item[goban->getJoueurActuel()]);
            item[goban->getJoueurActuel()]->setPos( x-pix, y-pix );
            indPiece=true;
        }
    }
    //enlever la pièce d'indication précedente
    else if(indPiece){
        scene->removeItem(item[goban->getJoueurActuel()]);
        indPiece=false;
    }
}

/** ********* gestion de click de souris ********* **
 *
 * @param:  QMouseEvent* event : evenement de souris
 *
 ****************************************************/
void GobanView::mousePressEvent(QMouseEvent* event) {
    //cacher l'indication de suicide
    emit etatSuicide(false);
    //position de click souris
    int x=event->pos().x(),y=event->pos().y();
    //test de validité d'intérsection choisie
    if(x>=(marge-10) && x<=(width()-marge+10) && y>=(marge-10) && y<=(height()-marge+10) &&
            ((x-marge)%esp<=10||(x-marge)%esp>=esp-10) && ((y-marge)%esp<=10||(y-marge)%esp>=esp-10)){
        //ajustement de la position
       x=(x-marge)%esp<=10?x-(x-marge)%esp:x+esp-(x-marge)%esp;
       y=(y-marge)%esp<=10?y-(y-marge)%esp:y+esp-(y-marge)%esp;
       //récupération de l'intersection
       int *inters=posToInters(x,y);
       //états de suicide et de capture
       bool suicide=false;
       bool capture=false;
       //vérifir si l'intersection choisie est vide
       if(goban->caseValide(inters[0],inters[1])){
           //vérifier si on est pas dans un cas de répétition
           if(!goban->testRepetition(inters[0],inters[1])){
               //générer les chaines adversaires
               vector<Chaine> ch;
               Chaine::genererChaines(inters[0],inters[1],*goban,ch);
               int n=0;
               //test de capture
               if((capture=Chaine::testCapture(ch))){
                   for(Chaine &c:ch){
                       vector<Piece*> p=c.getChaine();
                       if(p.size()!=0) n++;
                       /** ****  coups interdits **** **/
                       //cas repétition
                       int i=c.getChaine()[0]->getIndiceLigne(),j=c.getChaine()[0]->getIndiceCol();
                       if(c.estCapture()&&c.getChaine().size()==1&&goban->compterDegLib(i,j)==1&&((i!=0||i!=dim-1)&&(j!=0||j!=dim-1))){
                           goban->sauvEtatCapt(true);
                       }
                       //cas extreme des suicide
                       if(c.estCapture()&&c.getChaine().size()==1&&goban->compterDegLib(inters[0],inters[1])==0&&((i==0||i==dim-1)&&(j==0||j==dim-1))&&
                               ((Chaine(*goban,inters[0],inters[1],goban->getJoueurActuel()==0?NOIR:BLANC)).getChaine().size()<1)){
                          capture=false;
                          suicide=true;
                          goban->sauvEtatCapt(false);
                          break;
                       }
                       /** ************************** **/
                       //supression des pièces capturées
                       for(Piece * e:p){
                           supprimerPiece(e->getIndiceLigne(),e->getIndiceCol());
                       }
                       c.viderChaine();
                   }
                   if(n!=1)goban->sauvEtatCapt(false);
                   /***********************************/

                   //mise à jour des captures
                   emit majCapture(goban->getJoueurs()[0].getCapture(),goban->getJoueurs()[1].getCapture());

                   // condition de fin de partie : toutes les intersections sont pleines
                   if(goban->getCasesPleines()>=(goban->getTaille()*goban->getTaille()))
                       emit finPartie(goban->getJoueurs()[0].calculScore(),goban->getJoueurs()[1].calculScore());
               }
               else{//test de suicide
                   goban->sauvEtatCapt(false);
                   suicide=goban->testSuicide(inters[0],inters[1]);
               }
               //mise à jour du plateau
               if(capture || !suicide){
                   if(indPiece){//enlever la pièce d'indication
                       scene->removeItem(item[goban->getJoueurActuel()]);
                       indPiece=false;
                   }
                   //affichage de à pièce
                   afficherPiece(x,y,goban->getJoueurActuel());
                   //ajout de la pièce au goban
                   goban->poserPiece(inters[0],inters[1]);
                    //mise à jour de tour de jeu
                   emit tourChange(goban->getJoueurActuel());
                   //affichage du plateau
                   this->show();
                   //remetre le nombre de passes à 0
                   passe=0;
               }
               //sauvegarder l'état du goban
               goban->sauvGoban();
               //indication d'état de suicide
               emit etatSuicide(suicide);
           }
       }
   }
}

/** afficher une piece sur le goban **
 *
 * @param:  int x,int y : coordonnées d'intersection
 *          int i: joueur actuel
 *
 ********************************************/
void GobanView::afficherPiece(int x,int y,int i){
        //pièce à afficher
        QGraphicsPixmapItem *item=new QGraphicsPixmapItem(QPixmap::fromImage(QImage(pieceImg[i])));
        //position sur plateau
        int *pos=posToInters(x,y);
        //sauvegarder la pièce
        pieces[pos[0]][pos[1]]=item;
        //ajout de lapice à la scene
        scene->addItem( item);
        item->setPos( x-pix, y-pix );
        //libérer la variable de position
        delete pos;
}

/** supprimer une piece du goban **
 *
 * @param:  int x,int y : coordonnées d'intersection
 *
 ********************************************/
void GobanView::supprimerPiece(int x,int y){
       if(pieces[x][y]!=NULL){
           //enlever la pièce de la scene
           scene->removeItem(pieces[x][y]);
           //libérer le à ressource de la pièce
           delete pieces[x][y];
           pieces[x][y]=nullptr;
           //mise à jour de l'affichage
           this->show();
       }

}

/** conversion d'intersection en position **
 *
 * @param:  int x,int y : coordonnées d'intersection
 * @returns: int * : position en pixels
 *
 ********************************************/
int* GobanView::intersToPos(int x,int y){
    int *coord= new int[2];
    //abscisse
    coord[0]=marge+(y*esp);
    //ordonnée
    coord[1]=marge+(x*esp);
    return coord;
}

/** conversion de position en intersection **
 *
 * @param:  int posX,int posY : position en pixels
 * @returns: int * : coordonnées d'intersection
 *
 ********************************************/
int* GobanView::posToInters(int posX,int posY){
    int *inters= new int[2];
    //indice ligne
    inters[0]=(posY-marge)/esp;
    //indice colonne
    inters[1]=(posX-marge)/esp;
    return inters;
}

