#include "entities.h"

void fire_init(struct global *global, struct vector2 pos, SDL_Texture *texture)
{
  global->fires = realloc(global->fires,
                          (global->nb_fires + 1) * sizeof(struct block *));
  global->fires[global->nb_fires] = calloc(1, sizeof(struct block));
  global->fires[global->nb_fires]->type = B_FIRE;
  global->fires[global->nb_fires]->pos.x = pos.x;
  global->fires[global->nb_fires]->pos.y = pos.y;

  global->fires[global->nb_fires]->texture = texture;
  global->fires[global->nb_fires]->width = 50;
  global->fires[global->nb_fires]->height = 50;
  global->nb_fires++;
}

void penta_init(struct global *global, struct vector2 pos, SDL_Texture *texture,
                                                                      int proba)
{
  global->pentas = realloc(global->pentas, (global->nb_pentas + 1) *
                                                       sizeof(struct block *));
  global->pentas[global->nb_pentas] = calloc(1, sizeof(struct block));
  global->pentas[global->nb_pentas]->type = B_PENTA;
  global->pentas[global->nb_pentas]->pos.x = pos.x;
  global->pentas[global->nb_pentas]->pos.y = pos.y;
  global->pentas[global->nb_pentas]->texture = texture;
  global->pentas[global->nb_pentas]->width = 100;
  global->pentas[global->nb_pentas]->height = 100;
  global->pentas[global->nb_pentas]->proba = proba;
  global->nb_pentas++;
}

void sword_init(struct global *global, struct vector2 pos, SDL_Texture *texture)
{
  global->swords = realloc(global->swords, (global->nb_swords + 1) *
                                                       sizeof(struct block *));
  global->swords[global->nb_swords] = calloc(1, sizeof(struct block));
  global->swords[global->nb_swords]->type = B_SWORD;
  global->swords[global->nb_swords]->pos.x = pos.x;
  global->swords[global->nb_swords]->pos.y = pos.y;
  global->swords[global->nb_swords]->texture = texture;
  global->swords[global->nb_swords]->width = 24;
  global->swords[global->nb_swords]->height = 40;
  global->nb_swords++;
}
