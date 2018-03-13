/**
** \file subparser_redirections.c
** \brief C file containing the functions to subparse and create
         REDIRECTION nodes
** \author depott_g
*/

#include "parser.h"

int subparse_redirection(char **cmd, size_t size,
                                 struct AST *previous, enum child direction);
