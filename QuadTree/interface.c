#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>




int donnees(int *size, int *taille_min, int *n, int *max_p, int *alea){
    char *nb_total;
    char *nb_feuille;
    int lst_x[3] = {200, 250, 300};
    int lst_y[3] = {200, 150, 200};
    int y_lst[3] = {300, 350, 300};
    MLV_Keyboard_button touche;
    MLV_create_window( "Les donnees - du - Quadtree", "input box", 512, 512 );
    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_draw_text(10, 10,"Veuillez entrer les données du Quadtree dans la fenêtre ci-dessous.",MLV_COLOR_BLACK);
    MLV_draw_text(10, 40,"Choisissez la taille de l'espace de travail.",MLV_COLOR_BLACK);
    while(touche != MLV_KEYBOARD_RETURN){
        MLV_draw_filled_polygon(lst_x, lst_y, 3, MLV_COLOR_GRAY);
        MLV_draw_filled_polygon(lst_x, y_lst, 3, MLV_COLOR_GRAY);
        MLV_draw_text_box(200, 225, 100, 50, "%d", 1,MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER,*size);
        MLV_actualise_window();
        MLV_wait_keyboard(&touche, NULL, NULL);
        MLV_draw_adapted_text_box(10, 60,"", 1,MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_WHITE,MLV_TEXT_CENTER);
        if(touche == MLV_KEYBOARD_RETURN){
            break;
        }
        if(touche == MLV_KEYBOARD_UP) {
            if(*size < 1024) *size *= 2;
            else MLV_draw_text(10, 60,"Le size est trop grande",MLV_COLOR_BLACK);
        }
        else if (touche == MLV_KEYBOARD_DOWN){
            if(*size > 1) *size /= 2;
            else MLV_draw_text(10, 60,"Le size est trop petite",MLV_COLOR_BLACK);
        }
    }
    MLV_clear_window(MLV_COLOR_WHITE);
    touche = MLV_KEYBOARD_a;
    MLV_draw_adapted_text_box(50, 40,"", 1,MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_WHITE,MLV_TEXT_CENTER);
    MLV_draw_text(10, 40,"Choisissez la taille minimale des QuadTrees.",MLV_COLOR_BLACK);
    while(touche != MLV_KEYBOARD_RETURN){
        MLV_draw_filled_polygon(lst_x, lst_y, 3, MLV_COLOR_GRAY);
        MLV_draw_filled_polygon(lst_x, y_lst, 3, MLV_COLOR_GRAY);
        MLV_draw_text_box(200, 225, 100, 50, "%d", 1,MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER,*taille_min);
        MLV_actualise_window();
        MLV_wait_keyboard(&touche, NULL, NULL);
        MLV_draw_adapted_text_box(10, 60,"", 1,MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_WHITE,MLV_TEXT_CENTER);
        if(touche == MLV_KEYBOARD_RETURN){
            break;
        }
        if(touche == MLV_KEYBOARD_UP) {
            if(*taille_min < *size) *taille_min *= 2;
            else MLV_draw_text(10, 60,"Le size est trop grande",MLV_COLOR_BLACK);
        }
        else if (touche == MLV_KEYBOARD_DOWN){
            if(*taille_min > 1) *taille_min /= 2;
            else MLV_draw_text(10, 60,"Le size est trop petite",MLV_COLOR_BLACK);
        }
    }
    MLV_clear_window(MLV_COLOR_WHITE);
    touche = MLV_KEYBOARD_a;
    MLV_draw_adapted_text_box(50, 40,"", 1,MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_WHITE,MLV_TEXT_CENTER);
    MLV_draw_text(10, 40,"0 : Version Clique-Souris                   et                          1 : Version Aleatoire",MLV_COLOR_BLACK);
    while(touche != MLV_KEYBOARD_RETURN){
        MLV_draw_filled_polygon(lst_x, lst_y, 3, MLV_COLOR_GRAY);
        MLV_draw_filled_polygon(lst_x, y_lst, 3, MLV_COLOR_GRAY);
        MLV_draw_text_box(200, 225, 100, 50, "%d", 1,MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER,*alea);
        MLV_actualise_window();
        MLV_wait_keyboard(&touche, NULL, NULL);
        MLV_draw_adapted_text_box(10, 60,"", 1,MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_WHITE,MLV_TEXT_CENTER);
        if(touche == MLV_KEYBOARD_RETURN){
            break;
        }
        if(touche == MLV_KEYBOARD_UP) {
            *alea = 1;
        }
        else if (touche == MLV_KEYBOARD_DOWN){
            *alea = 0;
        }
    }
    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_draw_text(10, 10,"Veuillez entrer les données du Quadtree dans la fenêtre ci-dessous.",MLV_COLOR_BLACK
    );
    MLV_wait_input_box(150,218,250,30,MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,"Le nb totals des particules : ",&nb_total
    );
    *n = atoi(nb_total);
    MLV_wait_input_box(150,218,200,30,MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,"Le nb max par feuille : ",&nb_feuille
    );
    *max_p = atoi(nb_feuille);
    MLV_actualise_window();
    MLV_wait_seconds( 1 );
    free( nb_total );
    free( nb_feuille );
    MLV_free_window();
    return 0;
}


/*
Cette fonction permet d'attendre un clic de la souris pour récupérer les coordonnées du point cliqué.
Elle renvoie les coordonnées du point sous la forme d'un objet Point.
*/
Point get_point_on_clic(){
    MLV_Keyboard_button sym;
    double PERTURB = 0.0001/RAND_MAX;
    Point P;
    int x,y;
    while(1){
        MLV_Event event = MLV_wait_keyboard_or_mouse(&sym, NULL, NULL,&x, &y);
        if (event == MLV_KEY) {
            if( sym == MLV_KEYBOARD_q ){
                P.x = -1;
                return P;
            }
        }
        else if(event == MLV_MOUSE_BUTTON){
            P.x = x+(rand()%2?+1.:-1.)*PERTURB*rand();
            P.y = y+(rand()%2?+1.:-1.)*PERTURB*rand();
            return P;
        }
    }
    return P;
}

/* Affiche les points se trouvant dans un quadtree */
void affiche_point(Tree tree){
    if(tree != NULL){
        for(int i = 0; i < tree->nb_elm_in_part; i++){
            MLV_draw_filled_rectangle(tree->particules[i]->p->x, tree->particules[i]->p->y, 3, 3, MLV_COLOR_RED);
        }
    }
}

// La fonction 'fermeF' ferme la fênetre à la fin si l'utilisateur
// clique sur la touche q
int fermeF(){
    MLV_Keyboard_button sym;
    MLV_Button_state state;
    MLV_Event event = MLV_get_event(&sym, NULL, NULL, NULL, NULL,NULL, NULL, NULL, &state);
    if (event == MLV_KEY) {
        if(( sym == MLV_KEYBOARD_q ) && ( state == MLV_RELEASED )){
            MLV_free_window();
            return 0;
        }
    }
    MLV_actualise_window();
    MLV_wait_seconds( 10 );
    MLV_free_window();
    return 0;

}



/*
Elle prend en parametre un quadtree et affiche recursivement les points se trouvant dans le quadtree.
*/
void dessineQuadTree(Tree tree){
    if(tree != NULL){
        if(tree->nb_elm_in_part == -1){
            MLV_draw_rectangle(tree->pos.x - tree->size/2,
            tree->pos.y - tree->size/2, tree->size, tree->size, MLV_COLOR_WHITE);
            MLV_draw_filled_rectangle(tree->pos.x - tree->size/2,
            tree->pos.y - tree->size/2, tree->size, tree->size, MLV_rgba(255,255,255,10));
        }
        else if(tree->nb_elm_in_part == 0) return;
        else{

            MLV_draw_rectangle(tree->pos.x - tree->size/2,
            tree->pos.y - tree->size/2, tree->size, tree->size, MLV_COLOR_CYAN);
            MLV_draw_filled_rectangle(tree->pos.x - tree->size/2,
            tree->pos.y - tree->size/2, tree->size, tree->size, MLV_rgba(150,0,0,10));
            MLV_update_window();
        }
        affiche_point(tree);
        MLV_update_window();
        dessineQuadTree(tree->fNE);
        dessineQuadTree(tree->fNO);
        dessineQuadTree(tree->fSO);
        dessineQuadTree(tree->fSE);
    }
}
