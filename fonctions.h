#ifndef __fonctions_H_
#define __fonctions_H_
/*----------------------------------------------------------*/
/* Les prototypes et signatures des fonctions et procédures */
/*----------------------------------------------------------*/


/*-----------------------------------------------------------*/
/* Name : allouer                                            */
/* Auteur : Ugo Latry                                        */
/* Créée le : 27/04/2021                                     */
/* Description : Fonction permettant d'allouer de la mémoire */
/*-----------------------------------------------------------*/
int** allouer(int lignes, int colonnes);


/*----------------------------------------------------------------------------*/
/* Name : initialiser                                                         */
/* Auteur : Anthony Cerisere                                                  */
/* Créée le : 27/04/2021                                                      */
/* Description : Procédure permettant d'initialiser les valeurs de la matrice */
/*----------------------------------------------------------------------------*/
void initialiser(int** p_matrice, int lignes, int colonnes);


/*-----------------------------------------------------------------*/
/* Name : afficher                                                 */
/* Auteur : Léo Portet                                             */
/* Créée le : 27/04/2021                                           */
/* Description : Procédure permettant d'afficher la matrice du Jeu */
/*-----------------------------------------------------------------*/
void afficher(int** p_matrice, int lignes, int colonnes);


/*-----------------------------------------------------------------------------------------*/
/* Name :  voisins                                                                         */
/* Auteur :  Rémi Couzi & Léo Portet                                                       */
/* Créée le : 4/05/2021                                                                    */
/* Description : Fonction qui permet de savoir le nombre de voisins de pour chaque cellule */
/*-----------------------------------------------------------------------------------------*/
int voisins(int** p_mat, int ligne, int colonne, int lignes, int colonnes, int torique);

 
/*--------------------------------------------------------------------------*/
/* Name :  etat                                                             */
/* Auteur : Rémi Couzi & Léo Portet                                         */
/* Créée le : 03/05/2021                                                    */
/* Description : Fonction qui permet de changer ou non l'état d'une cellule */
/*--------------------------------------------------------------------------*/
int etat(int** p_mat, int nb_voisins, int y, int x);


/*----------------------------------------------------------------------------------------*/
/* Name :  copieMatrice                                                                   */
/* Auteur :  Ugo Latry                                                                    */ 
/* Créée le : 4/05/2021                                                                   */
/* Description : Procédure permettant de modifier la matrice grâce une matrice temporaire */
/*----------------------------------------------------------------------------------------*/
void copieMatrice(int** p_mat1, int** p_mat2, int lignes, int colonnes);


/*---------------------------------------------------------------*/
/* Name :  liberer                                               */
/* Auteur :  Anthony Cerisère                                    */ 
/* Créée le : 27/04/2021                                         */
/* Description : Procédure permettant de libérer l'espace mémoire*/
/*---------------------------------------------------------------*/
void liberer(int** p_mat, int lignes);

#endif
