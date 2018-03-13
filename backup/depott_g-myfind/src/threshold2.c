#include "include.h"

/* Function that returns the last name given in a path (./foo/bar -> bar) */
static char *get_name(char *path)
{
    int start = 0;
    for (int i = 0; path[i]; i++)
        if (path[i] == '/')
            start = i + 1;
    return path + start;
}

/*
** Function that returns 1 if the type of the file which path is given in
** the accumulator structure is the same as the argument 'type'
*/
static int type_match(struct accumulator *accu, char *type)
{
    struct stat st;
    int ans = lstat(accu->path, &st);
    if (ans == -1)
        err(1, "cannot read %s", accu->path);

    switch(st.st_mode & S_IFMT)
    {
        case S_IFBLK:
            return my_strcmp(type, "b");
        case S_IFCHR:
            return my_strcmp(type, "c");
        case S_IFDIR:
            return my_strcmp(type, "d");
        case S_IFREG:
            return my_strcmp(type, "f");
        case S_IFLNK:
            return my_strcmp(type, "l");
        case S_IFIFO:
            return my_strcmp(type, "p");
        case S_IFSOCK:
            return my_strcmp(type, "s");
        default:
            return 0;
    }
    return 0;
}

/* Function that returns true if the names of expr and accu match */
int func_name(struct expr *expr, struct accumulator *accu)
{
    if (!expr->right_op || expr->right_op->type != E_FILE)
        return 0;
    if (fnmatch(expr->right_op->name, get_name(accu->path), 0))
        return 0;
    return 1;
}

/*
** Function that returns true if the type contained as a file name in expr
** is the same as the type of the file described by the path in accu
*/
int func_type(struct expr *expr, struct accumulator *accu)
{
    if (!expr->right_op || expr->right_op->type != E_FILE)
        return 0;
    return type_match(accu, expr->right_op->name);
    return 1;
}
