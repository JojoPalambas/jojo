#include "rt.h"

int my_strcmp(char *a, char *b)
{
  int i = 0;
  int j = 0;
  int result = 1;

  while (result && a[i] && b[j])
  {
    if (a[i] != b[j])
      result = 0;
    i++;
    j++;
  }

  if (a[i] || b[j])
    result = 0;

  return result;
}

void obj_mat_init(struct object *obj)
{
  obj->material->ka.x = 0.;
  obj->material->ka.y = 0.;
  obj->material->ka.z = 0.;
  obj->material->kd.x = 0.;
  obj->material->kd.y = 0.;
  obj->material->kd.z = 0.;
  obj->material->ks.x = 0.;
  obj->material->ks.y = 0.;
  obj->material->ks.z = 0.;
  obj->material->ns = 0.;
  obj->material->ni = 1.0;
  obj->material->nr = 0.0;
  obj->material->d = 1.0;
}

int read_triangles(FILE *file, struct object *obj, int obj_n, char *tmp)
{
  struct vector3 *v = malloc(sizeof(struct vector3) * obj_n);
  if (!v)
    return -1;
  struct vector3 *vn = malloc(sizeof(struct vector3) * obj_n);
  if (!vn)
    return -1;
  char t_tmp[256];
  int test = 0;

  int v_i = 0;
  int vn_i = 0;
  for (int i = 1; i <= obj_n * 2; i++)
  {
    if ((!test && my_strcmp(tmp, "v")) || (test && my_strcmp(t_tmp, "v")))
    {
      struct vector3 vect;
      fscanf(file, "%f %f %f", &vect.x, &vect.y, &vect.z);
      v[v_i] = vect;
      v_i++;
    }
    if ((!test && my_strcmp(tmp, "vn")) || (test && my_strcmp(t_tmp, "vn")))
    {
      struct vector3 vect;
      fscanf(file, "%f %f %f", &vect.x, &vect.y, &vect.z);
      vn[vn_i] = vect;
      vn_i++;
    }
    fscanf(file, "%s", t_tmp);
    test = 1;
  }

  for (int i = 0; i < obj_n; i += 3)
  {
    struct triangle *triangle = malloc(sizeof (struct triangle));
    for (int j = 0; j < 3; j++)
    {
      triangle->v[j] = v[i + j];
      triangle->vn[j] = v[i + j];
    }
    obj->triangles = llist_push(obj->triangles, triangle);
  }

  free(v);
  free(vn);

  return 0;
}

char *read_material(FILE *file, struct object *obj)
{
  char *tmp = malloc(sizeof(char) * 256);

  fscanf(file, "%s", tmp);
  while (!my_strcmp(tmp, "v"))
  {
    if (my_strcmp(tmp, "Ka"))
      fscanf(file, "%f %f %f", &obj->material->ka.x, 
             &obj->material->ka.y, &obj->material->ka.z);
    if (my_strcmp(tmp, "Kd"))
      fscanf(file, "%f %f %f", &obj->material->kd.x, 
             &obj->material->kd.y, &obj->material->kd.z);
    if (my_strcmp(tmp, "Ks"))
      fscanf(file, "%f %f %f", &obj->material->ks.x, 
             &obj->material->ks.y, &obj->material->ks.z);
    if (my_strcmp(tmp, "Ns"))
      fscanf(file, "%f", &obj->material->ns);
    if (my_strcmp(tmp, "Nr"))
      fscanf(file, "%f", &obj->material->nr);
    if (my_strcmp(tmp, "Ni"))
      fscanf(file, "%f", &obj->material->ni);
    if (my_strcmp(tmp, "d"))
      fscanf(file, "%f", &obj->material->d);
    fscanf(file, "%s", tmp);
  }

  if (my_strcmp(tmp, "v"))
    return "v";
  if (my_strcmp(tmp, "vn"))
    return "vn";
  else
    return "not v or vn";
}

void read_object_number(FILE *file, int *obj_n)
{
  fscanf(file, "%d", obj_n);
}

int read_lights(FILE *file, struct global *global)
{
  char tmp[256];
  
  fscanf (file, "%s", tmp);
  while (!my_strcmp(tmp, "object"))
  {
    if (my_strcmp(tmp, "a_light"))
      fscanf(file, "%f %f %f", &global->a_light->color.x, 
             &global->a_light->color.y, &global->a_light->color.z);
    if (my_strcmp(tmp, "p_light"))
    {
      struct p_light *p = malloc(sizeof(struct p_light));
      if (!p)
        return -1;
      fscanf(file, "%f %f %f %f %f %f", &p->color.x, &p->color.y, &p->color.z,
             &p->pos.x, &p->pos.y, &p->pos.z);
      global->p_lights = llist_push(global->p_lights, p);
    }
    if (my_strcmp(tmp, "d_light"))
    {
      struct d_light *d = malloc(sizeof(struct d_light));
      if (!d)
        return -1;
      fscanf(file, "%f %f %f %f %f %f", &d->color.x, &d->color.y, &d->color.z,
             &d->dir.x, &d->dir.y, &d->dir.z);
      global->d_lights = llist_push(global->d_lights, d);
    }
    fscanf(file, "%s", tmp);
  }

  return 0;
}

void read_camera(FILE *file, struct global *global)
{
  char s[256];
  fscanf(file, "%s %d %d %f %f %f %f %f %f %f %f %f %f", s,
         &global->camera->width, &global->camera->height,
         &global->camera->pos.x, &global->camera->pos.y, &global->camera->pos.z,
         &global->camera->ortho1.x, &global->camera->ortho1.y,
         &global->camera->ortho1.z, &global->camera->ortho2.x,
         &global->camera->ortho2.y, &global->camera->ortho2.z,
         &global->camera->fov);
}

struct global *parsing(const char *path)
{
  struct global *global = malloc(sizeof(struct global));
  if (!global)
    return NULL;
  global->camera = malloc(sizeof(struct camera));
  if (!global->camera)
    return NULL;
  global->a_light = malloc(sizeof(struct a_light));
  if (!global->a_light)
    return NULL;

  FILE *file = NULL;

  file = fopen(path, "r");
  if (!file)
    return NULL;

  read_camera(file, global);
  if (read_lights(file, global) == -1)
    return NULL;

  int end = 0;

  while (!end)
  {
    struct object *obj = malloc(sizeof(struct object));
    if (!obj)
      return NULL;
    obj->material = malloc(sizeof(struct material));
    if (!obj->material)
      return NULL;

    obj_mat_init(obj);
    int obj_n = 0;
    read_object_number(file, &obj_n);
    char *tmp = read_material(file, obj);
    if (read_triangles(file, obj, obj_n, tmp) == -1)
      return NULL;
    global->objects = llist_push(global->objects, obj);
    if (!my_strcmp(tmp, "object"))
      end = 1;
  }
  if (fclose(file))
    return NULL;

  return global;
}
