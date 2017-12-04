/**
 * \file my_string.c
 * \brief Function needed to manipulate strings.
 * \author depott_g
*/

#include "include.h"

/**
 * \fn void 
 * \brief Compares two strings to tell if they are equal.
 * \param s1 First string
 *        s2 Second string
 * \return 1 if they are equal, 0 if not.
*/
int my_strcmp(const char *s1, const char *s2)
{
    for (int i = 0; s1[i] != '\0'; i++)
    {
        if (s2[i] == '\0')
            return 0;
        if (s1[i] != s2[i])
            return 0;
    }
    return 1;
}
