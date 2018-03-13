/**
** \file subparser_expression.c
** \brief C file containing the functions to subparse and create EXPRESSION nodes
** \author depott_g
*/

#include "parser.h"

int is_expr_separator(char *s)
{
    return s[0] == ';' || s[0] == '\n';
}

int subparse_expression(char **cmd, size_t size,
                                struct AST *previous, enum child direction)
{
    // Finds the end of the expression
    size_t len = 1;
    for (; len < size && cmd[len] && !is_expr_separator(cmd[len]); len++);

    // Creates an AST node and stores the expression inside
    struct AST *A = ast_create(EXPRESSION, cmd, len);

    // Links the previous node to the current one
    previous->children[direction] = A;

    // Calls the parser on the next expression and returns
    if (len >= size || !cmd[len])
        return 1;
    return parse_rec(cmd + len + 1, size - len - 1, A, NEXT);
}
