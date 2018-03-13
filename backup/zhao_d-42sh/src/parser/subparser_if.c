/**
** \file subparser_if.c
** \brief C file containing the functions to subparse and create IF nodes
** \author depott_g
*/

#include "parser.h"

int find_in(const char *s, const char **list)
{
    if (!list || !*list)
        return 0;
    for (size_t i = 0; list[i]; i++)
    {
        if (!strcmp(s, list[i]))
            return 1;
    }
    return 0;
}

int find_target(char **cmd, const char **targets,
                const char **adders, const char **substracters, int for_do)
{
    int level = 0;
    int separator_found = 0;
    size_t i = 0;
    for (;; i++)
    {
        if (!cmd[i])
            return -1;
        if (!level && separator_found && find_in(cmd[i], targets))
            return i;
        if (for_do && separator_found)
            return -1;
        if (!strcmp(cmd[i], ";") || !strcmp(cmd[i], "\n"))
            separator_found = 1;
        if (find_in(cmd[i], adders))
            level++;
        if (find_in(cmd[i], substracters))
        {
            if (level <= 0)
                return -1;
            else
                level--;
        }
    }
    // Never reached
    return -1;
}

int subparse_if(char **cmd, size_t size,
                        struct AST *previous, enum child direction, int depth)
{
    // Variables used for token finding
    const char *ifs[] =
    {
        "if", NULL
    };
    const char *thens[] =
    {
        "then", NULL
    };
    const char *elses[] =
    {
        "else", "elif", NULL
    };
    const char *fis[] =
    {
        "fi", NULL
    };

    // Searches for then, else and fi tokens
    int then_pos = find_target(cmd + 1, thens, ifs, fis, 0);
    int else_pos = find_target(cmd + 1, elses, ifs, fis, 0);
    int fi_pos = find_target(cmd + 1, fis, ifs, fis, 0);

    // Throws errors if "then" or "fi" tokens not found
    if (then_pos == -1)
    {
        warnx("if statement: THEN token not found");
        return 1;
    }
    if (fi_pos == -1)
    {
        warnx("if statement: FI token not found");
        return 1;
    }
    if (fi_pos < else_pos || fi_pos < then_pos
        || (else_pos != -1 && else_pos < then_pos))
    {
        if (else_pos != -1)
            warnx("if statement: IF, THEN, ELSE, FI tokens in wrong order");
        else
            warnx("if statement: IF, THEN, FI tokens in wrong order");
        return 0;
    }

    // Creates the IF node and puts it in the tree
    struct AST *A = ast_create(IF, NULL, 0);
    previous->children[direction] = A;

    // Operate recursive calls
    // size = then_pos because size = ["then" tok pos] - [condition start pos]
    if (!parse_rec(cmd + 1, then_pos, A, CONDITION))
        return 0;

    int then_size = else_pos != -1 ? else_pos - then_pos : fi_pos - then_pos;
    then_size -= 1;
    if (!parse_rec(cmd + then_pos + 2, then_size, A, LEFT))
        return 0;

    if (else_pos != -1)
    {
        if (!strcmp(cmd[else_pos + 1], "elif"))
        {
            free(cmd[else_pos + 1]);
            cmd[else_pos + 1] = calloc(1, 3);
            strcpy(cmd[else_pos + 1], "if");
            if (!subparse_if(cmd + else_pos + 1, fi_pos - else_pos - 1,
                             A, RIGHT, depth + 1))
                return 0;
        }
        else if (!parse_rec(cmd + else_pos + 2,
                            fi_pos - else_pos - 1, A, RIGHT))
            return 0;
    }
    if (!depth)
        if (!parse_rec(cmd + fi_pos + 2, size - fi_pos - 2, A, NEXT))
            return 0;

    return 1;
}
