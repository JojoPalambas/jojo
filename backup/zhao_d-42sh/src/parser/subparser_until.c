/**
** \file subparser_until.c
** \brief C file containing the functions to subparse and create WHILE nodes
** \author depott_g
*/

#include "parser.h"

int subparse_until(char **cmd, size_t size,
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

    // Searches for do and done tokens and throws errors if not found
    int do_pos = find_target(cmd + 1, dos, loops, dones, 0);
    if (do_pos == -1)
    {
        warnx("until statement: DO token not found");
        return 0;
    }

    int done_pos = find_target(cmd + 1, dones, loops, dones, 0);
    if (done_pos == -1)
    {
        warnx("until statement: DONE token not found");
        return 0;
    }

    if (done_pos < do_pos)
    {
        warnx("until statement: DO and DONE tokens in wrong order");
        return 0;
    }

    // Creates the IF node and puts it in the tree
    struct AST *A = ast_create(WHILE, NULL, 0);
    previous->children[direction] = A;

    // Puts the condition in the tree
    struct AST *N = ast_create(NOT, NULL, 0);
    A->children[CONDITION] = N;
    if (!parse_rec(cmd + 1, do_pos, N, RIGHT))
        return 0;

    // Manages the content of the loop with a NOT node
    if (!parse_rec(cmd + do_pos + 2, done_pos - do_pos - 1, A, RIGHT))
        return 0;

    return parse_rec(cmd + done_pos + 2, size - done_pos - 2, A, NEXT);
}
