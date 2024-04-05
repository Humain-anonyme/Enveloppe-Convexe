#include "QuadTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>


/*
    Cette fonction alloue de la mémoire pour une nouvelle structure ListePoint et un nouveau Point.
    Si l'allocation de mémoire échoue pour l'un des deux, la fonction retourne NULL.
    Les coordonnées du Point sont initialisées à -1, et la liste next est initialisée à NULL.
    La fonction retourne un pointeur vers la nouvelle structure ListePoint.
*/
ListePoint *allouePoint(){
    Plist t;
    t = (Plist)malloc(sizeof(ListePoint));
    if(t == NULL) return NULL;
    t->p = (Point*)malloc(sizeof(Point));
    if(t->p == NULL){
        free(t);
        return NULL;
    }
    t->p->x = -1;
    t->p->y = -1;
    t->next = NULL;
    return t;
}


/*
Cette fonction alloue de la mémoire pour une nouvelle structure QuadTree.
Si l'allocation de mémoire échoue, la fonction retourne NULL.
Les différents champs de la structure QuadTree sont initialisés selon les paramètres passés à la fonction.
Si la taille du quadtree atteint la taille minimale, la fonction alloue de la mémoire pour un tableau de max_p listes de points.
Sinon, la fonction alloue de la mémoire pour quatre sous-quadtrees et un tableau de max_p listes de points.
*/
QuadTree *alloueQuadTree(int max_p, int size, int taille_min, int x, int y){
    Tree tree = (Tree)malloc(sizeof(QuadTree));
    if(tree == NULL) return NULL;
    tree->nb_element = 0;
    tree->nbp = 0;
    tree->nb_elm_in_part = 0;
    tree->size = size;
    tree->taille_min = taille_min;
    tree->pos.x = x;
    tree->pos.y = y;
    if(size == taille_min){
        int max = max_p * 100;
        tree->particules = (Plist*)malloc(max * sizeof(Plist));
        if (tree->particules == NULL) {
            free(tree);
            return NULL;
        }

        for (int i = 0; i < max; i++) {
            tree->particules[i] = allouePoint();
        }

        tree->max_p = max;
        tree->fNE = NULL;
        tree->fNO = NULL;
        tree->fSE = NULL;
        tree->fSO = NULL;

    }
    else{
        int max = max_p+1 ;
        tree->particules = (Plist*)malloc(max * sizeof(Plist));
        if (tree->particules == NULL) {
            free(tree);
            return NULL;
        }

        for (int i = 0; i < max_p; i++) {
            tree->particules[i] = allouePoint();
        }

        tree->max_p = max_p;
        tree->fNO = alloueQuadTree(max_p, size/2, taille_min, tree->pos.x - tree->size / 4, tree->pos.y - tree->size / 4);
        tree->fNE = alloueQuadTree(max_p, size/2, taille_min, tree->pos.x - tree->size / 4, tree->pos.y + tree->size / 4);
        tree->fSO = alloueQuadTree(max_p, size/2, taille_min, tree->pos.x + tree->size / 4, tree->pos.y - tree->size / 4);
        tree->fSE = alloueQuadTree(max_p, size/2, taille_min, tree->pos.x + tree->size / 4, tree->pos.y + tree->size / 4);


    }
    return tree;


}

/*
    Cette fonction prend un pointeur vers une liste de particules lstp et un Point p.
    Si la liste est vide, la fonction met à jour les coordonnées du premier élément de la liste avec les coordonnées du point p.
    Sinon, la fonction parcourt la liste jusqu'à trouver le dernier élément, puis ajoute un nouvel élément à la fin contenant les coordonnées du point p.
    La fonction retourne 0.
*/
int insererPoint(Plist *lstp, Point p){
    if((*lstp)->p->x == -1){
        (*lstp)->p->x = p.x;
        (*lstp)->p->y = p.y;
    }
    else{
        Plist q = *lstp;
        while(q->next != NULL){
            q = q->next;
        }
        q->next->p->x = p.x;
        q->next->p->y = p.y;
    }
    return 0;
}

int distance(Point p1, Point p2){
    int x = abs(p2.x - p1.x);
    int y = abs(p2.y - p1.y);
    return (x > y) ? x : y; /* On retourne x si x > y sinon on retourne y */
}


/*
Cette fonction prend en entrée un pointeur vers un objet de type Tree. Elle parcourt la liste de particules de chaque nœud de 
l'arbre et libère l'espace mémoire alloué pour chaque particule, puis réinitialise la liste de particules pour chaque nœud. 
La fonction utilise des pointeurs et la fonction free() pour libérer la mémoire.
*/
void renitialise_particule(Tree tree){
    for (int i = 0; i < tree->nbp; i++) {
        Plist lstp = tree->particules[i];
        while (lstp != NULL) {
            Plist tmp = lstp;
            lstp = lstp->next;
            free(tmp->p);
            free(tmp);
        }
        tree->particules[i] = NULL;
    }
    tree->nb_elm_in_part = -1;
}

/*
Cette fonction prend en entrée un pointeur vers un objet de type Tree. Elle parcourt la liste de particules 
de chaque nœud de l'arbre et déplace chaque particule dans le fils correspondant s'il existe. 
La fonction utilise la fonction ajoutFils(Tree tree, Point p) pour ajouter chaque particule dans le fils correspondant.
*/
void purge_un(Tree tree){
    for (int j = 0; j < tree->nb_elm_in_part; j++) {
        Plist lstp = tree->particules[j];
        while (lstp != NULL) {
            Point pt = *lstp->p;
            int x = pt.x;
            int y = pt.y;
            if(x < tree->pos.x){
                if(y < tree->pos.y){
                    ajoutFils(tree->fNO, pt);
                }
                else{
                    ajoutFils(tree->fNE, pt);
                }
            }
            else{
                if(y < tree->pos.y){
                    ajoutFils(tree->fSO, pt);
                }
                else{
                    ajoutFils(tree->fSE, pt);
                }
            }
            lstp = lstp->next;
        }
    }
}


/*
Cette fonction prend en entrée un pointeur vers un objet de type Tree et un objet de type Point. 
Elle ajoute le point p à l'arbre tree. Si le nœud courant a encore de la place pour stocker des particules, 
la fonction ajoute simplement le point p à la liste de particules du nœud courant.Sinon, 
la fonction utilise la fonction purge_un(Tree tree) pour déplacer les particules du nœud courant dans les fils 
correspondants, puis la fonction se rappelle récursivement sur le fils correspondant pour ajouter le point p dans le bon fils.
*/
void ajoutFils(Tree tree, Point p) {
    if (tree == NULL) {
        return;
    }
    tree->nb_element += 1;
    if (tree->nbp < tree->max_p) {
        insererPoint(&tree->particules[tree->nb_elm_in_part], p);
        tree->nbp += 1;
        tree->nb_elm_in_part += 1;
    }
    else {
        purge_un(tree);

        if (p.x < tree->pos.x && p.y < tree->pos.y) {
            ajoutFils(tree->fNO, p);
        }
        else if (p.x < tree->pos.x && p.y >= tree->pos.y) {
            ajoutFils(tree->fNE, p);
        }
        else if (p.x >= tree->pos.x && p.y < tree->pos.y) {
            ajoutFils(tree->fSO, p);
        }
        else if (p.x >= tree->pos.x && p.y >= tree->pos.y) {
            ajoutFils(tree->fSE, p);
        }

        renitialise_particule(tree);

    }
}


/*
Cette fonction prend en entrée un pointeur vers un objet de type Tree et un objet de type Point. 
Elle ajoute le point p à l'arbre tree. Si l'arbre tree est nul, la fonction retourne -1. 
Sinon, la fonction utilise la fonction ajoutFils(Tree tree, Point p) pour ajouter le point p à l'arbre tree. 
La fonction retourne 0.
*/
int ajouteTree(Tree tree, Point p) {
    if (tree == NULL) {
        return -1;
    }
    ajoutFils(tree, p);
    return 0;
}




void afficheQuadTree(Tree tree) {
    if (tree != NULL) {
        // Affiche les informations du noeud courant.
        printf("Position : (%lf, %lf)\n", tree->pos.x, tree->pos.y);
        printf("Nombre de particules en dessous : %d\n", tree->nb_element);
        printf("Nombre d'éléments dans le QuadTree : %d\n", tree->nb_elm_in_part);
        printf("Particules : ");
        // Parcours les particules de `tree`.
        for (int i = 0; i < tree->max_p; i++) {
            if(tree->particules == NULL) break;    // Si la liste est vide, on sort de la boucle.
            Plist lstp = tree->particules[i];
            while (lstp != NULL && lstp->p->x != -1) {
                // Affiche les coordonnées de la particule courante.
                printf("(%lf, %lf) ", lstp->p->x, lstp->p->y);
                lstp = lstp->next;
            }
        }
        printf("\n");
        // Parcours récursivement les fils de `tree`.
        afficheQuadTree(tree->fNE);
        afficheQuadTree(tree->fNO);
        afficheQuadTree(tree->fSO);
        afficheQuadTree(tree->fSE);
    }
}


void freePoint(Point* p){
    if(p != NULL) {
        free(p);
    }
}


void freeQuadTree(QuadTree *tree){
    if (tree == NULL) return;
    for (int i = 0; i < tree->nb_elm_in_part; i++) {
        freePoint(tree->particules[i]->p);
        free(tree->particules[i]);
    }
    free(tree->particules);
    if (tree->size > tree->taille_min){
        freeQuadTree(tree->fNO);
        freeQuadTree(tree->fNE);
        freeQuadTree(tree->fSO);
        freeQuadTree(tree->fSE);
    }
    free(tree);
}
