/**
 * \file expr.c
 * \brief Functions needed to manipulate the expr structure (an AST structure).
 * \author depott_g
*/

#include "include.h"

/**
 * \fn struct expr *expr_init(char *arg)
 * \brief Initializes a new expr structure.
 * \param arg Keyword descripting the expression.
 * \return The newly created expr structure.
*/
struct expr *expr_init(char *arg)
{
    struct expr *expr = malloc(sizeof (struct expr));
    if (!expr)
        err(1, "Cannot malloc");
    expr->type = E_FILE;
    expr->name = arg;
    expr->left_op = NULL;
    expr->right_op = NULL;
    expr->next_op = NULL;
    return expr;
}

/**
 * \fn struct expr *expr_free(struct expr *expr)
 * \brief Recursively frees an expr structure.
 * \param expr The expr structure to free.
*/
void expr_free(struct expr *expr)
{
    if (!expr)
        return;

    expr_free(expr->left_op);
    expr_free(expr->right_op);
    expr_free(expr->next_op);
    free(expr);
    return;
}

/* Sets the type field of the expr struct regarding its name */
static void set_type(struct expr *expr)
{
    char *name = expr->name;
    if (my_strcmp(name, "-d"))
        expr->type = E_D;
    else if (my_strcmp(name, "-name"))
        expr->type = E_NAME;
    else if (my_strcmp(name, "-type"))
        expr->type = E_TYPE;
    else if (my_strcmp(name, "-o"))
        expr->type = E_OR;
    else if (my_strcmp(name, "-a"))
        expr->type = E_AND;
}

/**
 * \fn void parse_expr(struct command *cmd, enum direction direc,
 *                     struct expr *grandfather, struct expr *father)
 * \brief Parses the next expression from the command line.
 * \param cmd The command structure describing the command line.
 *        direc The direction the next child of the AST should go to.
 *        grandfather The grandparent of the expr node being created.
 *        father The parent of the expr node being created.
*/
void parse_expr(struct command *cmd, enum direction direc,
                struct expr *grandfather, struct expr *father)
{
    grandfather += 0;
    if (cmd->pos >= cmd->argc)
        return;
    char *arg = cmd->argv[cmd->pos];
    cmd->pos++;
    struct expr *expr = expr_init(arg);
    set_type(expr);
    switch (direc)
    {
        case next:
            father->next_op = expr;
            break;
        case left:
            father->left_op = expr;
            break;
        case right:
            father->right_op = expr;
            break;
        default:
            errx(1, "cannot parse the expressions: unexpected behavior");
    }

    if (expr->type == E_D)
        parse_expr(cmd, next, father, expr);
    else if (expr->type == E_NAME || expr->type == E_TYPE)
    {
        parse_expr(cmd, right, father, expr);
        parse_expr(cmd, next, father, expr);
    }
    else if(expr->type == E_OR || expr->type == E_OR)
    {
        if (father == grandfather)
            errx(1, "cannot parse the expressions: bad use of -o");
        grandfather->next_op = expr;
        father->next_op = NULL;
        expr->left_op = father;
        parse_expr(cmd, right, grandfather, expr);
        parse_expr(cmd, left, grandfather, expr);
    }
}
