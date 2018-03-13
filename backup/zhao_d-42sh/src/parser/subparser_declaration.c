/**
** \file subparser_declaration.c
** \brief C file containing the functions to subparse and create
         DECLARATION nodes
** \author depott_g
*/

#include "parser.h"

int subparse_declaration(char **cmd, size_t size,
                                 struct AST *previous, enum child direction)
{
    // Checks the syntax
    if (!cmd[2])
    {
        warnx("Cannot find right operand of declaration");
        return 0;
    }
    if (cmd[3] && strcmp(cmd[3], "\n") && strcmp(cmd[3], ";"))
        parse_rec(cmd + 4, size - 4, previous, direction);

    // Creates a DECLARATION AST node and links it to the rest of the expression
    struct AST *A = ast_create(DECLARATION, cmd, 1);
    previous->children[direction] = A;

    // Calls the parser on the related expression
    if (!subparse_string(cmd + 2, 1, A, RIGHT))
        return 0;
    return parse_rec(cmd + 4, size - 4, A, NEXT);
}
