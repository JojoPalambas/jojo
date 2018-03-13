// #include "control.h"
#include <math.h>
#include <stdio.h>

/*
** Structures exactly like map except that it will store in every cell
** its distance to the start
*/
struct dijmap
{
    float *floor;
    int width;
    int height;
    struct vector2 start;
};

void dijmap_print(struct dijmap *dijmap);
struct dijmap *dijkstra(struct map *map);
