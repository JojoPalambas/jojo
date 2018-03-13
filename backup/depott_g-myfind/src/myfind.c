/**
 * \file myfind.c
 * \brief Main function of the project.
 * \author depott_g
*/

#include "include.h"

/**
 * \fn int main(int argc, char **argv)
 * \brief Main functon that parses the command line and calls all the functions
 *        processing the files.
 * \param argc Number of arguments.
 *        argv Array of arguments.
*/
int main(int argc, char **argv)
{
    struct command *cmd = parse(argc, argv);
    if (argc == 1 || cmd->files_end - cmd->files_start <= 0)
    {
        // Calls findall with an empty file name
        struct accumulator *accu = accu_init("");
        if (!accu)
            err(1, "cannot initialize the accumulator");
        findall(accu, cmd);
        free(accu);
    }
    else
    {
        // Calls findall on every file of the command line
        for (size_t i = cmd->files_start; i < cmd->files_end; i++)
        {
            struct accumulator *accu = accu_init(argv[i]);
            findall(accu, cmd);
            free(accu);
        }
    }
    command_free(cmd);
}
