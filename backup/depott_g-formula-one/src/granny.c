#include <stdio.h>
#include "granny.h"
#include "include.h"

/* Function that computes the distance from (0, 0) to (i, j) */
static struct vector2 diff(struct vector2 src, struct vector2 dst)
{
    struct vector2 ret =
    {
        dst.x - src.x,
        dst.y - src.y
    };

    return ret;
}

/* Function that computes the norm of a vector2 */
static float norm(struct vector2 vect)
{
    return sqrt(vect.x * vect.x + vect.y * vect.y);
}

/* Function that computes the dot product of two vector2 */
static float scal_prod(struct vector2 src, struct vector2 dst)
{
    return src.x * dst.x + src.y * dst.y;
}

/* Function that computes the angle between two vector2 */
static float angle(struct vector2 src, struct vector2 dst)
{
    float ret = acos(scal_prod(src, dst) / (norm(src) * norm(dst)));
    return ret;
}

/*
** Function that returns 1 if next_pos is on the left of the car (looking at
** both its position and direction), -1 if it's on the right, else 0
*/
static int is_left(struct car *car, struct vector2 next_pos)
{
    next_pos.x += 0.5;
    next_pos.y += 0.5;
    struct vector2 next_relat_pos = diff(car->position, next_pos);
    // float ref_angle = angle(car->direction, next_relat_pos);

    struct vector2 rot_left =
    {
        -next_relat_pos.y,
        next_relat_pos.x
    };

    struct vector2 rot_right =
    {
        next_relat_pos.y,
        -next_relat_pos.x
    };

    float mid_angle = angle(car->direction, next_relat_pos);
    float left_angle = angle(car->direction, rot_left);
    float right_angle = angle(car->direction, rot_right);
    float diff_angle = right_angle - left_angle;

    float quant = 0.03;

    if (diff_angle <= quant && diff_angle >= -quant)
    {
        if (mid_angle <= quant && mid_angle >= -quant)
            return 0;
        return 1;
    }
    if (diff_angle > 0)
        return 1;
    if (diff_angle < 0)
        return -1;
    return 0;
}

/* Function that returns the next instruction regarding */
enum move granny(struct car *car, struct vector2 next_pos)
{
    float max_speed = 0.03;

    int left = is_left(car, next_pos);
    if (left == 1)
    {
        return TURN_LEFT;
    }
    if (left == -1)
    {
        return TURN_RIGHT;
    }
    if (norm(car->speed) >= max_speed)
    {
        return DO_NOTHING;
    }
    return ACCELERATE;
}
