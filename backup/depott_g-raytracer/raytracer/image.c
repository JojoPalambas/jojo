#include "rt.h"

#define M_PI 3.141592

static struct ppm *ppm_init(struct global *global)
{
    struct ppm *ppm = malloc(sizeof (struct ppm));
    if (!ppm)
    {
        fprintf(stderr, "Cannot allocate memory for ppm.\n");
        exit(1);
    }

    ppm->width = global->camera->width;
    ppm->height = global->camera->height;
    ppm->pixels = malloc(sizeof (struct rgb) * ppm->width * ppm->height);
    if (!ppm->pixels)
    {
        fprintf(stderr, "Cannot allocate memory for pixel table.\n");
        exit(1);
    }

    return ppm;
}

struct ppm *compute_image(struct global *global)
{
    struct vector3 campos = global->camera->pos;
    struct ppm *ppm = ppm_init(global);

    // Unitary vectors describing the plan of the screen and normal vector
    struct vector3 u = v3_normalize(global->camera->ortho1);
    struct vector3 v = v3_normalize(global->camera->ortho2);
    struct vector3 w = v3_crossprod(u, v);

    // Because z is backwards
    w.x = -w.x;
    w.y = -w.y;
    w.z = -w.z;

    // Distance from the camera to the screen
    float L = ppm->width /
        (2 * tan((global->camera->fov * 2 * M_PI / 360) / 2));

    // Center of the screen
    struct vector3 C = v3_sum(campos, v3_floatprod(w, L));

    // For every pixel of the screen
    for (int i = 0; i < ppm->width * ppm->height; i++)
    {
        // Coordinates of the current pixel
        int x = i % ppm->width;
        int y = i / ppm->width;

        x -= ppm->width / 2;
        y -= ppm->height / 2;

        // 3D position of the current pixel and direction of the ray
        struct vector3 pix_pos = v3_sum(C, v3_sum(v3_floatprod(u, x),
                                                  v3_floatprod(v, y)));
        struct vector3 cur_dir = v3_sum(pix_pos,
                                        v3_floatprod(campos, -1));
        cur_dir = v3_normalize(cur_dir);

        float mindist = -1;
        struct vector3 closest_ka =
        {
            0, 0, 0
        };

        // For every object of the scene
        struct llist *objects = global->objects;
        while (objects)
        {
            struct object *obj = objects->data;

            // For every triangle of the object
            struct llist *triangles = obj->triangles;
            while (triangles)
            {
                // Variables made to shorten the code and make it easier to read
                struct triangle *tri = triangles->data;
                struct vector3 n = tri->vn[0];
                struct vector3 A = tri->v[0];
                struct vector3 B = tri->v[1];
                struct vector3 C = tri->v[2];

                float a = n.x;
                float b = n.y;
                float c = n.z;
                float d = -a * A.x - b * A.y - c * A.z;

                float nr = v3_dotprod(n, cur_dir);
                // If the ray is parallel to the plane of the triangle
                if (nr <= 0)
                {
                    triangles = triangles->next;
                    continue;
                }

                float t0 = -((v3_dotprod(n, campos) + d) / nr);
                // If the ray comes from the wrong side
                if (t0 < 0)
                {
                    triangles = triangles->next;
                    continue;
                }

                // Variables made to shorten the code and make it easier to read
                struct vector3 AB = v3_sum(B, v3_floatprod(A, -1));
                struct vector3 AC = v3_sum(C, v3_floatprod(A, -1));
                struct vector3 BC = v3_sum(C, v3_floatprod(B, -1));
                struct vector3 BA = v3_sum(A, v3_floatprod(B, -1));
                struct vector3 CA = v3_sum(A, v3_floatprod(C, -1));
                struct vector3 CB = v3_sum(B, v3_floatprod(C, -1));

                // Point of intersection of the ray and the plane
                struct vector3 P = v3_sum(campos, v3_floatprod(cur_dir, t0));
                struct vector3 AP = v3_sum(P, v3_floatprod(A, -1));
                struct vector3 BP = v3_sum(P, v3_floatprod(B, -1));
                struct vector3 CP = v3_sum(P, v3_floatprod(C, -1));

                // If P is in the triangle
                if (v3_dotprod(v3_crossprod(CA, CB), v3_crossprod(CP, CB)) >= 0
                 && v3_dotprod(v3_crossprod(BC, BA), v3_crossprod(BP, BA)) >= 0
                 && v3_dotprod(v3_crossprod(AB, AC), v3_crossprod(AP, AC)) >= 0)
                {
                    float dist = v3_norm(v3_sum(P, v3_floatprod(campos, -1)));
                    if (mindist > dist || mindist == -1)
                    {
                        mindist = dist;
                        closest_ka.x = obj->material->ka.x * global->a_light->color.x;
                        closest_ka.y = obj->material->ka.y * global->a_light->color.y;
                        closest_ka.z = obj->material->ka.z * global->a_light->color.z;
                    }
                }
                triangles = triangles->next;
            }
            objects = objects->next;
        }
        // Put the color in the screen
        struct rgb ret_color =
        {
            closest_ka.x * 255,
            closest_ka.y * 255,
            closest_ka.z * 255
        };
        ppm->pixels[i] = ret_color;
    }
    return ppm;
}
