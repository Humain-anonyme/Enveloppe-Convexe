#include "interface.h"
#include "QuadTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>








int main(){
    int size = 512, n, max_p, taille_min = 1;
    int alea = 0;
    donnees(&size, &taille_min, &n, &max_p, &alea); // On initialise les donnees
    Tree tree = alloueQuadTree(max_p, size, taille_min, size/2, size/2); // On alloue la structure de donnees
    srand(time(NULL));
    Point p;
    int i;
    MLV_create_window("Appuyer sur 'q' pour fermer","",size,size);
    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_update_window();
    if(alea == 0){
        for(i = 0; i < n; i++){
            p = get_point_on_clic(); 
            if(p.x == -1) {
                MLV_free_window();
                return 0;
            }

            ajouteTree(tree, p); // On ajoute un point dans le quadtree
            MLV_clear_window(MLV_COLOR_WHITE);
            dessineQuadTree(tree); // On dessine le quadtree
            MLV_update_window();
        }
    }
    else{
        for(i = 0; i < n; i++){
            p.x =  rand() % size;
            p.y =  rand() % size;
            MLV_wait_milliseconds(600); 
            ajouteTree(tree, p); // On ajoute un point dans le quadtree
            MLV_clear_window(MLV_COLOR_WHITE);
            dessineQuadTree(tree); // On dessine le quadtree
            MLV_update_window();
        }
    }   
    MLV_wait_seconds(3);
    MLV_free_window();
    printf("Le QuadTree contient %d particules\n", tree->nb_element); // On affiche le nombre de points
    printf("-------------------------------------------------------------------\n");
    afficheQuadTree(tree);
    freeQuadTree(tree); // libere le Quadtree
    return 0;
}
