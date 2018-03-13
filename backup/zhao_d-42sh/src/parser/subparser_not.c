/**
** \file subparser_basics.c
** \brief C file containing the functions to subparse and create NOT nodes
** \author depott_g
*/

#include "parser.h"

size_t exclamation_scope(char **cmd)
{
    int level = 0;
    size_t i = 0;
    for (;; i++)
    {
        if (!cmd[i])
            return i;
        else if (!strcmp(cmd[i], "(") || !strcmp(cmd[i], "{"))
            level++;
        else if (!strcmp(cmd[i], ")") || !strcmp(cmd[i], "}"))
        {
            if (level <= 0)
                return i;
            else
                level--;
        }
        else if (!strcmp(cmd[i], ";") || !strcmp(cmd[i],"\n"))
        {
            if (level <= 0)
                return i + 1;
        }
    }
    // Never reached
    return i;
}

int subparse_not(char **cmd, size_t size,
                         struct AST *previous, enum child direction)
{
    // Creates a NOT AST node and links it to the rest of the expression
    struct AST *A = ast_create(NOT, NULL, 0);
    previous->children[direction] = A;

    // Calls the parser on the related expression
    size_t scope = exclamation_scope(cmd + 1);
    if (!parse_rec(cmd + 1, scope, A, RIGHT))
        return 0;
    return parse_rec(cmd + 1 + scope, size - 1 - scope, A, NEXT);
}
