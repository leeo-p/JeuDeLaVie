#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

    
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720


typedef struct{
    int r;
    int g;
    int b;
}color;

/* Code couleur
0: noir
1: blanc
2: rouge
3: vert 
4: bleu
5: gris
*/

/*     Compilation
       > Windows : gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
       > Linux   : gcc src/main.c -o bin/prog -lSDL2main -lSDL2 -lSDL2_ttf
       Exécution : cd bin
                   ./prog
*/

void SDL_ExitWithError(const char *message);

void menu(SDL_Renderer *renderer, TTF_Font *font);

void Bouton(SDL_Renderer *renderer, TTF_Font *font, char * nom, int x, int y, int widh, int height, int color);

void Update(SDL_Renderer *renderer, TTF_Font *font, int motif, int vitesse, int torique);

void clic(int x, int y, int* motif, int* vitesse, int* torique);

color cl(int couleur);

//------------------------------------------------------------------------------------------------------------------------------------

int Simulation(SDL_Renderer *renderer, SDL_Window *window, int motif, int vitesse, int torique);

void afficher(SDL_Renderer *renderer, int** p_matrice, int lignes, int colonnes, color c1, color c2);

FILE* lire(int motif);

int etat(int** p_mat, int nb_voisins, int x, int y);

int voisins(int** p_mat, int ligne,int colonne, int lignes, int colonnes, int torique);

int** allouer(int lignes, int colonnes);

void initialiser(int** p_mat, int lignes, int colonnes);

void copieMatrice(int** p_mat1, int** p_mat2, int lignes, int colonnes);

void liberer(int** p_mat, int lignes);

//--------------------------------------------------------------------

int main(int arc, char *argv[])
{ 
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface * icon = NULL;

    

    TTF_Font *font = NULL;

    SDL_Rect cell;
    cell.x = 300; //position en x
    cell.y = 300; //position en y
    cell.w = 10; //largeur
    cell.h = 10; //hauteur

    SDL_Rect background;
    background.x = WINDOW_WIDTH; //position en x
    background.y = WINDOW_HEIGHT; //position en y
    background.w = WINDOW_WIDTH; //largeur
    background.h = WINDOW_HEIGHT; //hauteur

    



    //Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        SDL_ExitWithError("Initialisation SDL");

    if(TTF_Init() == -1) 
        SDL_ExitWithError("Erreur d'initialisation de TTF_Init");

    //Création fenetre + rendu
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0)
        SDL_ExitWithError("Impossible de cree la fenetre et le rendu");

    //Chargement police de caractere
    font = TTF_OpenFont("../ressources/font/arial.ttf", 200);
    if (font == NULL)
        SDL_ExitWithError("Chargement police de caractere");


    //Set up du titre et de l'icone de la fenetre
    SDL_SetWindowTitle(window, "Jeu de la Vie");

    icon = SDL_LoadBMP("../ressources/icon/icon.bmp");
    SDL_SetWindowIcon(window,icon);

    //--------------------------ARRIERE PLAN---------------------------------
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)  //noir
        SDL_ExitWithError("Impossible de changer la couleur pour le rendu");

    if (SDL_RenderFillRect(renderer, &background) != 0)
        SDL_ExitWithError("Impossible de dessiner rect");

    SDL_RenderPresent(renderer);
    //--------------------------------------------------------------------------


    
    menu(renderer, font);

    
    
    int motif = 1;
    int vitesse = 2;
    int torique = 1;
    int lancer = 0;

    int x,y;
    int temp = 0;

    Update(renderer, font, motif, vitesse, torique);

    int program_launched = 1;

    while(program_launched)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    printf("Clic en %dx/%dy\n", x, y);
                    temp = motif + vitesse + torique;

                    clic(x,y, &motif, &vitesse, &torique);

                    //----------LANCER--------------------------------
                    if (615 < x && x < 1030 && 600 < y && y < 670){  
                        printf("Lancement !!!\n");
                        program_launched = Simulation(renderer, window, motif, vitesse, torique);
                        if (program_launched)
                        {
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                            SDL_RenderClear(renderer);
                            Update(renderer, font, motif, vitesse, torique);
                        }
                        
                        
                    }
                    //------------------------------------------------

                    if (motif+vitesse+torique != temp)                  
                        Update(renderer, font, motif, vitesse, torique);
                    break;


                case SDL_QUIT:
                    program_launched = 0;
                    break;

                default:
                    break;
                
            }
        }
    }
   

    //-------------------------FERMETURE-------------------------------------
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}



//------------------------------FONCTIONS ET PROCEDURES----------------------------------




int Simulation(SDL_Renderer *renderer, SDL_Window *window, int motif, int vitesse, int torique)
{
    int program_launched = 1;
    
    printf("Lancement simulation pour le motif numero %d\n", motif);
    int lignes, colonnes;
    int c1, c2; //variables temporaires pour les couleurs
    int temp;
    int tours;
    

    color couleur1, couleur2;
    int** p_matrice = NULL;
    int** p_temp = NULL; 

    //------FICHIER---------------------------------------
    FILE* fichier = NULL;

    fichier = lire(motif);
    
    if (fichier == NULL){
        printf("Erreur lors de l'ouverture\n");exit(1);
    }
    
    
    fscanf(fichier, "%d %d", &colonnes, &lignes);

    p_matrice = allouer(lignes, colonnes);
    initialiser(p_matrice, lignes, colonnes);

    for(int i=0;i<lignes;i++){        
        for( int j=0;j<colonnes;j++){
            fscanf(fichier, "%d",&p_matrice[i][j]);
        }
    }  

    fscanf(fichier, "%d %d %d", &tours, &c1, &c2);

    couleur1 = cl(c1);
    couleur2 = cl(c2);


    fclose(fichier);

    printf("============\nlignes : %d\ncolonnes : %d\ntours : %d\ntorique : %d\nc1: %d | c2 : %d\n=============\n", tours, lignes, colonnes, torique, c1, c2);

    SDL_SetRenderDrawColor(renderer, couleur2.r, couleur2.g, couleur2.b, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    p_temp = allouer(lignes, colonnes);
    initialiser(p_temp, lignes, colonnes);

    int pause = 0;
    int end = 0;
    int i=0;
    
    while (i <= tours && !end)
    {
        SDL_Event event;
        
        if (!pause){
            afficher(renderer, p_matrice, lignes, colonnes, couleur1, couleur2);
            SDL_RenderPresent(renderer);
            for(int m=0;m<lignes;m++){
                for(int n=0;n<colonnes;n++){
                    temp = voisins(p_matrice, m, n, lignes, colonnes, torique);
                    p_temp[m][n] = etat(p_matrice, temp, m, n);  
                }
            }
            copieMatrice(p_temp, p_matrice, lignes, colonnes);
            SDL_Delay(100*(4-vitesse));
            printf("tour %d\n", i);
            i++;
        }

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_SPACE)
                        pause = !pause;
    
                    if(event.key.keysym.sym == SDLK_ESCAPE && !end)
                        end = 1;

                    if(event.key.keysym.sym == SDLK_UP)
                        vitesse++;if (vitesse>4){vitesse = 4;}

                    if(event.key.keysym.sym == SDLK_DOWN)
                        vitesse--;if (vitesse<1){vitesse=1;}
                    
                    break;

                case SDL_QUIT:
                    program_launched = 0;
                    end = 1;
                    break;


                default:
                    break;
            }
        }
    }

    liberer(p_matrice, lignes);
    liberer(p_temp, lignes);
    
    return program_launched;
}


void afficher(SDL_Renderer *renderer, int** p_matrice, int lignes, int colonnes, color c1, color c2){

    float coteC, coteL;
    coteC = 1080/colonnes;
    coteL = 720/lignes;

    SDL_Rect back;
    back.x = 0;
    back.y = 0;
    back.w = colonnes*coteC;
    back.h = lignes*coteL;

    SDL_Rect temp;
    temp.x = colonnes*coteC;
    temp.y = lignes*coteL;
    temp.w = coteC;
    temp.h = coteL;

    //arriere plan noir
    SDL_SetRenderDrawColor(renderer, c2.r, c2.g, c2.b, SDL_ALPHA_OPAQUE); //couleur du fond
    SDL_RenderFillRect(renderer, &back); //on remplie le fond
    SDL_SetRenderDrawColor(renderer, c1.r, c1.g, c1.b, SDL_ALPHA_OPAQUE);//couleur du dessin
    
    for(int i=0; i < lignes; i++){
        for(int j=0; j < colonnes; j++){
            if (p_matrice[i][j]){
                temp.x = j*coteC;
                temp.y = i*coteL;
                SDL_RenderFillRect(renderer, &temp);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

color cl(int couleur){
    color temp;
    switch(couleur)
    {
        case 0: //noir
            temp.r = 0;temp.g = 0;temp.b = 0;break;
        case 1: //blanc
            temp.r = 255;temp.g = 255;temp.b = 255;break;
        case 2: //rouge
            temp.r = 255;temp.g = 0;temp.b = 0;break;
        case 3: //vert
            temp.r = 0;temp.g = 255;temp.b = 0;break;
        case 4: //bleu
            temp.r = 0;temp.g = 0;temp.b = 255;break;
        case 5: //gris
            temp.r = 100;temp.g = 100;temp.b = 100;break;
        default:
            temp.r = 0;temp.g = 0;temp.b = 0;break;
    }
    return temp;
}

FILE* lire(int motif)
{
    FILE* fichier = NULL;

    switch(motif)
    {
        case 1: 
            fichier = fopen("../ressources/motifs/aireisti.txt", "r");break;
        case 2: 
            fichier = fopen("../ressources/motifs/boule.txt", "r");break;
        case 3: 
            fichier = fopen("../ressources/motifs/canon.txt", "r");break;
        case 4: 
            fichier = fopen("../ressources/motifs/cerclefeu.txt", "r");break;
        case 5: 
            fichier = fopen("../ressources/motifs/clignotant.txt", "r");break;
        case 6: 
            fichier = fopen("../ressources/motifs/cy-tech.txt", "r");break;
        case 7: 
            fichier = fopen("../ressources/motifs/discord.txt", "r");break;
        case 8: 
            fichier = fopen("../ressources/motifs/github.txt", "r");break;
        case 9: 
            fichier = fopen("../ressources/motifs/grenouille.txt", "r");break;
        case 10: 
            fichier = fopen("../ressources/motifs/illuminati.txt", "r");break;
        case 11: 
            fichier = fopen("../ressources/motifs/nvidia.txt", "r");break;
        case 12: 
            fichier = fopen("../ressources/motifs/planeur.txt", "r");break;
        case 13: 
            fichier = fopen("../ressources/motifs/satan.txt", "r");break;
        case 14: 
            fichier = fopen("../ressources/motifs/shrek.txt", "r");break;
        case 15: 
            fichier = fopen("../ressources/motifs/vache.txt", "r");break;
        default: 
            break;
    }
    return fichier;
}

//------------------------------------------------------------------

int voisins(int** p_mat, int ligne,int colonne, int lignes, int colonnes, int torique){
    int cpt = 0;
    
    /*-------------------Si la matrice n'est pas Torique------------------*/
    if (!torique){   //matrice finie
        for(int i = ligne-1; i < ligne+2 ;i++){
            for(int j = colonne-1; j < colonne+2; j++){
                if (0 <= i && i < lignes && 0 <= j && j < colonnes && (i != ligne || j != colonne)){
                    cpt += p_mat[i][j];
                }
            }
        }  
    }
    /*-------------------------------------------------------------------*/
    
    /*--------------------Si la matrice est Torique----------------------*/
    else{
        int x,y;
        for(int i = ligne-1; i < ligne+2; i++){
            for(int j = colonne-1; j < colonne+2; j++){
                if (i != ligne || j != colonne){
                    if (0 <= i && i < lignes && 0 <= j && j < colonnes){
                        cpt += p_mat[i][j];
                    }
                    else{
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
    return cpt; 
}



/* Check */
/* Fonction qui permet de changer ou non l'état d'une cellule */
int etat(int** p_mat, int nb_voisins, int x, int y){    
    int cel = p_mat[x][y];
    //naissance si une cellule vide a exactement 3 voisins | survie d'une cellule si elle a 2 ou 3 voisins
    if ((nb_voisins == 3 && cel == 0) ^ ((nb_voisins == 2 || nb_voisins == 3) && cel == 1)){ 
        /*Naissance d'une cellule*/
        return 1;
    }
    //la cellule meurt d'isolement si elle a 1 voisin | la cellule meurt de surpopulation si elle a 4 voisins ou plus
    else{
        /*Mort d'une cellule*/
        return 0;
    }
}

//------------------------------------------------------------------------

int** allouer(int lignes, int colonnes){
    int** p_tab;
    p_tab = malloc(lignes *sizeof(int*));
    for(int i=0; i < lignes; i++){
        p_tab[i] = malloc(colonnes *sizeof(int));
    }
    return p_tab;
}

/* Check */
/* Procédure permettant d'initialiser les valeurs de la matrice */
void initialiser(int** p_mat, int lignes, int colonnes){
    for(int i=0; i < lignes; i++){
        for(int j=0; j < colonnes; j++){
            p_mat[i][j] = 0;
        }
    }
}

void copieMatrice(int** p_mat1, int** p_mat2, int lignes, int colonnes){   //la matrice 2 prends la valeur de la 1
    for (int i=0; i<lignes; i++){
        for (int j=0; j<colonnes; j++){
            p_mat2[i][j] = p_mat1[i][j];
        }
    }
}

void liberer(int** p_mat, int lignes){ //liberation de mémoire
    for(int i=0; i<lignes; i++){
        free(p_mat[i]);
    }
    free(p_mat);
    p_mat = NULL;
}


//---------------SDL-------------------------------------------------------



void clic(int x, int y, int* motif, int* vitesse, int* torique)
{

    //-----MOTIF-------------------------------------

    if (30 < x && x < 260 && 28 < y && y < 100)      
        *motif = 1; //aireisti
    if (280 < x && x < 500 && 28 < y && y < 100)      
        *motif = 2; //boule
    if (30 < x && x < 260 && 115 < y && y < 180)      
        *motif = 3; //canon
    if (280 < x && x < 500 && 115 < y && y < 180)      
        *motif = 4; //cercle
    if (30 < x && x < 260 && 200 < y && y < 265)      
        *motif = 5; //cligno
    if (280 < x && x < 500 && 200 < y && y < 265)      
        *motif = 6; //cy
    if (30 < x && x < 260 && 285 < y && y < 345)      
        *motif = 7; //discord
    if (280 < x && x < 500 && 285 < y && y < 345)      
        *motif = 8; //github
    if (30 < x && x < 260 && 380 < y && y < 445)      
        *motif = 9; //grenouille
    if (280 < x && x < 500 && 380 < y && y < 445)      
        *motif = 10; //illuminati
    if (30 < x && x < 260 && 460 < y && y < 525)      
        *motif = 11; //nvidia
    if (280 < x && x < 500 && 460 < y && y < 525)      
        *motif = 12; //planeur
    if (30 < x && x < 260 && 540 < y && y < 610)      
        *motif = 13; //satan
    if (280 < x && x < 500 && 540 < y && y < 610)      
        *motif = 14; //shrek
    if (30 < x && x < 260 && 630 < y && y < 690)      
        *motif = 15; ///vache
    

    //---------VITESSE---------------------------------

    if (715 < x && x < 940 && 30 < y && y < 95)      
        *vitesse = 1; 
    if (715 < x && x < 940 && 120 < y && y < 180)      
        *vitesse = 2; 
    if (715 < x && x < 940 && 200 < y && y < 270)      
        *vitesse = 3; 

    //----------TORIQUE--------------------------------

    if (715 < x && x < 940 && 370 < y && y < 450)      
        *torique = 1; 
    if (715 < x && x < 940 && 460 < y && y < 530)      
        *torique = 0; 
    
}


void Update(SDL_Renderer *renderer, TTF_Font *font, int motif, int vitesse, int torique)
{
    int c1 = 30, c2 = 275, c3 = 712;
    int h1= 27, h2 = 112, h3 = 197, h4 = 282, h5 = 377, h6 = 452, h7 = 537, h8 = 622;
    int w = 235, h = 80;

    menu(renderer, font);

    switch(motif)
    {
        case 1:
            Bouton(renderer, font, "AirEISTI", c1, h1, w, h, 2);break;
        case 2:
            Bouton(renderer, font, "Boule", c2, h1, w, h, 2);break;
        case 3:
            Bouton(renderer, font, "Canon", c1, h2, w, h, 2);break;
        case 4:
            Bouton(renderer, font, "CercleFeu", c2, h2, w, h, 2);break;
        case 5:
            Bouton(renderer, font, "Clignotant", c1, h3, w, h, 2);break;
        case 6:
            Bouton(renderer, font, "CY Tech", c2, h3, w, h, 2);break;
        case 7:
            Bouton(renderer, font, "Discord", c1, h4, w, h, 2);break;
        case 8:
            Bouton(renderer, font, "GitHub", c2, h4, w, h, 2);break;
        case 9:
            Bouton(renderer, font, "Grenouille", c1, h5, w, h, 2);break;
        case 10:
            Bouton(renderer, font, "Illuminati", c2, h5, w, h, 2);break;
        case 11:
            Bouton(renderer, font, "Nvidia", c1, h6, w, h, 2);break;
        case 12:
            Bouton(renderer, font, "Planeur", c2, h6, w, h, 2);break;
        case 13:
            Bouton(renderer, font, "Satan", c1, h7, w, h, 2);break;
        case 14:
            Bouton(renderer, font, "Shrek", c2, h7, w, h, 2);break;
        case 15:
            Bouton(renderer, font, "Vache", c1, h8, w, h, 2);break;
        default:
            break;
    }

    switch(vitesse)
    {
        case 1:
            Bouton(renderer, font, "Lent", c3, h1, w, h, 2);break;
        case 2:
            Bouton(renderer, font, "Moyen", c3, h2, w, h, 2);break;
        case 3:
            Bouton(renderer, font, "Rapide", c3, h3, w, h, 2);break;
        default:
            break;
    }

    if (torique)
    {
        Bouton(renderer, font, "Torique", c3, h5-5, w, h, 2);
    }
    else{
        Bouton(renderer, font, "Non Torique", c3, h6+5, w, h, 2);
    }

    SDL_RenderPresent(renderer);

}

void menu(SDL_Renderer *renderer, TTF_Font *font){

    int motif = 1;
    int vitesse = 2;
    int ouvert = 0;
    

    int c1 = 30, c2 = 275, c3 = 712;
    int h1= 27, h2 = 112, h3 = 197, h4 = 282, h5 = 377, h6 = 452, h7 = 537, h8 = 622;

    int w = 235, h = 80;

    SDL_Surface *texte = NULL;
    SDL_Texture * texture = NULL;

    SDL_Color colorWhite = {255, 255, 255};
    SDL_Color colorRed = {255, 0, 0};


    SDL_Rect rectMotifs;
    rectMotifs.x = 20; //position en x
    rectMotifs.y = 20; //position en y
    rectMotifs.w = 500; //largeur
    rectMotifs.h = 690; //hauteur

    SDL_Rect rectLancer;
    rectLancer.x = 610; //position en x
    rectLancer.y = 600; //position en y
    rectLancer.w = 430; //largeur
    rectLancer.h = 80; //hauteur

    SDL_Rect rectVitesse;
    rectVitesse.x = 680; //position en x
    rectVitesse.y = 19; //position en y
    rectVitesse.w = 300; //largeur
    rectVitesse.h = 265; //hauteur

    SDL_Rect rectTorique;
    rectTorique.x = 680; //position en x
    rectTorique.y = 364; //position en y
    rectTorique.w = 300; //largeur
    rectTorique.h = 180; //hauteur

    SDL_Rect background;
    background.x = WINDOW_WIDTH; //position en x
    background.y = WINDOW_HEIGHT; //position en y
    background.w = WINDOW_WIDTH; //largeur
    background.h = WINDOW_HEIGHT; //hauteur

    printf("ici");
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &background);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); //blanc
       

    Bouton(renderer, font, "AirEISTI", c1, h1, w, h, 1);
    Bouton(renderer, font, "Boule", c2, h1, w, h, 1);
    Bouton(renderer, font, "Canon", c1, h2, w, h, 1);
    Bouton(renderer, font, "CercleFeu", c2, h2, w, h, 1);
    Bouton(renderer, font, "Clignotant", c1, h3, w, h, 1);
    Bouton(renderer, font, "CY Tech", c2, h3, w, h, 1);
    Bouton(renderer, font, "Discord", c1, h4, w, h, 1);
    Bouton(renderer, font, "GitHub", c2, h4, w, h, 1);
    Bouton(renderer, font, "Grenouille", c1, h5, w, h, 1);
    Bouton(renderer, font, "Illuminati", c2, h5, w, h, 1);
    Bouton(renderer, font, "Nvidia", c1, h6, w, h, 1);
    Bouton(renderer, font, "Planeur", c2, h6, w, h, 1);
    Bouton(renderer, font, "Satan", c1, h7, w, h, 1);
    Bouton(renderer, font, "Shrek", c2, h7, w, h, 1);
    Bouton(renderer, font, "Vache", c1, h8, w, h, 1);

    Bouton(renderer, font, "Lent", c3, h1, w, h, 1);
    Bouton(renderer, font, "Moyen", c3, h2, w, h, 1);
    Bouton(renderer, font, "Rapide", c3, h3, w, h, 1);

    Bouton(renderer, font, "Torique", c3, h5-5, w, h, 1);
    Bouton(renderer, font, "Non Torique", c3, h6+5, w, h, 1);

    texte = TTF_RenderText_Blended(font,"Lancer simulation", colorWhite);
    texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_RenderCopy(renderer, texture, NULL, &rectLancer);
    SDL_FreeSurface(texte); 
    SDL_DestroyTexture(texture);
    SDL_RenderDrawRect(renderer, &rectLancer);
    
    SDL_RenderDrawRect(renderer, &rectMotifs);    //zone des ressources/motifs
    SDL_RenderDrawRect(renderer, &rectVitesse);  //zone vitesse
    SDL_RenderDrawRect(renderer, &rectTorique);   //zone torique
         
    SDL_RenderPresent(renderer);
}

void Bouton(SDL_Renderer *renderer, TTF_Font *font, char * nom, int x, int y, int w, int h, int color)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_Color colorWhite = {255, 255, 255};
    SDL_Color colorRed = {255, 0, 0};
    SDL_Surface *texte = NULL;
    SDL_Texture * texture = NULL;

    if (color == 1){texte = TTF_RenderText_Blended(font, nom, colorWhite);}
    if (color == 2){texte = TTF_RenderText_Blended(font, nom, colorRed);}
    texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(texte); 
    SDL_DestroyTexture(texture);
    SDL_RenderDrawRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}


void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

