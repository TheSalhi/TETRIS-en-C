#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FAUX 0
#define VRAI 1
#define TAILLE 10


typedef struct {
    char **forme;
    int largeur;
    int ligne;
    int colonne;

} Piece;


void EffacePiece(Piece piece){     //Procédure qui libère l'espace alloué pour une pièce.

    int i;

    for(i = 0; i < piece.largeur; i++){
       
        free(piece.forme[i]);
    }
   
    free(piece.forme);
}

char Grille[TAILLE][TAILLE] = {0};
int VerificationPosition(Piece piece){    //Fonction qui vérifie si la position est disponible.

    int i, j;
    char **forme;

    forme= piece.forme;
   
    for(i = 0; i < piece.largeur;i++) {

        for(j = 0; j < piece.largeur ;j++){

            if((piece.colonne+j < 0 || piece.colonne+j >= TAILLE || piece.ligne+i >= TAILLE)){     //Si la pièce sort de la grille.
               
                if(forme[i][j]){

                    return FAUX;
                }
            }

            else if(Grille[piece.ligne+i][piece.colonne+j] && forme[i][j])

                return FAUX;

            }
        }
   
    return VRAI;    //Si la position est disponible.
}

Piece GenerePiece(Piece piece){      //Fonction qui alloue l'espace nécessaire pour une piece.

    int i;
    int j;
    char **generepiece;
    Piece piece1;

    piece1 = piece;
    generepiece = piece.forme;
    piece1.forme = (char**)malloc(piece1.largeur*sizeof(char*));  //Allocation dynamique.
   
    for(i = 0; i < piece1.largeur; i++){

        piece1.forme[i] = (char*)malloc(piece1.largeur*sizeof(char));
       
        for(j=0; j < piece1.largeur; j++) {

            piece1.forme[i][j] = generepiece[i][j];
        }
    }
    return piece1;
}

Piece piece0;
char Tour = VRAI;   //Permet de savoir si le jeu continue ou non.
void NouvellePiece(){     //Procédure qui envoie une pièce au hasard.

    Piece piece1;
    Piece ModelePiece[7]= {     //Tableau qui stocke les pièces.

    {(char *[]){(char []){0,0,0,0},             
                (char []){1,1,1,1},              //Piece en forme de Barre.
                (char []){0,0,0,0},
                (char []){0,0,0,0}
                },
                4},                              
    {(char *[]){(char []){0,1,1},
                (char []){1,1,0},                //Piece en forme de S.
                (char []){0,0,0}                 
                },
                3},                             
    {(char *[]){(char []){1,1,0},
                (char []){0,1,1},                //Piece en forme de Z.
                (char []){0,0,0}                 
                },
                3},                             
    {(char *[]){(char []){0,1,0},
                (char []){1,1,1},                //Piece en forme de T à l'envers.
                (char []){0,0,0}                 
                },
                3},                              
    {(char *[]){(char []){0,0,1},
                (char []){1,1,1},                //Piece en forme L (à l'envers).
                (char []){0,0,0}                 
                },
                3},                              
    {(char *[]){(char []){1,0,0},
                (char []){1,1,1},                //Piece en forme de L.
                (char []){0,0,0}                 
                },
                3},                              
    {(char *[]){(char []){1,1},
                (char []){1,1}                   //Piece en forme de Cube.
                },
                2}                                     
    };

    piece1 = GenerePiece(ModelePiece[rand()%7]);            //Génère une pièce au hasard parmi les 7.
    piece1.ligne = 0;                                       //Met la pièce en haut de la grille.
    piece1.colonne = rand()%(TAILLE-piece1.largeur+1);      //Met la pièce dans une colonne au hasard.
    EffacePiece(piece0);
    piece0 = piece1;

    if(!VerificationPosition(piece0)){                      // !VerificationPosition = si VerificationPosition retourne FAUX.

        Tour = FAUX;                                        //Si tour = FAUX on passe au tour suivant.
    }
}

void TournePiece(Piece piece){  //Procédure qui tourne la pièce dans le sens horaire.

    int i;
    int j;
    int k;
    int largeur;
    Piece PieceDemo;

    PieceDemo = GenerePiece(piece);
    largeur = piece.largeur;

    for(i = 0; i < largeur ; i++){

        for(j = 0, k = largeur-1; j < largeur ; j++, k--){  //Transforme chaque colonne en ligne en partant du bas de la colonne.

                piece.forme[i][j] = PieceDemo.forme[k][i];
        }
    }

    EffacePiece(PieceDemo);
}

void RemplirGrille(){   //Procédure qui remplace chaque case de la grille par une piece.

    int i;
    int j;

    for(i = 0; i < piece0.largeur ;i++){

        for(j = 0; j < piece0.largeur ; j++){

            if(piece0.forme[i][j])

                Grille[piece0.ligne+i][piece0.colonne+j] = piece0.forme[i][j];  
        }
    }
}

int score = 0;
void EffaceLigne(){     //Procédure qui efface une ligne si elle est pleine.

    int i;
    int j;
    int somme;
    int compteur;

    compteur=0;

    for(i=0;i<TAILLE;i++){

        somme = 0;

        for(j=0;j<TAILLE;j++){

            somme=somme+Grille[i][j];
        }

        if(somme==TAILLE){      //Si une ligne est remplie.

            int l;
            int k;

            compteur++;
           
            for(k = i;k >=1;k--){

                for(l=0;l<TAILLE;l++){

                    Grille[k][l]=Grille[k-1][l];   //La ligne pleine est remplacée par la ligne du dessus.
                }
            }

            for(l=0;l<TAILLE;l++){

                Grille[k][l]=0;  
            }
        }
       
    }

     score=score + 200*compteur;  //Pour chaque ligne pleine le score augmente.
}

void AfficheGrille(){   //Procédure qui affiche la grille avec les pièces.

     int i;
     int j;
     char Tableau[TAILLE][TAILLE] = {0};  
   
    for(i = 0; i < piece0.largeur ;i++){

        for(j = 0; j < piece0.largeur ; j++){

            if(piece0.forme[i][j])

                Tableau[piece0.ligne+i][piece0.colonne+j] = piece0.forme[i][j];
        }
    }
   
    printf(" A B C D E F G H I J\n");

    for(i = 0; i < TAILLE ;i++){

        for(j = 0; j < TAILLE ; j++){

            if(Grille[i][j] + Tableau[i][j]==0){

                printf("|%c",' ');
            }

            else{

                printf("|%c",'@');
            }

        }
        printf("|");
        printf("\n");
    }
    printf("\n");
    printf("Appuyez sur s pour en bas \n");
    printf("Appuyez sur d pour droite \n");
    printf("Appuyez sur q pour gauche \n");
    printf("Appuyez sur z pour tourner \n");
    printf("Ensuite appuyez sur ENTREE\n");
    printf("\n Score: %d\n\n", score);
}

void DeplacerPiece(int action){   //Procédure qui déplace la pièce grace aux touches.

    Piece temp;

    temp = GenerePiece(piece0);

    switch(action){    //Permet de choisir la direction en focntion de la touche activée.

        case 's':

            temp.ligne = temp.ligne+1;   //La pièce descend.

            if(VerificationPosition(temp)){
               
                piece0.ligne = piece0.ligne+1;
            }

            else {

                RemplirGrille();
                EffaceLigne();
                NouvellePiece();
            }

            break;

        case 'd':

            temp.colonne = temp.colonne+1;  //La pièce va à droite.

            if(VerificationPosition(temp)){

                piece0.colonne = piece0.colonne+1;
            }

            break;

        case 'q':  

            temp.colonne=temp.colonne-1;  //La pièce va à gauche.

            if(VerificationPosition(temp)){

                piece0.colonne = piece0.colonne-1;
            }

            break;

        case 'z':

            TournePiece(temp);  //La pièce change d'orientation.

            if(VerificationPosition(temp)){

                TournePiece(piece0);
            }

            break;
    }

    EffacePiece(temp);
    AfficheGrille();
}


int main() {

    int touche;
    char Pseudo[50];
    srand(time(0));

    printf("\n                                 BIENVENUE SUR\n\n");
    printf(" /////////////////// XXXXX  XXXXX  XXXXX  XXXX    X  XXXXX ///////////////////\n");
    printf(" ///////////////////   X    X        X    X   X   X  X     ///////////////////\n");
    printf(" ///////////////////   X    XXXX     X    XXXX    X  XXXXX ///////////////////\n");
    printf(" ///////////////////   X    X        X    X  X    X      X ///////////////////\n");
    printf(" ///////////////////   X    XXXXX    X    X   X   X  XXXXX ///////////////////\n\n");
    printf("Bienvenue sur TETRIS, veuillez saisir votre Pseudo :  ");
    scanf("%s",&Pseudo);
    NouvellePiece();
    AfficheGrille();

    while(Tour){

        touche = getchar();
        DeplacerPiece(touche);
    }

    printf ("  #####     #    #     # ####### ####### #     # ####### ######\n");
    printf (" #     #   # #   ##   ## #       #     # #     # #       #     #\n");
    printf (" #        #   #  # # # # #       #     # #     # #       #     #\n");
    printf (" #  #### #     # #  #  # #####   #     # #     # #####   ######\n");
    printf (" #     # ####### #     # #       #     #  #   #  #       #   #\n");
    printf (" #     # #     # #     # #       #     #   # #   #       #    #\n");
    printf ("  #####  #     # #     # ####### #######    #    ####### #     #\n\n");

    printf ("              %s votre score est de: %d\n" ,Pseudo,score);
    EffacePiece(piece0);
    return 0;
}