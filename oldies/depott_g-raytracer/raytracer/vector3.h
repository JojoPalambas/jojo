#ifndef VECTOR3_H
#define VECTOR3_H

#include "structures.h"

/* Returns the norm of v3 */
float v3_norm(struct vector3 v3);

/* Returns a normalized copy of v3 */
struct vector3 v3_normalize(struct vector3 v3);

/* Returns the dot product of va3 and vb3 */
float v3_dotprod(struct vector3 va3, struct vector3 vb3);

/* Returns the cross product of va3 and vb3 */
struct vector3 v3_crossprod(struct vector3 va3, struct vector3 vb3);

/* Substracts vb3 to va3 and returns the result */
struct vector3 v3_sum(struct vector3 va3, struct vector3 vb3);

/* Returns f times v3 */
struct vector3 v3_floatprod(struct vector3 v3, float f);

#endif
