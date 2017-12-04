#include "rt.h"

float v3_norm(struct vector3 v3)
{
    float ret = v3.x * v3.x
              + v3.y * v3.y
              + v3.z * v3.z;
    ret = sqrt(ret);
    return ret;
}

struct vector3 v3_normalize(struct vector3 v3)
{
    float norm = v3_norm(v3);
    struct vector3 ret =
    {
        v3.x / norm,
        v3.y / norm,
        v3.z / norm
    };
    return ret;
}

float v3_dotprod(struct vector3 va3, struct vector3 vb3)
{
    return va3.x * vb3.x + va3.y * vb3.y + va3.z * vb3.z;
}

struct vector3 v3_crossprod(struct vector3 va3, struct vector3 vb3)
{
    struct vector3 prod =
    {
        va3.y * vb3.z - va3.z * vb3.y,
        va3.z * vb3.x - va3.x * vb3.z,
        va3.x * vb3.y - va3.y * vb3.x
    };
    return prod;
}

struct vector3 v3_sum(struct vector3 va3, struct vector3 vb3)
{
    struct vector3 ret =
    {
        va3.x + vb3.x,
        va3.y + vb3.y,
        va3.z + vb3.z
    };
    return ret;
}

struct vector3 v3_floatprod(struct vector3 v3, float f)
{
    struct vector3 ret =
    {
        v3.x * f,
        v3.y * f,
        v3.z * f
    };
    return ret;
}
