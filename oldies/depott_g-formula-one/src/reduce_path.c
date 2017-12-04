#include <stdio.h>
#include <stdlib.h>

#include "granny.h"
#include "include.h"

/* Return the distance between u and v. */
float dist_u_v(struct vector2 u, struct vector2 v)
{
  float dist = sqrt(((v.x - u.x) * (v.x - u.x)) + ((v.y - u.y) * (v.y - u.y)));
  return dist;
}

/*
** Calculate the angle between 3 points and return 1 if they are aligned,
** else return 0.
*/
int cut(struct vector2 u, struct vector2 v, struct vector2 w)
{
  /* Call dist_u_v() to find the distances (u-v), (v-w) and (w-u). */
  float dist_uv = dist_u_v(u, v);
  float dist_vw = dist_u_v(v, w);
  float dist_wu = dist_u_v(w, u);

  /* Find the angle (uvw). */
  float angle = acos((dist_uv * dist_uv + dist_vw * dist_vw - dist_wu
                     * dist_wu) / (2 * dist_uv * dist_wu));

  /* Return 1 if the 3 points are aligned. */
  if (angle < 0.05 && angle > -0.05)
    return 1;
  else
    return 0;
}

/*
** Delete the useless points in tab.
** Example: if a, b and c are aligned then delete b.
*/
void reduce_cut_tab(struct vector2 *tab, int *count)
{
  int i = 0;

  while (i < *count - 2)
  {
    if (cut(tab[i], tab[i + 1], tab[i + 2]))
    {
      for (int j = i + 1; j < *count - 1; j++)
      {
        tab[j] = tab[j + 1];
      }
      *count = *count - 1;
    }
    else
      i++;
  }
}

/*
** Fill table whith the path found in dijmap and call reduce_cut-tab to
** reduce it.
*/
int make_cut_tab(struct dijmap *dijmap, struct vector2 *tab)
{
  int count = 0;
  int end = 100;

  for (int i = 0; i < dijmap->width * dijmap->height; i++)
  {
    if (dijmap[i] > -1)
    {
      count++;
      if (count >= 100)
      {
        end *= 2;
        struct vector2 *tmp = realloc(tab, end * sizeof(struct vector2));
        if (!tmp)
          return -1;
        else
          tab = tmp;
      }
      tab[i].x = i / dijmap->height;
      tab[i].y = i % dijmap->width;
    }
  }

  reduce_cut_tab(tab, &count);
  return 0;
}

/*
** Create tab and call make_cut_tab to fill it.
** Return -1 if an error occured, else return 0.
*/
int make_cut_path(struct dijmap *dijmap, struct map *map)
{
  struct vector2 *tab = malloc(100 * sizeof(struct vector2));
  if (!tab)
    return -1;

  if (make_cut_tab(dijmap, tab) == -1)
    return -1;

  map = map;
  return 0;
}
