#ifndef TEST_H_
# define TEST_H_

# include <stdio.h>
# include <stdlib.h>

struct map *map_new(int width, int height, float sx, float sy);
void map_set_floor(struct map *self, enum floortype type, int x, int y);
void map_delete(struct map *self);

#endif /* TEST_H_ */
