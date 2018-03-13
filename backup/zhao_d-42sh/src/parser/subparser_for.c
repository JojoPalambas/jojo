/**
** \file subparser_for.c
** \brief C file containing the functions to subparse and create FOR nodes
** \author depott_g
*/

#include "parser.h"

int subparse_for(char **cmd, size_t size,
                           struct AST *previous, enum child direction)
{
    // Variables used for token finding
    const char *loops[] =
    {
        "while", "until", "for", NULL
    };
    const char *dos[] =
    {
        "do", NULL
    };
    const char *dones[] =
    {
        "done", NULL
    };

    // Searches for in, do and done tokens and throws errors if not found
    if (strcmp(*(cmd + 2), "in"))
    {
        warnx("for statement: IN token not found or not at the right place");
        return 0;
    }
    int do_pos = find_target(cmd + 1, dos, loops, dones, 1);
    if (do_pos == -1)
    {
        warnx("for statement: DO token not found");
        return 0;
    }

    int done_pos = find_target(cmd + 1, dones, loops, dones, 0);
    if (done_pos == -1)
    {
        warnx("for statement: DONE token not found");
        return 0;
    }

    if (done_pos < do_pos)
    {
        warnx("for statement: DO and DONE tokens in wrong order");
        return 0;
    }

    // Creates the FOR node, fills it with the variable and puts it in the tree
    struct AST *A = ast_create(FOR, cmd + 1, 1);
    previous->children[direction] = A;

    // Operate recursive calls
    if (!subparse_string(cmd + 3, do_pos - 3, A, CONDITION))
        return 0;

    int do_size = done_pos - do_pos - 1;
    if (!parse_rec(cmd + do_pos + 2, do_size, A, RIGHT))
    return 0;

    return parse_rec(cmd + done_pos + 2, size - done_pos - 2, A, NEXT);
}
