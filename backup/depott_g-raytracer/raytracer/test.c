#include "rt.h"
#include "test.h"

void test_d_lights(struct global *global)
{
  printf("\nD_lights:\n");
  pritnf("%f %f %f\n", global->p_lights->color.x, global->p_lights->color.y,
                       global->p_lights->color.z);
}

void test_p_lights(struct global *global)
{
  printf("\nP_lights:\n");
  printf("%f %f %f\n",global->p_lights->color.x, global->p_lights->color.y,
                     global->p_lights->color.z);
}

void test_a_light(struct global *global)
{
  printf("\nA_light;\n");
  printf("%f %f %f\n", global->a_light->color.x, global->a_light->color.y,
                     global->a_light->color.z);
}

void test_camera(struct global *global)
{
  printf("\nCamera:\n");
  printf("%d %d ", global->camera->width, global->camera->height);
  printf("%f %f %f ", global->camera->pos.x, global->camera->pos.y,
                      global->camera->pos.z);
  printf("%f %f %f ", global->camera->ortho1.x, global->camera->ortho1.y,
                      global->camera->ortho1.z);
  printf("%f %f %f ", global->camera->ortho2.x, global->camera->ortho2.y,
                      global->camera->ortho2.z);
  printf("%f\n", global->camera->fov);
}

void test(struct global *global)
{
  printf("Tests:\n");
  test_camera(global);
  test_a_light(global);
  test_p_lights(global);
  test_d_lights(global);
}
