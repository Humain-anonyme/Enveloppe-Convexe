

typedef struct {
  double x;
  double y;
} Point;


typedef struct _vrtx_{
    Point* s;                      /* un point de l’ensemble */ 
    struct _vrtx_ *prev;           /* le vertex précédent */ 
    struct _vrtx_ *next;           /* le vertex suivant */ 
} Vertex, *Polygon;



typedef struct
{
    Polygon pol;        /* le polygône */
    int curlen;         /* la longueur courante */
    int maxlen;         /* la longueur maximale */
} ConvexHull;