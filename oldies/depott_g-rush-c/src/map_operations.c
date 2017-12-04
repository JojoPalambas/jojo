#include "maps.h"

enum floortype get_map_floor(struct map *map, int light, int i, int j)
{
  if (light)
    return map->light[i * map->width + j];
  return map->dark[i *map->width + j];
}
