#ifndef ENTITIES_H
#define ENTITIES_H

/*==================================INCLUDES=================================*/

#include <stdlib.h>
#include <math.h>
#include "maps.h"
#include "game.h"

/*===================================MACROS==================================*/

#define MY_PI 3.141592
#define MONSTER_SPEED 1
#define SWORD_COOLDOWN 30

/*=================================STRUCTURES================================*/

enum entity_type
{
  CHARACTER,
  CHARACTER_WITH_FLOWER,
  MONS
};

enum direction
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

enum block_type
{
  B_FIRE,
  B_PENTA,
  B_SWORD
};

struct block
{
  enum block_type type;
  struct vector2 pos;
  SDL_Texture *texture;
  int width;
  int height;
  int proba;
};

struct sword
{
    enum direction v_dir;
    struct vector2 pos;
    int step;
    int width;
    int height;
    int cooldown;
};

struct entity
{
  enum entity_type type;
  enum direction v_dir;
  struct vector2 dir;
  struct vector2 pos;
  int speed;
  int pv;
  SDL_Texture *texture;
  int width;
  int height;
  int armed;
  struct sword *sword;
};

/*
 * Calculus for entity hitbox : 
 *          pos.y + height / 4 < y < pos.y + height
 *          pos.x < x < pos.x + width
*/

/*=================================FUNCTIONS=================================*/

struct entity *player_init(struct vector2 pos, SDL_Texture *texture);
void monster_init(struct global *global, struct vector2 pos,
                   SDL_Texture *texture);
void player_sword_init(struct global *global, struct vector2 pos,
                       enum direction direction);
void update_monster(struct global *global, struct entity *monster, struct vector2 goal);
void flee(struct entity *monster, struct vector2 repulsor);

#endif
