#ifndef __QUADTREE__
#define __QUADTREE__



/*
Définit une structure de données Point contenant deux membres : x et y de type double. 
Cette structure est utilisée pour représenter les coordonnées d'un point dans l'espace.
*/
typedef struct{
    double x;
    double y;
} Point;


/*
Définit une structure de données ListePoint contenant un pointeur vers un point p et 
un pointeur vers l'élément suivant next. Cette structure est utilisée pour stocker une liste de points.
*/
typedef struct _liste_{
    Point *p;
    struct _liste_ *next;
}ListePoint, *Plist;


/*
- `nbp` : le nombre de points stockés dans le noeud courant.
- `nb_elm_in_part` : le nombre d'éléments dans chaque partition.
- `max_p` : le nombre maximal de points stockables dans le noeud courant.
- `nb_element` : le nombre de points stockés dans le noeud courant et dans ses fils.
- `particules` : un tableau de pointeurs de listes de points, stockant les points présents dans chaque partition.
- `pos` : les coordonnées du coin supérieur gauche du noeud courant.
- `size` : la taille de chaque côté du noeud courant.
- `taille_min` : la taille minimale du côté du noeud courant pour qu'il soit subdivisé.
- `fNE`, `fSE`, `fNO`, `fSO` : les quatre fils du noeud courant.
*/
typedef struct _QuadTree_{
    int nbp;
    int nb_elm_in_part;
    int max_p;
    int nb_element;
    Plist *particules;
    Point pos;
    int size;
    int taille_min;
    struct _QuadTree_ *fNE;
    struct _QuadTree_ *fSE;
    struct _QuadTree_ *fNO;
    struct _QuadTree_ *fSO;
} QuadTree, *Tree;


/*
Cette fonction alloue dynamiquement de la mémoire pour un point et retourne un pointeur vers ce point. 
Elle est utilisée pour allouer des points dans la mémoire pour être utilisés par d'autres fonctions.
*/
ListePoint *allouePoint();

/*
Cette fonction alloue dynamiquement de la mémoire pour un QuadTree et retourne un pointeur vers cette mémoire. 
Elle initialise également tous les membres de la structure de données.
- `max_p` : le nombre maximal de points stockables dans le noeud courant.
- `size` : la taille de chaque côté du noeud courant.
- `taille_min` : la taille minimale du côté du noeud courant pour qu'il soit subdivisé.
- `x` : la coordonnée `x` du coin supérieur gauche du noeud courant.
- `y` : la coordonnée `y` du coin supérieur gauche du noeud courant.
*/
QuadTree *alloueQuadTree(int max_p, int size, int taille_min, int x, int y);

/*
Cette fonction ajoute un point à une liste de points. Elle prend en entrée un pointeur vers une liste de points et un point. 
Elle retourne un code d'erreur qui indique si l'ajout du point a réussi ou échoué.
*/
int insererPoint(Plist *lstp, Point p);

/*
Cette fonction calcule la distance entre deux points donnés en entrée.
*/
int distance(Point p1, Point p2);

/*
Cette fonction parcourt l'arbre quadtree et réinitialise les particules à NULL.
*/
void renitialise_particule(Tree tree);


/* Cette fonction supprime les nœuds d'un QuadTree qui ont une seule particule. */
void purge_un(Tree tree);


/*
Cette fonction ajoute un fils à un nœud d'arbre donné. Elle prend en entrée un point et un arbre. 
Elle divise ensuite l'arbre en quatre quarts et insère le point dans le quadrant approprié.
*/
void ajoutFils(Tree tree, Point p);

/* Cette fonction ajoute un point à un arbre quadtree donné. */
int ajouteTree(Tree tree, Point p);

/* Cette fonction affiche tous les points stockés dans un arbre quadtree donné. */
void afficheQuadTree(Tree tree);


/* Cette fonction permet de liberer un point */
void freePoint(Point* p);

/* Cette libere les particules dans le quadtree ainsi que sa structure */
void freeQuadTree(QuadTree *tree);

#endif
