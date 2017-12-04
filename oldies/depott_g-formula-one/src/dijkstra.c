#include "control.h"
#include "include.h"

#include <stdlib.h>

/* Converts a floating position to the coordinates of the cell around it */
static struct vector2 pos_cell(struct vector2 pos)
{
    struct vector2 ret =
    {
        (float)(int)pos.x, (float)(int)pos.y
    };
    return ret;
}

/* Initializes the dijmap structure */
static struct dijmap *dijmap_init(struct map *map)
{
    // Allocates the needed memory
    struct dijmap *dijmap = malloc(sizeof (struct dijmap));
    dijmap->floor = malloc(sizeof (float) * map->width * map->height);

    // Fills the dijmap with -1 values and a -2 for the end
    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            if (map->floor[i * map->width + j] == FINISH)
                dijmap->floor[map->width * i + j] = -2;
            else
                dijmap->floor[map->width * i + j] = -1;
        }
    }

    // Initializes the other values of the struct dijmap
    dijmap->width = map->width;
    dijmap->height = map->height;
    dijmap->start = pos_cell(map->start);
    return dijmap;
}

/* Computes the distance between the point (0, 0) and the point (i, j) */
static float dist(int i, int j)
{
    if (i == 0 && j == 0)
        return 0;
    if (i == j || i == -j)
        return sqrt(2);
    return 1;
}

/*
** Uses Dijkstra's algorithm to fill the whole dijmap with, in every cell,
** its distance to the start
*/
static void dijmap_build_rec(struct dijmap *dijmap, struct map *map,
                  struct vector2 v2, float depth)
{
    int pos = v2.y * dijmap->width + v2.x;
    if (dijmap->floor[pos] == -1)
        dijmap->floor[pos] = 0;
    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            int cur_pos = (v2.y + j) * dijmap->width + (v2.x + i);
            float d = dist(i, j);

            if (v2.x + i < 0 || v2.y + j < 0
             || v2.x + i >= map->width || v2.y + j >= map->height
             || (i == 0 && j == 0)
             || i == j
             || i == -j)
                continue;

            if (map->floor[cur_pos] == BLOCK)
                continue;
            else if (map->floor[cur_pos] == ROAD
                  || map->floor[cur_pos] == GRASS)
            {
                float d_fric = 0;
                if (map->floor[cur_pos] == ROAD)
                    d_fric = d / CAR_FRICTION_FACTOR;
                else if (map->floor[cur_pos] == GRASS)
                    d_fric = d / CAR_GRASS_FRICTION_FACTOR;

                if (dijmap->floor[cur_pos] > depth + d_fric
                 || dijmap->floor[cur_pos] == -1)
                {
                    dijmap->floor[cur_pos] = depth + d_fric;
                    struct vector2 new_v = { v2.x + i, v2.y + j };
                    dijmap_build_rec(dijmap, map, new_v, depth + d_fric);
                }
            }
            else if (map->floor[cur_pos] == FINISH)
            {
                if (dijmap->floor[cur_pos] > depth + d)
                    dijmap->floor[cur_pos] = depth + d;
            }
        }
    }
}

/*
 * Function that returns the coordinates of the cell having the smallest value
 * in the eight cells around v2
*/
static struct vector2 min_around(struct dijmap *dijmap, struct vector2 v2)
{
    // Makes the coordinates of v2 readable and efficient to use
    v2 = pos_cell(v2);

    // Sets all the info to know about the min cell
    float min = -1;
    int mini = -1;
    int minj = -1;

    // For every cell around v2
    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            int cur_pos = (v2.y + j) * dijmap->width + (v2.x + i);

            // If the coordinates are invalid
            if (v2.x + i < 0 || v2.y + j < 0
             || v2.x + i >= dijmap->width || v2.y + j >= dijmap->height
             || (i == 0 && j == 0)
             || dijmap->floor[cur_pos] == -1
             || dijmap->floor[cur_pos] == -2
             || i == j
             || i == -j)
                continue;

            // If the cell is the min cell to find
            if (min == -1
                || (dijmap->floor[cur_pos] < min))
            {
                min = dijmap->floor[cur_pos];
                mini = i;
                minj = j;
            }
        }
    }
    struct vector2 ret =
    {
        v2.x + mini, v2.y + minj
    };
    return ret;
}

/* Function that calls dijmap_build_rec */
static void dijmap_build(struct dijmap *dijmap, struct map *map)
{
    dijmap_build_rec(dijmap, map, dijmap->start, 0);
}

/* Function that returns the coordinates of the end of a map */
static struct vector2 find_end(struct map *map)
{
   for (int j = 0; j < map->height; j++)
   {
       for (int i = 0; i < map->width; i++)
       {
           if (map->floor[j * map->width + i] == FINISH)
           {
               struct vector2 ret = { i, j };
               return ret;
           }
       }
   }
   struct vector2 error =
   {
       -1, -1
   };
   return error;
}

/* Function that draws the shape of the path found with Dijkstra's in cache */
static void draw_cache(struct dijmap *dijmap, float *cache, struct vector2 pos)
{
    int index = pos.y * dijmap->width + pos.x;
    cache[index] = 1;
    if (!dijmap->floor[index])
        return;
    struct vector2 next = min_around(dijmap, pos);
    draw_cache(dijmap, cache, next);
}

/* Function that sets to -1 all the unneccessary cells of dijmap */
static void dijmap_clean(struct dijmap *dijmap, struct map *map)
{
    unsigned wihe = dijmap->width * dijmap->height;
    float *cache = malloc(sizeof (float) * wihe);
    for (unsigned i = 0; i < wihe; i++)
        cache[i] = 0;

    struct vector2 end = find_end(map);
    draw_cache(dijmap, cache, end);

    for (unsigned i = 0; i < wihe; i++)
    {
        if (!cache[i])
            dijmap->floor[i] = -1;
    }
}

/* Function that gathers all the other functions */
struct dijmap *dijkstra(struct map *map)
{
    struct dijmap *dijmap = dijmap_init(map);

    dijmap_build(dijmap, map);
    dijmap_clean(dijmap, map);

    return dijmap;
}
