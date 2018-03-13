/**
** \file parser.h
** \brief Header file for all the parser functions
** \author depott_g
*/

#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../variables/variables.h"

/*============================================================================*/
/* Functions from builtin.c */
/**
** \fn int (*builtin_find(char *name))(char **)
** \brief Searches for a builtin from its name and returns a pointer to the
          corresponding function.
** \param name Name of the builtin to search for
** \return A pointer to the function matching with the builtin name if found,
           else NULL
*/
int (*builtin_find(char *name))(char **);

/**
** \fn int bi_echo(char **args)
** \brief Builtin function that prints on stdout all the words contained in the
          array of strings separated by whitespaces, then prints a carriage
          return on stdout. If the first word is "-l", the ending carriage
          return is not printed.
** \param args The array of words to print
** \return 0
*/
int bi_echo(char **args);

#endif
