#include "control.h"
#include "granny.h"
#include "include.h"
#include <stdlib.h>

/* Structure used to store the current situation of the process */
struct situation
{
    struct vector2 *next;
    struct dijmap *dijmap;
    int end;
};

struct situation situation =
{
    NULL,
    NULL,
    0
};

/* Converts a floating position to the coordinates of the cell around it */
static struct vector2 pos_cell(struct vector2 pos)
{
    struct vector2 ret =
    {
        (float)(int)pos.x, (float)(int)pos.y
    };  
        return ret;
}

/* Initializes the situation structure */
static void situation_init(struct map *map)
{
    if (situation.end)
        return;

    situation.next = malloc(sizeof (struct vector2));
    struct vector2 start = pos_cell(map->start);
    situation.next->x = start.x;
    situation.next->y = start.y;

    situation.dijmap = dijkstra(map);
}

/* Frees situation */
void situation_free()
{
    situation.end = 1;
    free(situation.next);
    free(situation.dijmap->floor);
    free(situation.dijmap);
}

/* Function that returns an instruction for the car, called every frame */
enum move update(struct car *car)
{
    if (situation.end)
        return DO_NOTHING;

    // At the beginning: initializes situation
    if (!situation.dijmap)
        situation_init(car->map);

    // Converts the car's coordinates into int coordinates
    struct vector2 cur = pos_cell(car->position);

    // Creates other variables
    struct dijmap *dijmap = situation.dijmap;
    float *floor = dijmap->floor;
    int width = dijmap->width;
    int height = dijmap->height;
    int cur_pos = cur.y * width + cur.x;

    if (floor[cur_pos] == -2)
    {
        situation_free();
        return DO_NOTHING;
    }

    // If the 'next' point has been reached, get the next 'next'
    if (cur.x == situation.next->x && cur.y == situation.next->y)
    {
        // Searches in the 8 cells around the next point (cur_pos = next)
        for (int j = cur.y - 1; j <= cur.y + 1; j++)
        {
            for (int i = cur.x - 1; i <= cur.x + 1; i++)
            {
                if (i < 0 || i >= width
                 || j < 0 || j >= height
                 || (i == cur.x && j == cur.y))
                    continue;

                if (floor[j * width + i] == -2
                 || floor[j * width + i] > floor[cur_pos])
                {
                    situation.next->x = i;
                    situation.next->y = j;
                    break;
                }
            }
        }
    }

    // Makes the car go to situation.next
    return granny(car, *situation.next);
}
