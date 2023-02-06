#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "fonctions.h"
    
int main() {
    /*-------------------------------Déclaration des variables-------------------------*/
    int lignes, colonnes;
    int tours, torique;  //matrice torique ou non
    int temp;
    int** p_matrice;
    int** p_temp; //matrice temporaire
    /*---------------------------------------------------------------------------------*/


    /*---------------Lecture du Motif de départ dans le Fichier.txt--------------------*/
    scanf("%d %d",&colonnes, &lignes); //lecture fichier texte nb lignes/colonnes

    p_matrice = allouer(lignes, colonnes); //allocation mémoire lignes/colonnes
    p_temp = allouer(lignes, colonnes);
    
    initialiser(p_matrice, lignes, colonnes);
    initialiser(p_temp, lignes, colonnes);

    /*Boucle de lecture du motif de départ dans le fichier texte*/
    for(int i=0; i < lignes; i++) {        
        for( int j=0; j < colonnes; j++) {
            scanf("%d",&p_matrice[i][j]);
        }
    }  

    scanf("%d %d",&tours, &torique);  //lecture nb tours et si la matrice est torique ou non
    /*---------------------------------------------------------------------------------*/


    /*---------------------------------Boucle Principale-------------------------------*/
    for(int i=0; i < tours; i++) {
        system("clear"); //efface ce qu'il y avait à l'écran

        /*Affichage de la matrice */
        afficher(p_matrice, lignes, colonnes);

        for(int m=0; m < lignes; m++) {
            for(int n=0; n < colonnes; n++) {
                //on calcule et renvoie le nombre de voisins d'une case
                temp = voisins(p_matrice, m, n, lignes, colonnes, torique);
               
                
                //on calcule la valeur de la case qu'on stocke dans une matrice temporaire
                p_temp[m][n] = etat(p_matrice, temp, m, n);  
                
            }
        }
        //on remplace la matrice temporaire dans la principale
        copieMatrice(p_temp, p_matrice, lignes, colonnes);

        //réglage de la vitesse de rafraîchissement du terminal 
        usleep(50000);
    }
    /*---------------------------------------------------------------------------------*/
    
    liberer(p_matrice, lignes);
    liberer(p_temp, lignes);

    return 0;
}
