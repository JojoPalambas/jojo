#include "rt.h"

/* Write the infos given by the struct ppm to the ppm file. */
void print_out(struct ppm *ppm, FILE *file)
{
  fprintf(file, "P3\n%d %d\n255\n", ppm->width, ppm->height);
  for (int i = 0; i < ppm->height; i++)
  {
    for (int j = 0; j < ppm->width; j++)
    {
      struct rgb cur_pix = ppm->pixels[i * ppm->width + j];

      fprintf(file, "%d %d %d ", cur_pix.r, cur_pix.g, cur_pix.b);
    }
    fprintf(file, "\n");
  }
}

/* Create the ppm file, call print_out and close the ppm file. */
int make_out(struct ppm *ppm, char *output)
{
  FILE *file = NULL;

  file = fopen(output, "w");
  if (!file)
    return -1;

  print_out(ppm, file);

  if (fclose(file))
    return -1;
  
  return 0;
}
