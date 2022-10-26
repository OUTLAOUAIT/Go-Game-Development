#include "Chaine.h"

    /* constructeur d'initialisation avec
     * une liste d'initialisation pour les différents attributs
     */
    Chaine::Chaine(Goban & plateau,char joueur,int x,int y,int d):
        chaine(vector<Piece *>(0)),
        degLiberte(0),
        joueur(joueur),
        plateau(plateau),
        srcX(x),srcY(y)
    {
        /** génération de la chaine des pièces selon la direction **/

        if(d==0){
        //chaine de l'ensemble des pièces adjacents à (srcX,srcY)
            updateChaine(srcX-1,srcY);
            updateChaine(srcX,srcY+1);
            updateChaine(srcX+1,srcY);
            updateChaine(srcX,srcY-1);
        }
        else{
            //chaine qui est au-dessus de (srcX,srcY)
            if(d==HAUT)
                updateChaine(srcX-1,srcY);
            //chaine qui est à droite de (srcX,srcY)
            else if(d==DROIT)
                updateChaine(srcX,srcY+1);
            //chaine qui est au-dessous de (srcX,srcY)
            else if(d==BAS)
                updateChaine(srcX+1,srcY);
            //chaine qui est à gauche de (srcX,srcY)
            else if(d==GAUCHE)
                updateChaine(srcX,srcY-1);
        }
        //calculer le degré de libérté de la chaine
        compterDegLiberte();

    }
    /** recherche des pièces adjacents **/
    void Chaine::updateChaine(int x,int y){
        /* test sur la validité de la case et l'existence de la pièce dans la chaine */
        if(plateau.caseValide(x,y,joueur) && !existePiece(x,y)){
            //ajouter la pièce (x,y) à la chaine
            chaine.push_back(plateau.getPiece(x,y));
            //recherche recursive d'autre pièces dans les quatres directions
            updateChaine(x+1,y);
            updateChaine(x-1,y);
            updateChaine(x,y+1);
            updateChaine(x,y-1);
        }
        return;
    }
    /** calcul du degré de libérté de la chaine **/
    int Chaine::compterDegLiberte(){
        /* parcourir la liste des pièces */
        for(Piece *p:chaine){
            // coordonnées de la pièce *p
            int x=p->getIndiceLigne();
            int y=p->getIndiceCol();
            // degré de libérté de *p
            int n=plateau.compterDegLib(x,y);
            // indice de *p
            int indice=getIndice(p);
            // vérifier si une pièce q de la chaine partage une libérté avec p
            /*******************************
             *       y-2 y-1  y  y+1 y+2
             *
             *        |   |   |   |   |
             * x-2  - . - . - q - . - . -
             *        |   |   |   |   |
             * x-1  - . - q - . - q - . -
             *        |   |   |   |   |
             *  x   - q - . - p - . - q -
             *        |   |   |   |   |
             * x+1  - . - q - . - q - . -
             *        |   |   |   |   |
             * x+2  - . - . - q - . - . -
             *        |   |   |   |   |
             ********************************/
            // la libérté en haut
            if((n>0) && plateau.caseValide(x-1,y) &&
                    ( getIndice(plateau.getPiece(x-1,y-1))<indice ||
                        getIndice(plateau.getPiece(x-2,y))<indice ||
                        getIndice(plateau.getPiece(x-1,y+1))<indice ))
                n--;
            // la libérté a droite
            if((n>0)&& plateau.caseValide(x,y+1) &&
                    ( getIndice(plateau.getPiece(x-1,y+1))<indice ||
                        getIndice(plateau.getPiece(x,y+2))<indice ||
                        getIndice(plateau.getPiece(x+1,y+1))<indice ))
                n--;
            // la libérté en bas
            if((n>0)&& plateau.caseValide(x+1,y) &&
                    ( getIndice(plateau.getPiece(x+1,y+1))<indice ||
                        getIndice(plateau.getPiece(x+2,y))<indice ||
                        getIndice(plateau.getPiece(x+1,y-1))<indice ))
                n--;
            //la libérté à gauche
            if((n>0)&& plateau.caseValide(x,y-1) &&
                    ( getIndice(plateau.getPiece(x+1,y-1))<indice ||
                        getIndice(plateau.getPiece(x,y-2))<indice ||
                        getIndice(plateau.getPiece(x-1,y-1))<indice ))
                n--;
           //incrémentation du degré de libérté par n
           degLiberte+=n;

        }
        return degLiberte;
    }
    /** recupérer le vector des pièces de la chaine **/
    vector<Piece *>& Chaine::getChaine(){
        return chaine;
    }
    /** vérifier si la pièce (x,y) du goban appartient à la chaine **/
    bool Chaine::existePiece(int x,int y){
        //addresse de la pièce
        const Piece *piece=plateau.getPiece(x,y);
        //si la case n'appartient pas au goban
        if(piece==NULL)
               return false;
        //parcours de la chaine
        for(Piece *p:chaine){
            if(p==piece)//comparer p est les éléments de la chaine
                return true;
        }
        return false;
    }
    /** reinitialisation de la chaine **/
    void Chaine::resetChaine(){
        //supprimer les éléments du vector
        chaine.clear();
        degLiberte=0;
    }
    /** suppression des pièces de la chaine dans le goban **/
    int Chaine::viderChaine(){
       //nombre des pièces de la chaine
       int t=chaine.size();
       cout<<"Captures : "<<t<<" ==> [";
       //parcours de la chaine
       for(Piece *p:chaine){
           //affichage des pièces enlevees
           cout<<"{"<<p->getCouleur()<<":("<<p->getIndiceLigne()+1<<","<<p->getIndiceCol()+1<<")}";
           //enlever la pièce p du goban
           plateau.supprimerPiece(p->getIndiceLigne(),p->getIndiceCol());
       }
       cout<<"]"<<endl;
       resetChaine();
       //retourner le nombre des pièces de la chaine
       return t;
    }
    /** tester si la pièce source de la chaine est dans un état de suicide **/
    bool Chaine::estSuicide(){
        //Chaine a(plateau,plateau.pieceAdverse(joueur),srcX,srcY);

        /* Il existe de cas pour les cahines
         * cas 1 : chaine est de 0 élément => intersection (srcX,srcY) vide entouree par des pièces adverses
         *                                     (2,3 ou 4 selon la position dans goban : coin , cote ou milieu)
         * cas 2 : chaine est de >=1 éléments => chaine d'1 degré de liberte
         */
        if( ((chaine.size()==0 && degLiberte==0) ||(chaine.size()>0 && degLiberte==1 ))
             && plateau.compterDegLib(srcX,srcY)==0 ){
            return true;
        }
        return  false;
    }
     /** tester si la pièce source peut capturer les pièces de cette chaine **/
    bool Chaine::estCapture(){
        /* chaine doit être connectée
         * au moins comporte une pièce
         * degre de libérté == 1
         */
        if( chaine.size()>0 && degLiberte==1 && estConnecte() )
            return true;
        return false;
    }
    /** affichage de la chaine **/
    void Chaine::afficher(){
        cout<<"Tete {"<<srcX+1<<","<<srcY+1<<"} DegLibTete : "<<plateau.compterDegLib(srcX,srcY)<<endl;
        cout<<"Taille("<<chaine.size()<<")\nElements : [";
        //pacours de la chaine
        for(Piece * v:chaine){
            if(v!=NULL)
                cout<<"("<<v->getIndiceLigne()+1<<","<<v->getIndiceCol()+1<<") ";
        }
        cout<<"]"<<endl;
        cout<<"Suicide : "<<(estSuicide()?"Oui":"Non")<<" Capture : "<<(estCapture()?"Oui":"Non")<<endl;
    }
    /** récuperer l'indice d'une pièce dans la chaine **/
    int Chaine::getIndice(Piece *p){// indice i: 0<i<chaine.size() si p appartient a chaine , chaine.size() sinon
        //taille de la chaine
        int i=0,t=chaine.size();
        //si p n'existe pas
        if(p==NULL) return t;
        for(;i<t;i++)
            //comprer p avec les éléments de chaine
            if(chaine[i]==p)
               break;
        //indice de p
        return i;
    }

    /** vérifier si les pièces de la chaine sont connectées **/
    bool Chaine::estConnecte(){
        //si la chaine est vide
        if(chaine.size()==0)
            return false;
        //parcours de la chaine
        for(Piece *p:chaine){
            int x=p->getIndiceLigne(),y=p->getIndiceCol();
            // si p appartient a la chaine et aucun de ces pièces adjecentes q n'appartient pas
            /************************
             *       y-1  y  y+1
             *
             *        |   |   |
             * x-1  - . - q - . -
             *        |   |   |
             *  x   - q - p - q -
             *        |   |   |
             * x+1  - . - q - . -
             *        |   |   |
             ***********************/
            if(chaine.size()>1 &&!existePiece(x,y-1)&&!existePiece(x,y+1)&&!existePiece(x+1,y)&&!existePiece(x-1,y))
                return false;
        }
        return true;
    }
    /** générer des chaines liées a intersection (i,j) **/

    void Chaine::genererChaines(int i,int j,Goban &goban,vector<Chaine> &chaines,bool val){
        //les intersections adjacentes a (i,j)
        int  coord[4][3] ={{i-1,j,HAUT},{i,j+1,DROIT},{i+1,j,BAS},{i,j-1,GAUCHE}};
        //vider le vector des chaines
        chaines.clear();
        //récuperer le joueur actuel
        Joueur &joueur=goban.getJoueurs()[goban.getJoueurActuel()];
        //parcours des 4 directions adjacents a s
        for(int t=0;t<4;t++){
            /* test de validité de l'intersection */
            if(goban.caseHorsBorne(coord[t][0],coord[t][1]) || goban.caseValide(coord[t][0],coord[t][1]))
                continue;
            /* chaines du joueur actuel : meme couleur */
            else if(val){
                //tester si la pièce a la même couleur que le joueur
                if(goban.caseValide(coord[t][0],coord[t][1],joueur.getCouleur()) )
                {
                    unsigned int n=0;
                    //verifier si la pièce n'appartient pas à aucune des chaines déjâ traitées
                    for(unsigned int k=0;k < chaines.size();k++)
                        if(!chaines[k].existePiece(coord[t][0],coord[t][1]))
                            n++;
                        else
                            break;
                    if(n!=0)//ajout de la pièce à la chaine
                        chaines.push_back(Chaine(goban,joueur.getCouleur(),i,j,coord[t][2]));
                }
            }
            /* chaines adverses : couleur adverse */
            else{
                 //tester si la pièce est de couleur différent que le joueur
                if(goban.caseValide(coord[t][0],coord[t][1],goban.pieceAdverse(joueur.getCouleur())) )
                {
                   unsigned int n=0;
                   //verifier si la pièce n'appartient pas à aucune des chaines déjâ traitées
                    for( unsigned int k=0;k < chaines.size();k++)
                        if(!chaines[k].existePiece(coord[t][0],coord[t][1]))
                            n++;
                    if( n== chaines.size() )//ajout de la pièce a la chaine
                        chaines.push_back(Chaine(goban,goban.pieceAdverse(joueur.getCouleur()),i,j,coord[t][2]));
                }
            }
        }
    }
    /** test de capture sur un ensemble des chaine adverse **/
    bool Chaine::testCapture(vector<Chaine> &chainesAdv){
        unsigned int  cpt=0;
        //existence d'une chaine à capturer
        bool val=false;
        //parcours des chaines possibles
        while(cpt<chainesAdv.size()){
            if(chainesAdv[cpt].estCapture()){//garder les chaines à capturer
               val= true;
            }
            else{//reinitiliser celle qui ne le sont pas
                chainesAdv[cpt].resetChaine();
            }
            cpt++;
        }
        return val;
    }
