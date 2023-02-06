# Projet Algorithmique fin 1ere année CY-Tech

## Le Jeu de la Vie

Le Jeu de la Vie a été inventé par John Horton Conway en 1970. Ce n'est pas un jeu approprement parlé pusiqu'il ne nécessite aucun joueur.
Mais c'est plutôt un automate cellulaire. Partant d'une organisation de différentes cellules de départ, celles-ci vont, au cours de l'exécution
du programme, évoluer suivant un shéma de règles bien précises.

Règle n°1 : une cellule reste en vie si elle est entourée de deux ou trois cellules voisines (en sachant q'une cellule peut avoir au maximum 8
cellules voisines).

Règle n°2 : une cellule meurt d'isolement si elle est entourée d'une seule cellule voisine ou une cellule meurt si elle est entourée d'au moins
4 cellules voisines.

Règles n°3 : une cellule prend vie si elle est entourée d'exactement 3 cellules voisines.

## Utilisation
  
Dans la console :    
- compiler le fichier fonctions.c et le fichier main.c en utilisant la commande :  
<pre><code>make clean</code></pre>  
(pour être sur d'avoir toutes les modifications), puis la commande :  
<pre><code>make</code></pre>  
- ensuite utiliser la commande :  
<pre><code>cat motifs/nomDuMotif.txt | ./exe</code></pre>  
qui permet d'accéder au dossier motifs contenant tous les motifs de départ à savoir :  
&nbsp;&nbsp;&nbsp;&nbsp; - canon.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - planeur.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - clignotant.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - grenouille.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - cerclefeu.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - boule.txt    
&nbsp;&nbsp;&nbsp;&nbsp; - illuminati.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - github.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - discord.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - nvidia.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - cy-tech.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - vache.txt   
&nbsp;&nbsp;&nbsp;&nbsp; - aireisti.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - shrek.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - satan.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - bateau.txt  
&nbsp;&nbsp;&nbsp;&nbsp; - bipolaire.txt  

puis qui permet d'exécuter le programme.

## A venir  

Version 2 :  
- une interface graphique
- un menu principale avec :  
&nbsp;&nbsp;&nbsp;&nbsp; - choix du motifs    
&nbsp;&nbsp;&nbsp;&nbsp; - choix vitesse  
&nbsp;&nbsp;&nbsp;&nbsp; - choix matrice torique ou non  

