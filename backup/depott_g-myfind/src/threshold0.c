#include "include.h"

static int apply_expr(struct command *cmd, struct expr *expr,
                      struct accumulator *accu, struct dirent *cur_dirent)
{
    if (!expr)
        return 1;
    switch (expr->type)
    {
        case E_SENT:
            return apply_expr(cmd, expr->next_op, accu, cur_dirent);
        case E_D:
            return func_d(cmd)
                && apply_expr(cmd, expr->next_op, accu, cur_dirent);

        case E_NAME:
            return func_name(expr, accu)
                && apply_expr(cmd, expr->next_op, accu, cur_dirent);

        case E_TYPE:
            return func_type(expr, accu)
                && apply_expr(cmd, expr->next_op, accu, cur_dirent);

        case E_OR:
            return (apply_expr(cmd, expr->left_op, accu, cur_dirent)
                 || apply_expr(cmd, expr->right_op, accu, cur_dirent))
                 && apply_expr(cmd, expr->next_op, accu, cur_dirent);

        case E_AND:
            return apply_expr(cmd, expr->left_op, accu, cur_dirent)
                && apply_expr(cmd, expr->right_op, accu, cur_dirent)
                && apply_expr(cmd, expr->next_op, accu, cur_dirent);

        default:
            return apply_expr(cmd, expr->next_op, accu, cur_dirent);
    }
}

/* Processes one file, applying the expr and printing its name if needed */
void process_file(struct dirent *cur_dirent,
        struct accumulator *accu, struct command *cmd)
{
    // Properly create a copy of accu concatenated with cur_dirent->d_name
    struct accumulator *cpy = accu_cpy(accu);
    if (!accu)
        err(1, "cannot copy the accumulator");

    if (cpy->path[cpy->pos - 1] != '/')
        accu_concat(cpy, "/");
    accu_concat(cpy, cur_dirent->d_name);

    // Processes the copy
    int result = apply_expr(cmd, cmd->expr, cpy, cur_dirent);
    if (result && !cmd->reverse)
        accu_print(cpy);

    // Calls findall_rec on the copy if needed
    struct stat st;
    int ans = lstat(cpy->path, &st);
    if (ans == -1)
        err(1, "cannot read %s", cpy->path);

    if (cur_dirent->d_type == DT_DIR
            || ((st.st_mode & S_IFMT) == S_IFLNK && cmd->opt == L))
    {
        findall_rec(cpy, cmd);
    }
    if (result && cmd->reverse)
        accu_print(cpy);
    free(cpy);
}

/* Recursive findall function, called on every file of the tree */
void findall_rec(struct accumulator *accu, struct command *cmd)
{
    // Opens the directory
    DIR *cur_dir = opendir(accu->path);
    if (!cur_dir)
        err(1, "cannot open %s", accu->path);
    struct dirent *cur_dirent = readdir(cur_dir);
    if (!cur_dirent)
        err(1, "cannot read %s", accu->path);

    // Processes every file in the directory
    while (cur_dirent)
    {
        if (my_strcmp(cur_dirent->d_name, ".")
            || my_strcmp(cur_dirent->d_name, ".."))
        {
            cur_dirent = readdir(cur_dir);
            continue;
        }
        process_file(cur_dirent, accu, cmd);
        cur_dirent = readdir(cur_dir);
    }
    closedir(cur_dir);
}

/* Function called on every file of the command line */
void findall(struct accumulator *accu, struct command *cmd)
{
    // Transforms the empty file name to the file name "."
    if (accu->path[0] == 0)
        accu_concat(accu, ".");

    // Manages the case when the file is a link but the -P option is enabled
    struct stat st;
    int ans = lstat(accu->path, &st);
    if (ans == -1)
        err(1, "cannot open %s", accu->path);
    if ((st.st_mode & S_IFMT) == S_IFLNK && cmd->opt == P)
    {
        accu_print(accu);
        return;
    }

    // The rest of the function is only for other cases
    // Manages the case when the name given does not match a directory
    DIR *cur_dir = opendir(accu->path);
    if (!cur_dir)
    {
        if (errno == ENOTDIR)
        {
            accu_print(accu);
            return;
        }
        err(1, "cannot open %s", accu->path);
    }
    struct dirent *cur_dirent = readdir(cur_dir);
    if (!cur_dirent)
        err(1, "cannot read %s", accu->path);

    // Treats the file and calls the recursive findall function on the file
    int result = apply_expr(cmd, cmd->expr, accu, cur_dirent);
    if (result && !cmd->reverse)
        accu_print(accu);
    findall_rec(accu, cmd);
    if (result && cmd->reverse)
        accu_print(accu);

    closedir(cur_dir);
}
