#include "rt.h"

static void light_free(void *light)
{
    struct p_light *pl = light;
    free(pl);
}

static void triangle_free(void *triangle)
{
    struct triangle *tr = triangle;
    free(tr);
}

static void object_free(void *object)
{
    struct object *obj = object;
    free(obj->material);
    llist_apply(obj->triangles, triangle_free);
    llist_free(obj->triangles);
}

void global_free(struct global *global)
{
    free(global->camera);

    free(global->a_light);

    llist_apply(global->p_lights, light_free);
    llist_free(global->p_lights);

    llist_apply(global->d_lights, light_free);
    llist_free(global->d_lights);

    llist_apply(global->objects, object_free);
    llist_free(global->objects);
}

int main(int argc, char *argv[])
{
  if (argc == 3)
  {
    struct global *global = parsing(argv[1]);

    /*char s[256];
    printf("%s %d %d %f %f %f %f %f %f %f %f %f %f", s,
            global->camera->width, global->camera->height,
            global->camera->pos.x, global->camera->pos.y, global->camera->pos.z,
            global->camera->ortho1.x, global->camera->ortho1.y,
            global->camera->ortho1.z, global->camera->ortho2.x,
            global->camera->ortho2.y, global->camera->ortho2.z,
            global->camera->fov);*/

    struct ppm *ppm = compute_image(global);
    ppm = ppm;
    make_out(ppm, argv[2]);
    //global_free(global);
  }
  else
  {
    fprintf(stderr, "The program should be used like: ./rt input output\n");
    return 1;
  }

  return 0;
}
