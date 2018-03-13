/**
** \file subparser_while.c
** \brief C file containing the functions to subparse and create WHILE nodes
** \author depott_g
*/

#include "parser.h"

int subparse_while(char **cmd, size_t size,
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
        warnx("while statement: DO token not found");
        return 0;
    }

    int done_pos = find_target(cmd + 1, dones, loops, dones, 0);
    if (done_pos == -1)
    {
        warnx("while statement: DONE token not found");
        return 0;
    }

    if (done_pos < do_pos)
    {
        warnx("while statement: DO and DONE tokens in wrong order");
        return 0;
    }

    // Creates the WHILE node and puts it in the tree
    struct AST *A = ast_create(WHILE, NULL, 0);
    previous->children[direction] = A;

    // Operate recursive calls
    // size = do_pos because size = ["do" tok pos] - [condition start pos]
    if (!parse_rec(cmd + 1, do_pos, A, CONDITION))
        return 0;

    int do_size = done_pos - do_pos;
    do_size -= 1;
    if (!parse_rec(cmd + do_pos + 2, do_size, A, RIGHT))
        return 0;

    return parse_rec(cmd + done_pos + 2, size - done_pos - 2, A, NEXT);
}
