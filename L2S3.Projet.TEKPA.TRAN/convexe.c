#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "convexe.h"



// fonction 'affichePoly' permet afficher les sommets d'un polygone
void affichePoly(Polygon pol) {
  if (pol == NULL) {
    printf("Polygon is empty\n");
    return;}
  Vertex *polyg_new = pol;
  do {
    printf("[%f, %f] ", polyg_new->s->x, polyg_new->s->y);
    polyg_new = polyg_new->next;
  } while (polyg_new != pol);
  printf("\n");
}

// lafonction 'longueur' retourne la longueur courante d'une enveloppe convexe
int longueur(ConvexHull *c){
    Vertex *v = c->pol;
    do{
        c->curlen++;  
        v = v->next; 
    } while(v != c->pol); 
    return c->curlen;
}

// la fonction alloueVertex alloue de la mémoire pour un nouveau sommet et renvoie un pointeur vers celui-ci
Vertex* alloueVertex(Point *p){
    Polygon t;
    t = (Polygon)malloc(sizeof(Vertex));
    if(t==NULL)return NULL;
    t->s = (Point *)malloc(sizeof(Point));
    t->s->x = p->x;
    t->s->y = p->y;
    t->prev = NULL;
    t->next = NULL;
    return t;
}

// la fonction 'estVide' verifie si un polygone est vide ou non
int estVide(Polygon pol)
{
    if(pol == NULL)
        return 1;
    return -1;
}

// la fonction insertFin insère un nouveau point à la fin d'un polygone, 
// elle utilise la fonction estvide pour verifier si un polygone est vide. 
void insertFin(Polygon *pol, Point p){
    Vertex *pol_new = alloueVertex(&p);
    if(pol_new==NULL){
        fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
        exit(EXIT_FAILURE);
    }
    pol_new->s->x = p.x;
    pol_new->s->y = p.y;
    if(estVide(*pol)==1){
        *pol = pol_new;
        pol_new->prev = pol_new;
        pol_new->next = pol_new;
    }
    else{
        Vertex *last = (*pol)->prev;
        last->next = pol_new;
        pol_new->prev = last;
        pol_new->next = *pol;
        (*pol)->prev = pol_new;
    }
}

//la fonction 'free2' libère la mémoire allouée pour un polygone
void free2(Polygon *pol){
    Polygon *stock;
    stock = pol;
    do{
        Polygon *new = &(*stock)->next;
        free(stock);
        stock = new;
    }while(stock!=pol);

}

// la fonction direct retourne la direction d'une ligne formée par trois points
//(si les points alignées, directs ou bien indirects)
int direct(Point *p1,Point *p2,Point *p3){
    return (p2->x-p1->x)*(p3->y-p1->y)-(p3->x-p1->x)*(p2->y-p1->y);
}

// La fonction 'polynome' prend un convexe et dessine ses sommets
void polynome(ConvexHull *c){
    int coordonnee1_x[500]={};
    int coordonnee1_y[500]={};
    int i;
    for(i=0; i<c->curlen; i++){
        coordonnee1_x[i] = (int)c->pol->s->x;
        coordonnee1_y[i] = (int)c->pol->s->y;
        c->pol=c->pol->next;
    }
    MLV_draw_polygon( coordonnee1_x, coordonnee1_y, c->curlen, MLV_COLOR_BLUE );
    MLV_update_window();
}

// La fonction 'free_convexHull' libère la mémoire allouée pour une enveloppe convexe.
void free_convexHull(Polygon *poly) {
    Polygon *poly2 = poly;
    (*poly)->next->prev = (*poly2)->prev;
    (*poly)->prev->next = (*poly2)->next;
}

// La fonction 'afficheP' prend une liste de points et les affiche sur l'interface
void afficheP(Point points[], int i){
    for(int j = 0; j<i; j++){
        MLV_draw_filled_circle((int)points[j].x,(int)points[j].y,3,MLV_COLOR_GREEN);
    }
    MLV_update_window();
}



Point get_point_on_clic(){
    double PERTURB = 0.0001/RAND_MAX;
    Point P;
    int x,y;
    MLV_wait_mouse(&x,&y);
    P.x = x+(rand()%2?+1.:-1.)*PERTURB*rand();
    P.y = y+(rand()%2?+1.:-1.)*PERTURB*rand();
    MLV_draw_filled_circle((int)P.x,(int)P.y,3,MLV_COLOR_GREEN);
    MLV_update_window();
    return P;
}

// La fonction 'deldouble' verifie lors de l'insertion d'un nouveau point si 
// cette dernière est à l'intérieur du convexe ou non
int deldouble(ConvexHull *c,Point *p){
    int count = 0;
    Vertex*pol = c->pol;
    do{
        if(pol->s->x == p->x && pol->s->y == p->y){
            count++;
        }
        pol = pol->prev;
    }while(pol != c->pol);
    return count;
}

// La fonction 'enrigistre' verifie aussi si un point est à intérieur du convexe
// Mais cette fois-ci dans le but de la coloration des points
int enrigistre(ConvexHull *c,Point *p){
    int count = 0;
    Vertex*pol = c->pol;
    do{
        if(pol->s->x == p->x && pol->s->y == p->y){
            count++;
        }
        pol = pol->prev;
    }while(pol != c->pol->next);
    return count;
}

// La fonction 'afficheP2' permet d'afficher les points en les filtrant
// En effet elle verifie si un point est à interieur du convexe. Le point sera colorié en vert
// Si ce dernier n'y est pas alors elle est colorié en jaune
void afficheP2(ConvexHull *c, Point points[], int i){
    int t;
    for(int j = 0; j<i; j++){
        //printf("83YEROIHIRJHOOPEJOJOJE3U\n\n");
        t = enrigistre(c, &points[j]);
        
        if(t!=0){
            MLV_draw_filled_circle((int)points[j].x,(int)points[j].y,3,MLV_COLOR_GREEN);
        }
        else{
            MLV_draw_filled_circle((int)points[j].x,(int)points[j].y,3,MLV_COLOR_YELLOW1);
        }
    }
    printf("%d\n", t);
    MLV_update_window();
}


//La fonction 'pts' est utilisée pour créer une enveloppe 
//convexe à partir d'un ensemble de points saisis par l'utilisateur. 
//La fonction prend en entrée un pointeur 
//vers une structure ConvexHull et modifie cette structure en y ajoutant des points pour créer l'enveloppe convexe. 
void pts(ConvexHull *c){
    Point points[50000];
    Point p;
    int i,j,k,x;
    for(i = 0; i<3; i++){
        p = get_point_on_clic();
        points[i] = p;}
    //printf("830002GUHDJOPJOE\n\n");
    afficheP(points,i);
    int poly_sens = direct(&points[0],&points[1],&points[2]);
    if(poly_sens <0){
        p = points[2];
        points[2] = points[1];
        points[1] = p;
    }
    for(j = 0; j<3; j++){
        insertFin(&(c)->pol,points[j]);
        affichePoly(c->pol);
    }
    longueur(c);
    polynome(c);
    Vertex *polyg_new;
    for(k = 3; k<c->maxlen; k++){
        int test = 0;
        p = get_point_on_clic();
        points[i++] = p;
        polyg_new = c->pol;
        do {
            x = direct(&p,polyg_new->s,polyg_new->next->s);
            if(x < 0){
                //x = direct(&p,polyg_new->s,polyg_new->next->s);
                if(test == 0){
                    polyg_new = polyg_new->next;
                    insertFin(&polyg_new,p);
                    polyg_new = polyg_new->prev;
                    c->curlen++;
                    test++;
                }
                else {free_convexHull(&polyg_new);c->curlen--;
                }
            }else{test = 0;}
            polyg_new = polyg_new->next;
        } while (polyg_new != c->pol);
        c->pol = polyg_new;
        affichePoly(c->pol);
        int retest = deldouble(c,&p);
        if(retest>1){
            free_convexHull(&c->pol);
            c->pol = c->pol->next;
            free_convexHull(&c->pol);
            c->curlen--;
            c->curlen--;
        }
        
        MLV_clear_window(MLV_COLOR_BLACK);
        afficheP2(c,points,i);
        polynome(c);
        affichePoly(c->pol);
        
       
    }
   
    
}

// La fonction 'pts_rand' fait la même chose que la fonction 'pts' 
// mais cette fois-ci de façon aléatoire sans que l'utilisateur
// ait à cliquer sur chaque point 
void pts_rand(ConvexHull *c, int width, int height){
    Point points[50000];
    Point p;
    int i,j,k;
    for(i = 0; i<3; i++){
        p.x = rand() % width;
        p.y = rand() % height;
        points[i] = p;}
    afficheP(points,i);
    int poly_sens = direct(&points[0],&points[1],&points[2]);
    if(poly_sens <0){
        p = points[2];
        points[2] = points[1];
        points[1] = p;
    }
    for(j = 0; j<3; j++){
        insertFin(&(c)->pol,points[j]);
    }
    longueur(c);
    polynome(c);
    Vertex *polyg_new;
    for(k = 3; k<c->maxlen; k++){
        int test = 0;
        p.x = rand() % width;
        p.y = rand() % height;
        points[i++] = p;
        polyg_new = c->pol;
        do {
            int x = direct(&p,polyg_new->s,polyg_new->next->s);
            if(x < 0){
                x = direct(&p,polyg_new->s,polyg_new->next->s);
                if(test == 0){
                    polyg_new = polyg_new->next;
                    insertFin(&polyg_new,p);
                    polyg_new = polyg_new->prev;
                    c->curlen++;
                    test++;
                }
                else {free_convexHull(&polyg_new);c->curlen--;
                }
            }else{test = 0;}
            polyg_new = polyg_new->next;
        } while (polyg_new != c->pol);
        c->pol = polyg_new;
        affichePoly(c->pol);
        int retest = deldouble(c,&p);
        if(retest>1){
            free_convexHull(&c->pol);
            c->pol = c->pol->next;
            free_convexHull(&c->pol);
            c->curlen--;
            c->curlen--;
        }
        //MLV_wait_seconds( 1 );
        MLV_clear_window(MLV_COLOR_BLACK);
        afficheP2(c,points,i);
        polynome(c);
        affichePoly(c->pol);
        
       
    }
    
    
}

// La fonction 'fermeF' ferme la fênetre à la fin si l'utilisateur 
// clique sur la touche q 
int fermeF(){
    MLV_Keyboard_button sym;
    MLV_Button_state state;
    while (1) {
        MLV_Event event = MLV_get_event(&sym, NULL, NULL, NULL, NULL,NULL, NULL, NULL, &state);
        if (event == MLV_KEY) {
            if(( sym == MLV_KEYBOARD_q ) && ( state == MLV_RELEASED )){
                MLV_free_window();
                return 0;
            }
        }
        MLV_actualise_window();
    }
    MLV_wait_seconds( 10 );
    MLV_free_window();
    return 0;

}

// La fonction 'fini' prend en paramètre le convexe 
// Et si le nombre max de point est atteint, affiche un message 
// Pour informer l'utilisateur
void fini(ConvexHull *c, int width){
    int i = 0;
    while(i<c->maxlen)i++;
    const char *text_box = "Le nombre maximal de points est atteint.\nPLus de point possible\appuiyez sur q pour fermer la fênetre";
    int width_box = 0 , height_box = 0, size_interligne = 9;
    MLV_get_size_of_adapted_text_box(
            text_box,
            size_interligne,
            &width_box, &height_box
    );
    int positionBoxX = (width-width_box)/2, positionBoxY = 300;
    MLV_draw_adapted_text_box(
            positionBoxX, positionBoxY,
            text_box,
            size_interligne,
            MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
            MLV_TEXT_CENTER
    );
    MLV_actualise_window();
    fermeF();
}  

int main(int argc, char *argv[]){
    ConvexHull c = {NULL, 0, 0};
    printf("Veuillez entrer le nombre max de points : ");
    scanf("%d",&c.maxlen);
    //scanf("%d",&c.maxlen);
    int width = 840, height = 660; 
    MLV_create_window("Ex1","Ex1",width,height);
    int i;
    for (i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0){
            pts_rand(&c, width, height);
        }
    }
    if(i<2){
        pts(&c);
    }
    fini(&c,width);
    //fermeF();
    //MLV_wait_seconds( 20 );
    //MLV_free_window();
    

}
