#ifndef STRUCTURES_H
#define STRUCTURES_H

struct vector3
{
    float x;
    float y;
    float z;
};

struct camera
{
    int width;
    int height;

    struct vector3 pos;

    struct vector3 ortho1;
    struct vector3 ortho2;

    float fov;
};

struct a_light
{
    struct vector3 color;
};

struct p_light
{
    struct vector3 color;
    struct vector3 pos;
};

struct d_light
{
    struct vector3 color;
    struct vector3 dir;
};

struct llist
{
    void *data;
    struct llist *next;
};

struct material
{
    struct vector3 ka;
    struct vector3 kd;
    struct vector3 ks;

    float ns;
    float ni;
    float nr;

    float d;
};

struct triangle
{
    struct vector3 v[3];
    struct vector3 vn[3];
};

struct object
{
    struct material *material;

    struct llist *triangles;
};

struct global
{
    struct camera *camera;
    
    struct a_light *a_light;
    struct llist *p_lights;
    struct llist *d_lights;

    struct llist *objects;
};

struct rgb
{
    int r;
    int g;
    int b;
};

struct ppm
{
    int width;
    int height;
    struct rgb *pixels;
};

#endif
