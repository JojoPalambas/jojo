#ifndef MAPS_H
# define MAPS_H

#include <stdlib.h>


enum floortype
{
  STONE = 0,    //.
  FLOWER = 1,   //f
  FIRE = 2,     //b
  WALL = 3,     //w
  VOID = 4,     //v
  START = 5,    //s
  MONSTER = 6,  //m
  TRAP = 7,     //t
  SWORD = 8     //e
};

struct vector2
{
  float x;
  float y;
};

struct map
{
  enum floortype *light;
  enum floortype *dark;
  size_t width;
  size_t height;
  struct vector2 start;
};

struct map *parse_map(const char *path);
enum floortype get_map_floor(struct map *map, int light, int i, int j);
#endif
