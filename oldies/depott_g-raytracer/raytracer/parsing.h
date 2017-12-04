#ifndef PARSING_H
#define PARSING_H

#include "structures.h"

/*
** Fill the given global structure with the informations from the input file.
** Return -1 if an error occured, else return 0.
*/
struct global *parsing(const char *path);

#endif
