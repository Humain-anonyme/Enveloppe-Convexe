#ifndef __INTERFACE__
#define __INTERFACE__
#include "QuadTree.h"



/*
Cette fonction permet de récupérer les paramètres pour initialiser un Quadtree.
Les paramètres sont passés par référence pour pouvoir modifier leur valeur dans la fonction.
Elle renvoie un entier qui indique si la saisie des paramètres a été réussie ou non.
*/
int donnees(int *size, int *n, int *max_p, int *taille_min, int *alea);


/*
Cette fonction permet d'attendre un clic de la souris pour récupérer les coordonnées du point cliqué.
Elle renvoie les coordonnées du point sous la forme d'un objet Point.
*/
Point get_point_on_clic();


/*
Cette fonction prend en argument un quadtree et affiche sur l'interface ses points.
*/
void affiche_point(Tree tree);

/* Cette fonction permet de fermer la fenetre en cliquant sur "q" */
int fermeF();


/*
Cette fonction permet de dessiner les quadrants de l'arbre Quadtree et les points qu'ils contiennent.
Elle prend en argument un objet Tree qui représente l'arbre Quadtree à dessiner.
*/
void dessineQuadTree(Tree tree);


#endif
