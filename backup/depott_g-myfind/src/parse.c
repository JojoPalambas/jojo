#include "include.h"

/**
 * \enum step
 * \brief Describes the type of word to parse next.
*/
enum step
{
    opt = 0, /*! Option */
    file = 1, /*! File name */
    expr = 2 /*! Expression */
};

/* Initializer for the command structure */
static struct command *cmd_init(int argc, char **argv)
{
    struct command *cmd = malloc(sizeof (struct command));
    if (!cmd)
        err(1, "cannot create structure command");
    cmd->argc = argc;
    cmd->argv = argv;
    cmd->pos = 1;
    cmd->opt = P;
    cmd->files_start = 0;
    cmd->files_end = argc;
    cmd->reverse = 0;
    cmd->expr = NULL;

    return cmd;
}

void command_free(struct command *cmd)
{
    if (!cmd)
        return;

    expr_free(cmd->expr);
    free(cmd);
    return;
}

/* Function that parses a single option */
static enum step parse_option(struct command *cmd, char *arg)
{
    enum step step = opt;
    if (my_strcmp(arg, "-H"))
        cmd->opt = H;
    else if (my_strcmp(arg, "-L"))
        cmd->opt = L;
    else if (my_strcmp(arg, "-P"))
        cmd->opt = P;
    else
    {
        step = file;
        cmd->files_start = cmd->pos;
    }
    return step;
}

/* Function used to parse the entire command line */
struct command *parse(int argc, char** argv)
{
    struct command *cmd = cmd_init(argc, argv);

    // Parsing options and file names
    enum step step = opt;
    for (; cmd->pos < argc && step < expr; cmd->pos++)
    {
        char *arg = argv[cmd->pos];
        if (step == opt)
        {
            step = parse_option(cmd, arg);
        }

        if (step == file)
        {
            if (arg[0] == '-')
            {
                cmd->files_end = cmd->pos;
                step = expr;
            }
        }
    }
    // Parsing expressions
    cmd->pos--;
    cmd->expr = expr_init("");
    cmd->expr->type = E_SENT;
    parse_expr(cmd, next, cmd->expr, cmd->expr);
    return cmd;
}
