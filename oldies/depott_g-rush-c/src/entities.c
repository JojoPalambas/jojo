#include "entities.h"

void monster_init(struct global *global, struct vector2 pos,
                                          SDL_Texture *texture)
{
    struct entity *monster = malloc(sizeof(struct entity));
    monster->type = MONS;
    monster->v_dir = LEFT;
    monster->dir.x = 1.0f;
    monster->dir.y = 0.0f;
    monster->pos = pos;
    monster->speed = MONSTER_SPEED;
    monster->pv = 3;
    monster->texture = texture;
    monster->width = 70;
    monster->height = 70;

    global->monsters = realloc(global->monsters,
                            sizeof (struct entity) * (global->nb_monsters + 1));
    global->monsters[global->nb_monsters] = monster;
    global->nb_monsters++;
}

struct entity *player_init(struct vector2 pos, SDL_Texture *texture)
{
  struct entity *player = calloc(1, sizeof(struct entity));
  player->type = CHARACTER;
  player->v_dir = DOWN;
  player->dir.x = 1.0f;
  player->dir.x = 0.0f;
  player->pos.x = pos.x;
  player->pos.y = pos.y;
  player->speed = 2;
  player->pv = 5;
  player->texture = texture;
  player->width = 30;
  player->height = 40;
  player->armed = 0;
  player->sword = calloc(1, sizeof(struct sword));
  player->sword->v_dir = DOWN;
  player->sword->pos = player->pos;
  player->sword->step = -1;
  player->sword->width = 30;
  player->sword->height = 30;
  player->sword->cooldown = 0;
  return player;
}

unsigned v2_norm(struct vector2 vect)
{
  return sqrt(vect.x * vect.x + vect.y * vect.y);
}

void update_monster(struct global *global, struct entity *mon, 
                                                            struct vector2 goal)
{
  struct vector2 new_dir;
  new_dir.x = goal.x - mon->pos.x;
  new_dir.y = goal.y - mon->pos.y;

  if (new_dir.x != 0)
    new_dir.x /= v2_norm(new_dir);
  if (new_dir.y != 0)
    new_dir.y /= v2_norm(new_dir);
  mon->dir.x = new_dir.x;
  mon->dir.y = new_dir.y;

  int angle = atan2(mon->dir.x, mon->dir.y);
  if (angle > -MY_PI/2 && angle <= MY_PI/2)
    mon->v_dir = RIGHT;
  else
    mon->v_dir = LEFT;

  int divisor = global->swords[0] ? 2 : 1;
  struct vector2 new_pos;
  new_pos.x = mon->pos.x + new_dir.x * mon->speed / divisor;
  new_pos.y = mon->pos.y + new_dir.y * mon->speed / divisor;
  mon->pos.x = new_pos.x;
  mon->pos.y = new_pos.y;

  // Update orientation
  if (goal.x < mon->pos.x)
      mon->v_dir = LEFT;
  else
      mon->v_dir = RIGHT;
}

void flee(struct entity *mon, struct vector2 repulsor)
{
  if (mon->pos.x == repulsor.x && mon->pos.y == repulsor.y)
      return;

  struct vector2 new_dir;
  new_dir.x = repulsor.x - mon->pos.x;
  new_dir.y = repulsor.y - mon->pos.y;
  new_dir.x /= v2_norm(new_dir);
  new_dir.y /= v2_norm(new_dir);

  mon->pos.x -= new_dir.x * mon->speed;
  mon->pos.y -= new_dir.y * mon->speed;
}
