/**
** \file subparser_pipe.c
** \brief C file containing the functions to subparse and create PIPE nodes
** \author depott_g
*/

#include "parser.h"

int subparse_pipe(char **cmd, size_t size,
                          struct AST *previous, enum child direction);
