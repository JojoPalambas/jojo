#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "maps.h"

void map_parse(struct global *global)
{
  char *pathname = global->maps[global->map];
  FILE *file = fopen(pathname, "r");
  if (!file)
    err(1, "cannot open");
  
  char *line = calloc(20, sizeof(char));
  
  fgets(line, 20, file);
  sscanf(line, "MG %d\n", &global->kill_count);

  fgets(line, 20, file);
  struct vector2 pl_pos;
  sscanf(line, "PS %f %f\n", &pl_pos.x, &pl_pos.y);

  global->start.x = pl_pos.x;
  global->start.y = pl_pos.y;


  while (fgets(line, 20, file))
  {
    if (!line[0])
      break;
    char c;
    struct vector2 pos;
    int prob;

    sscanf(line, "%c %f %f %d\n", &c, &pos.x, &pos.y, &prob);

    if (c == 'F')
    {
      fire_init(global, pos, global->block_textures[DFIRE]);
    }
    else if (c == 'P')
    {
      penta_init(global, pos, global->block_textures[DPENTA], prob);
    }
    else if (c == 'S')
    {
      sword_init(global, pos, global->block_textures[WSWORD]);
    }
  }
  free(line);
  fclose(file);
}
