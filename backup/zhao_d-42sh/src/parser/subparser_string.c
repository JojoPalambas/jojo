/**
** \file subparser_string.c
** \brief C file containing the functions to subparse and create STRING nodes
** \author depott_g
*/

#include "parser.h"

int subparse_string(char **cmd, size_t size,
                         struct AST *previous, enum child direction)
{
    struct AST *A = ast_create(STRING, cmd, size);
    previous->children[direction] = A;
    return 1;
}
