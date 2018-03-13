/*
** \file builtin.c
** \brief C file containing builtins and a function to find them
** \author depott_g
*/

#include "builtin.h"

int (*builtin_find(char *name))(char **)
{
    if (!strcmp(name, "echo"))
        return bi_echo;
    return NULL;
}

int bi_echo(char **args)
{
    size_t i = 1;
    int l_option = 0;
    for (; args[i] && !strcmp(args[i], "-n"); i++)
        l_option = 1;
    for (; args[i]; i++)
    {
        if (args[i + 1])
            printf("%s ", args[i]);
        else
            printf("%s%s", args[i], l_option ? "" : "\n");
    }
    return 0;
}
