/**
 * \file accu.c
 * \brief Functions needed for the accumulator structure.
 * \author depott_g
*/

#include "include.h"
/**
 * \fn struct accumulator *accu_init(const char *path)
 * \brief Initializes a new accumulator structure.
 * \param path Path to put in the structure.
 * \return The newly created accumulator structure.
*/
struct accumulator *accu_init(const char *path)
{
    struct accumulator *accu = malloc(sizeof (struct accumulator));
    if (!accu)
        return NULL;
    accu->pos = 0;
    accu_concat(accu, path);
    return accu;
}

/**
 * \fn void *accu_concat(struct accumulator *accu, const char *path)
 * \brief Concatenates a string to the path of the accumulator.
 * \param accu Accumulator to concatenate the string to.
 *        path String to concatenate to the accumulator.
*/
void accu_concat(struct accumulator *accu, const char *path)
{
    int i = 0;
    for (; path[i] && i + accu->pos < 4096; i++)
        accu->path[accu->pos + i] = path[i];
    accu->pos += i;
    accu->path[accu->pos] = 0;
}

/**
 * \fn void accu_print(struct accumulator *accu)
 * \brief Prints the path contained in the accumulator.
 * \param accu The accumulator which path will be printed.
*/
void accu_print(struct accumulator *accu)
{
    printf("%s\n", accu->path);
}

/**
 * \fn void *accu_print_concat(struct accumulator *accu, const char *path)
 * \brief Prints the content of an accumulator concatenated with a string.
 * \param accu The accumulator to print.
 *        path The string to print after the accumulator.
*/
void accu_print_concat(struct accumulator *accu, const char *path)
{
    if (accu->path[accu->pos - 1] == '/')
        printf("%s%s\n", accu->path, path);
    else
        printf("%s/%s\n", accu->path, path);
}

/**
 * \fn struct accumulator *accu_cpy(struct accumulator *accu)
 * \brief Copies an accumulator.
 * \param accu Accumulator structure to copy.
 * \return The copy of the accumulator.
*/
struct accumulator *accu_cpy(struct accumulator *accu)
{
    struct accumulator *cpy = accu_init(accu->path);
    return cpy;
}
