# Projet Algorithmique fin 1ere année CY-Tech

## Le Jeu de la Vie

Le Jeu de la Vie a été inventé par John Horton Conway en 1970. Ce n'est pas un jeu approprement parlé pusiqu'il ne nécessite aucun joueur. Mais c'est plutôt un automate cellulaire. Partant d'une organisation de différentes cellules de départ, celles-ci vont, au cours de l'exécution du programme, évoluer suivant un shéma de règles bien précises.

Règle n°1 : une cellule reste en vie si elle est entourée de deux ou trois cellules voisines (en sachant q'une cellule peut avoir au maximum 8 cellules voisines).

Règle n°2 : une cellule meurt d'isolement si elle est entourée d'une seule cellule voisine ou une cellule meurt si elle est entourée d'au moins 4 cellules voisines.

Règles n°3 : une cellule prend vie si elle est entourée d'exactement 3 cellules voisines.

## Utilisation

### Compilation

Dans la console, il faut compiler en utilisant la commande appropriée en fonction du système d'exploitation de la machine:
* **Windows**: `gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf`
* **Linux**: `gcc src/main.c -o bin/prog -lSDL2main -lSDL2 -lSDL2_ttf`  

### Exécution 

Dans la console, accéder au dossier bin avec : `cd bin`  
Puis lancer l'exécutable avec : `./prog`

### Commandes pour la simulation

Les différents touches utiles pour utiliser l'application:
* **Touches directionnelles (haut/bas)**: Augmenter/Diminuer la vitesse
* **Barre espace**: Mettre en pause la simulation
* **Échap**: Retour au menu principal

### Autres informations

Dans le menu, les paramètres sélectionnés sont écrit en rouge (motif, vitesse et si c'est torique ou pas).
