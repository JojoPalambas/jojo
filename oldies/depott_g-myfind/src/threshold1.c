#include "include.h"

/* Function that makes the program the directory content before its name */
int func_d(struct command *cmd)
{
    cmd->reverse = 1;
    return 1;
}
