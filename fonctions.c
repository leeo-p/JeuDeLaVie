#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>


/* Check */
/* Fonction permettant d'allouer de la mémoire à la matrice */
int** allouer(int lignes, int colonnes) {
    int** p_tab;
    p_tab = malloc(lignes *sizeof(int*));
    for(int i=0; i < lignes; i++) {
        p_tab[i] = malloc(colonnes *sizeof(int));
    }
    return p_tab;
}

/* Check */
/* Procédure permettant d'initialiser les valeurs de la matrice */
void initialiser(int** p_mat, int lignes, int colonnes) {
    for(int i=0; i < lignes; i++) {
        for(int j=0; j < colonnes; j++) {
            p_mat[i][j] = 0;
        }
    }
}

/* Check */
/* Procédure permettant d'afficher le matrice */
void afficher(int** p_matrice, int lignes, int colonnes) {
    printf("\n");
    for(int i=0; i<colonnes; i++) {
        printf("=  ");
    }
    /*---------------------Boucle d'affichage-------------------*/
    printf("\n");
    for(int i=0; i < lignes; i++) {
        for(int j=0; j < colonnes; j++) {
            printf("|");
            if(p_matrice[i][j] == 1) {
                printf("\033[104m  \033[0m"); //remplissage des espaces avec la couleur bleu (cellule vivante)
            }
            else {
                printf("  "); //pas de remplissage (pas de cellule)
            }
        }
        printf("\n");

    }
    /*---------------------------------------------------------*/
    for(int i=0; i < colonnes; i++) {
        printf("=  ");
    }
    printf("\n");
}


/* Check */
/* Fonction qui permet de savoir le nombre de voisins de pour chaque cellule */ 
int voisins(int** p_mat, int ligne, int colonne, int lignes, int colonnes, int torique) {
    int cpt = 0;
    
    /*-------------------Si la matrice n'est pas Torique------------------*/
    if (!torique) {   //matrice finie
        for(int i = ligne-1; i < ligne+2 ;i++) {
            for(int j = colonne-1; j < colonne+2; j++) {
                if (0 <= i && i < lignes && 0 <= j && j < colonnes && (i != ligne || j != colonne)) {
                    cpt += p_mat[i][j];
                }
            }
        }  
    }
    /*-------------------------------------------------------------------*/
    
    /*--------------------Si la matrice est Torique----------------------*/
    else {
        int x,y;
        for(int i = ligne-1; i < ligne+2; i++) { 
            for(int j = colonne-1; j < colonne+2; j++) {
                if (i != ligne || j != colonne) {
                    if (0 <= i && i < lignes && 0 <= j && j < colonnes) { 
                        cpt += p_mat[i][j];
                    }
                    else {
                        x = i;
                        y = j;
                        if (i == lignes){x = 0;}
                        if (i == -1){x = lignes-1;}

                        if (j == colonnes){y = 0;}
                        if (j == -1){y = colonnes-1;}

                        cpt += p_mat[x][y];
                    }
                }
            }
        }
    }
    /*------------------------------------------------------------------*/
    
    return cpt; //retourne le nombre de cellules voisines vivantes
}



/* Check */
/* Fonction qui permet de changer ou non l'état d'une cellule */
int etat(int** p_mat, int nb_voisins, int x, int y) {    
    int cel = p_mat[x][y];
    //naissance si une cellule vide a exactement 3 voisins | survie d'une cellule si elle a 2 ou 3 voisins
    if ((nb_voisins == 3 && cel == 0) ^ ((nb_voisins == 2 || nb_voisins == 3) && cel == 1)) { 
        /*Naissance d'une cellule*/
        return 1;
    }
    //la cellule meurt d'isolement si elle a 1 voisin | la cellule meurt de surpopulation si elle a 4 voisins ou plus
    else {
        /*Mort d'une cellule*/
        return 0;
    }
}

/* Check */
/* Procédure permettant de modifier la matrice grâce une matrice temporaire */
void copieMatrice(int** p_mat1, int** p_mat2, int lignes, int colonnes) {   //la matrice 2 prends la valeur de la 1
    for (int i=0; i < lignes; i++) {
        for (int j=0; j < colonnes; j++) {
            p_mat2[i][j] = p_mat1[i][j];
        }
    }
}

/* Check */
/* Procédure permettant de libérer l'espace mémoire */
void liberer(int** p_mat, int lignes) { //liberation de mémoire
    for(int i=0; i < lignes; i++) {
        free(p_mat[i]);
    }
    free(p_mat);
    p_mat = NULL;
}
